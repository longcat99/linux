/**
 * ep0.c - DesignWare USB3 DRD Controller Endpoint 0 Handling
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2  of
 * the License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/list.h>
#include <linux/dma-mapping.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/composite.h>

#include "core.h"
#include "debug.h"
#include "gadget.h"
#include "io.h"
#include "../drivers/sstar/include/ms_platform.h"

static void __dwc3_ep0_do_control_status(struct dwc3 *dwc, struct dwc3_ep *dep);
static void __dwc3_ep0_do_control_data(struct dwc3 *dwc,
		struct dwc3_ep *dep, struct dwc3_request *req);

static const char *dwc3_ep0_state_string(enum dwc3_ep0_state state)
{
	switch (state) {
	case EP0_UNCONNECTED:
		return "Unconnected";
	case EP0_SETUP_PHASE:
		return "Setup Phase";
	case EP0_DATA_PHASE:
		return "Data Phase";
	case EP0_STATUS_PHASE:
		return "Status Phase";
	default:
		return "UNKNOWN";
	}
}

#ifdef DWC3_TRACE_EP0
static const char *dwc3_ep0_trb_type_string(u32 type)
{
	 switch (type)
	 {
		case DWC3_TRBCTL_NORMAL:
			return "normal";
		case DWC3_TRBCTL_CONTROL_SETUP:
			return "setup";
		case DWC3_TRBCTL_CONTROL_STATUS2:
			return "status2";
		case DWC3_TRBCTL_CONTROL_STATUS3:
			return "status3";
		case DWC3_TRBCTL_CONTROL_DATA:
			return "data";
		case DWC3_TRBCTL_ISOCHRONOUS_FIRST:
			return "isoc-first";
		case DWC3_TRBCTL_ISOCHRONOUS:
			return "isoc";
		case DWC3_TRBCTL_LINK_TRB:
			return "link";
		default:
			return "UNKNOWN";
	}
}
#endif

static void dwc3_ep0_prepare_one_trb(struct dwc3 *dwc, u8 epnum,
		dma_addr_t buf_dma, u32 len, u32 type, bool chain)
{
	struct dwc3_trb			*trb;
	struct dwc3_ep			*dep;
	dma_addr_t              miu_addr;

	dep = dwc->eps[epnum];

	trb = &dwc->ep0_trb[dep->trb_enqueue];

	if (chain)
		dep->trb_enqueue++;

    miu_addr = (dma_addr_t)Chip_Phys_to_MIU(buf_dma);
	trb->bpl = lower_32_bits(miu_addr);
	trb->bph = upper_32_bits(miu_addr);
	trb->size = len;
	trb->ctrl = type;

	trb->ctrl |= (DWC3_TRB_CTRL_HWO
			| DWC3_TRB_CTRL_ISP_IMI);

	if (chain)
		trb->ctrl |= DWC3_TRB_CTRL_CHN;
	else
		trb->ctrl |= (DWC3_TRB_CTRL_IOC
				| DWC3_TRB_CTRL_LST);

	trace_dwc3_prepare_trb(dep, trb);
#ifdef DWC3_TRACE_EP0
	printk(KERN_DEBUG "ep0_prepare_trb: %d/%d trb %p buf %08x%08x size %d ctrl %08x (%c%c%c%c:%c%c:%s)",
		dep->queued_requests, dep->allocated_requests,
		trb, trb->bph, trb->bpl,
		trb->size, trb->ctrl,
		trb->ctrl & DWC3_TRB_CTRL_HWO ? 'H' : 'h',
		trb->ctrl & DWC3_TRB_CTRL_LST ? 'L' : 'l',
		trb->ctrl & DWC3_TRB_CTRL_CHN ? 'C' : 'c',
		trb->ctrl & DWC3_TRB_CTRL_CSP ? 'S' : 's',
		trb->ctrl & DWC3_TRB_CTRL_ISP_IMI ? 'S' : 's',
		trb->ctrl & DWC3_TRB_CTRL_IOC ? 'C' : 'c',
		dwc3_ep0_trb_type_string(trb->ctrl & 0x3f0));
#endif
}

static int dwc3_ep0_start_trans(struct dwc3 *dwc, u8 epnum)
{
	struct dwc3_gadget_ep_cmd_params params;
	struct dwc3_ep			*dep;
	int				ret;
	dma_addr_t      miu_addr;

	dep = dwc->eps[epnum];
	if (dep->flags & DWC3_EP_BUSY) {
		dwc3_trace(trace_dwc3_ep0, "%s still busy", dep->name);
#ifdef DWC3_TRACE_EP0
		printk(KERN_DEBUG "\t =%s still busy", dep->name);
#endif
		return 0;
	}

	memset(&params, 0, sizeof(params));
	Chip_Flush_MIU_Pipe();
	miu_addr = (dma_addr_t)Chip_Phys_to_MIU(dwc->ep0_trb_addr);
	params.param0 = upper_32_bits(miu_addr);
	params.param1 = lower_32_bits(miu_addr);

	ret = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_STARTTRANSFER, &params);
	if (ret < 0) {
		dwc3_trace(trace_dwc3_ep0, "%s STARTTRANSFER failed",
				dep->name);
#ifdef DWC3_TRACE_EP0
		printk(KERN_DEBUG "\t =%s STARTTRANSFER failed", dep->name);
#endif
		return ret;
	}

	dep->flags |= DWC3_EP_BUSY;
	dep->resource_index = dwc3_gadget_ep_get_transfer_index(dep);
	dwc->ep0_next_event = DWC3_EP0_COMPLETE;

	return 0;
}

static int __dwc3_gadget_ep0_queue(struct dwc3_ep *dep,
		struct dwc3_request *req)
{
	struct dwc3		*dwc = dep->dwc;

	req->request.actual	= 0;
	req->request.status	= -EINPROGRESS;
	req->epnum		= dep->number;

	list_add_tail(&req->list, &dep->pending_list);

	/*
	 * Gadget driver might not be quick enough to queue a request
	 * before we get a Transfer Not Ready event on this endpoint.
	 *
	 * In that case, we will set DWC3_EP_PENDING_REQUEST. When that
	 * flag is set, it's telling us that as soon as Gadget queues the
	 * required request, we should kick the transfer here because the
	 * IRQ we were waiting for is long gone.
	 */
	if (dep->flags & DWC3_EP_PENDING_REQUEST) {
		unsigned	direction;

		direction = dwc->ep0_expect_in;

		if (dwc->ep0state != EP0_DATA_PHASE) {
			dev_WARN(dwc->dev, "Unexpected pending request\n");
			return 0;
		}

		__dwc3_ep0_do_control_data(dwc, dwc->eps[direction], req);

		dep->flags &= ~DWC3_EP_PENDING_REQUEST;

		return 0;
	}

	/*
	 * In case gadget driver asked us to delay the STATUS phase,
	 * handle it here.
	 */
	if (dwc->delayed_status) {
		unsigned	direction;

		direction = !dwc->ep0_expect_in;
		dwc->delayed_status = false;
		usb_gadget_set_state(&dwc->gadget, USB_STATE_CONFIGURED);

		if (dwc->ep0state == EP0_STATUS_PHASE) {
#ifdef DWC3_EP0_SCHEDULING
			// indicator flag hints that schedule contol status by ep0 thread is needed
			if (dwc->ep0_schedule_indicator) {
				dwc->ep0_scheduled = true;
				return 0;
			}
			else {
				dwc->ep0_scheduled = false;
			}
#endif
			__dwc3_ep0_do_control_status(dwc, dwc->eps[direction]);
		}
		else {
			dwc3_trace(trace_dwc3_ep0,
					"too early for delayed status");
#ifdef DWC3_TRACE_EP0
			printk(KERN_DEBUG "\t =too early for delayed status");
#endif
		}

		return 0;
	}

	/*
	 * Unfortunately we have uncovered a limitation wrt the Data Phase.
	 *
	 * Section 9.4 says we can wait for the XferNotReady(DATA) event to
	 * come before issueing Start Transfer command, but if we do, we will
	 * miss situations where the host starts another SETUP phase instead of
	 * the DATA phase.  Such cases happen at least on TD.7.6 of the Link
	 * Layer Compliance Suite.
	 *
	 * The problem surfaces due to the fact that in case of back-to-back
	 * SETUP packets there will be no XferNotReady(DATA) generated and we
	 * will be stuck waiting for XferNotReady(DATA) forever.
	 *
	 * By looking at tables 9-13 and 9-14 of the Databook, we can see that
	 * it tells us to start Data Phase right away. It also mentions that if
	 * we receive a SETUP phase instead of the DATA phase, core will issue
	 * XferComplete for the DATA phase, before actually initiating it in
	 * the wire, with the TRB's status set to "SETUP_PENDING". Such status
	 * can only be used to print some debugging logs, as the core expects
	 * us to go through to the STATUS phase and start a CONTROL_STATUS TRB,
	 * just so it completes right away, without transferring anything and,
	 * only then, we can go back to the SETUP phase.
	 *
	 * Because of this scenario, SNPS decided to change the programming
	 * model of control transfers and support on-demand transfers only for
	 * the STATUS phase. To fix the issue we have now, we will always wait
	 * for gadget driver to queue the DATA phase's struct usb_request, then
	 * start it right away.
	 *
	 * If we're actually in a 2-stage transfer, we will wait for
	 * XferNotReady(STATUS).
	 */
	if (dwc->three_stage_setup) {
		unsigned        direction;

		direction = dwc->ep0_expect_in;
#ifdef DWC3_EP0_SCHEDULING
		// indicator flag hints that schedule IN contol data by ep0 thread is needed
		if (dwc->ep0_schedule_indicator) {
			dwc->ep0_scheduled = true;
			return 0;
		}
		else {
			dwc->ep0_scheduled = false;
		}
#endif
		dwc->ep0state = EP0_DATA_PHASE;

		__dwc3_ep0_do_control_data(dwc, dwc->eps[direction], req);
	}

	return 0;
}

int dwc3_gadget_ep0_queue(struct usb_ep *ep, struct usb_request *request,
		gfp_t gfp_flags)
{
	struct dwc3_request		*req = to_dwc3_request(request);
	struct dwc3_ep			*dep = to_dwc3_ep(ep);
	struct dwc3			*dwc = dep->dwc;

	unsigned long			flags;

	int				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	if (!dep->endpoint.desc) {
		dwc3_trace(trace_dwc3_ep0,
				"trying to queue request %p to disabled %s",
				request, dep->name);
#ifdef DWC3_TRACE_EP0
		printk(KERN_DEBUG "\t =trying to queue request %p to disabled %s", request, dep->name);
#endif
		ret = -ESHUTDOWN;
		goto out;
	}

	/* we share one TRB for ep0/1 */
	if (!list_empty(&dep->pending_list)) {
		ret = -EBUSY;
		goto out;
	}

	dwc3_trace(trace_dwc3_ep0,
			"queueing request %p to %s length %d state '%s'",
			request, dep->name, request->length,
			dwc3_ep0_state_string(dwc->ep0state));
#ifdef DWC3_TRACE_EP0
	{
		unsigned	direction;
		if (dwc->ep0state == EP0_SETUP_PHASE && dwc->three_stage_setup)
			direction = dwc->ep0_expect_in;
		else
			direction = !dwc->ep0_expect_in;
		printk(KERN_DEBUG "queueing request %p to %s length %d state '%s'",
			request, dwc->eps[direction]->name, request->length,
			dwc3_ep0_state_string(dwc->ep0state));
	}
#endif

	ret = __dwc3_gadget_ep0_queue(dep, req);

out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	return ret;
}

static void dwc3_ep0_stall_and_restart(struct dwc3 *dwc)
{
	struct dwc3_ep		*dep;

	/* reinitialize physical ep1 */
	dep = dwc->eps[1];
	dep->flags = DWC3_EP_ENABLED;

	/* stall is always issued on EP0 */
	dep = dwc->eps[0];
	__dwc3_gadget_ep_set_halt(dep, 1, false);
	dep->flags = DWC3_EP_ENABLED;
	dwc->delayed_status = false;

	if (!list_empty(&dep->pending_list)) {
		struct dwc3_request	*req;

		req = next_request(&dep->pending_list);
		dwc3_gadget_giveback(dep, req, -ECONNRESET);
	}

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_start(dwc);
}

int __dwc3_gadget_ep0_set_halt(struct usb_ep *ep, int value)
{
	struct dwc3_ep			*dep = to_dwc3_ep(ep);
	struct dwc3			*dwc = dep->dwc;

	dwc3_ep0_stall_and_restart(dwc);

	return 0;
}

int dwc3_gadget_ep0_set_halt(struct usb_ep *ep, int value)
{
	struct dwc3_ep			*dep = to_dwc3_ep(ep);
	struct dwc3			*dwc = dep->dwc;
	unsigned long			flags;
	int				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_ep0_set_halt(ep, value);
	spin_unlock_irqrestore(&dwc->lock, flags);

	return ret;
}

void dwc3_ep0_out_start(struct dwc3 *dwc)
{
	int				ret;

	dwc3_ep0_prepare_one_trb(dwc, 0, dwc->ctrl_req_addr, 8,
			DWC3_TRBCTL_CONTROL_SETUP, false);
	ret = dwc3_ep0_start_trans(dwc, 0);
	WARN_ON(ret < 0);
}

static struct dwc3_ep *dwc3_wIndex_to_dep(struct dwc3 *dwc, __le16 wIndex_le)
{
	struct dwc3_ep		*dep;
	u32			windex = le16_to_cpu(wIndex_le);
	u32			epnum;

	epnum = (windex & USB_ENDPOINT_NUMBER_MASK) << 1;
	if ((windex & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN)
		epnum |= 1;

	dep = dwc->eps[epnum];
	if (dep->flags & DWC3_EP_ENABLED)
		return dep;

	return NULL;
}

static void dwc3_ep0_status_cmpl(struct usb_ep *ep, struct usb_request *req)
{
}
/*
 * ch 9.4.5
 */
static int dwc3_ep0_handle_status(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl)
{
	struct dwc3_ep		*dep;
	u32			recip;
	u32			reg;
	u16			usb_status = 0;
	__le16			*response_pkt;

	recip = ctrl->bRequestType & USB_RECIP_MASK;
	switch (recip) {
	case USB_RECIP_DEVICE:
		/*
		 * LTM will be set once we know how to set this in HW.
		 */
		usb_status |= dwc->gadget.is_selfpowered;

		if ((dwc->speed == DWC3_DSTS_SUPERSPEED) ||
		    (dwc->speed == DWC3_DSTS_SUPERSPEED_PLUS)) {
			reg = dwc3_readl(dwc->regs, DWC3_DCTL);
			if (reg & DWC3_DCTL_INITU1ENA)
				usb_status |= 1 << USB_DEV_STAT_U1_ENABLED;
			if (reg & DWC3_DCTL_INITU2ENA)
				usb_status |= 1 << USB_DEV_STAT_U2_ENABLED;
		}

		break;

	case USB_RECIP_INTERFACE:
		/*
		 * Function Remote Wake Capable	D0
		 * Function Remote Wakeup	D1
		 */
		break;

	case USB_RECIP_ENDPOINT:
		dep = dwc3_wIndex_to_dep(dwc, ctrl->wIndex);
		if (!dep)
			return -EINVAL;

		if (dep->flags & DWC3_EP_STALL)
			usb_status = 1 << USB_ENDPOINT_HALT;
		break;
	default:
		return -EINVAL;
	}

	response_pkt = (__le16 *) dwc->setup_buf;
	*response_pkt = cpu_to_le16(usb_status);

	dep = dwc->eps[0];
	dwc->ep0_usb_req.dep = dep;
	dwc->ep0_usb_req.request.length = sizeof(*response_pkt);
	dwc->ep0_usb_req.request.buf = dwc->setup_buf;
	dwc->ep0_usb_req.request.complete = dwc3_ep0_status_cmpl;

	return __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_req);
}

static int dwc3_ep0_handle_feature(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl, int set)
{
	struct dwc3_ep		*dep;
	u32			recip;
	u32			wValue;
	u32			wIndex;
	u32			reg;
	int			ret;
	enum usb_device_state	state;

	wValue = le16_to_cpu(ctrl->wValue);
	wIndex = le16_to_cpu(ctrl->wIndex);
	recip = ctrl->bRequestType & USB_RECIP_MASK;
	state = dwc->gadget.state;

	switch (recip) {
	case USB_RECIP_DEVICE:

		switch (wValue) {
		case USB_DEVICE_REMOTE_WAKEUP:
			break;
		/*
		 * 9.4.1 says only only for SS, in AddressState only for
		 * default control pipe
		 */
		case USB_DEVICE_U1_ENABLE:
			if (state != USB_STATE_CONFIGURED)
				return -EINVAL;
			if ((dwc->speed != DWC3_DSTS_SUPERSPEED) &&
			    (dwc->speed != DWC3_DSTS_SUPERSPEED_PLUS))
				return -EINVAL;

			reg = dwc3_readl(dwc->regs, DWC3_DCTL);
			//if (set)
				//reg |= DWC3_DCTL_INITU1ENA;
			//else
				//reg &= ~DWC3_DCTL_INITU1ENA;
			dwc3_writel(dwc->regs, DWC3_DCTL, reg);
			break;

		case USB_DEVICE_U2_ENABLE:
			if (state != USB_STATE_CONFIGURED)
				return -EINVAL;
			if ((dwc->speed != DWC3_DSTS_SUPERSPEED) &&
			    (dwc->speed != DWC3_DSTS_SUPERSPEED_PLUS))
				return -EINVAL;

			reg = dwc3_readl(dwc->regs, DWC3_DCTL);
			//if (set)
				//reg |= DWC3_DCTL_INITU2ENA;
			//else
				//reg &= ~DWC3_DCTL_INITU2ENA;
			dwc3_writel(dwc->regs, DWC3_DCTL, reg);
			break;

		case USB_DEVICE_LTM_ENABLE:
			return -EINVAL;

		case USB_DEVICE_TEST_MODE:
			if ((wIndex & 0xff) != 0)
				return -EINVAL;
			if (!set)
				return -EINVAL;

			switch (wIndex >> 8) {
			case TEST_J:
			case TEST_K:
			case TEST_SE0_NAK:
			case TEST_PACKET:
			case TEST_FORCE_EN:
				dwc->test_mode_nr = wIndex >> 8;
				dwc->test_mode = true;
				break;
			default:
				return -EINVAL;
			}
			break;
		default:
			return -EINVAL;
		}
		break;

	case USB_RECIP_INTERFACE:
		switch (wValue) {
		case USB_INTRF_FUNC_SUSPEND:
			if (wIndex & USB_INTRF_FUNC_SUSPEND_LP)
				/* XXX enable Low power suspend */
				;
			if (wIndex & USB_INTRF_FUNC_SUSPEND_RW)
				/* XXX enable remote wakeup */
				;
			break;
		default:
			return -EINVAL;
		}
		break;

	case USB_RECIP_ENDPOINT:
		switch (wValue) {
		case USB_ENDPOINT_HALT:
			dep = dwc3_wIndex_to_dep(dwc, ctrl->wIndex);
			if (!dep)
				return -EINVAL;
			if (set == 0 && (dep->flags & DWC3_EP_WEDGE))
				break;
			ret = __dwc3_gadget_ep_set_halt(dep, set, true);
			if (ret)
				return -EINVAL;
			break;
		default:
			return -EINVAL;
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int dwc3_ep0_set_address(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	enum usb_device_state state = dwc->gadget.state;
	u32 addr;
	u32 reg;

	addr = le16_to_cpu(ctrl->wValue);
	if (addr > 127) {
		dwc3_trace(trace_dwc3_ep0, "invalid device address %d", addr);
		return -EINVAL;
	}

	if (state == USB_STATE_CONFIGURED) {
		dwc3_trace(trace_dwc3_ep0,
				"trying to set address when configured");
		return -EINVAL;
	}

	reg = dwc3_readl(dwc->regs, DWC3_DCFG);
	reg &= ~(DWC3_DCFG_DEVADDR_MASK);
	reg |= DWC3_DCFG_DEVADDR(addr);
	dwc3_writel(dwc->regs, DWC3_DCFG, reg);

	if (addr)
		usb_gadget_set_state(&dwc->gadget, USB_STATE_ADDRESS);
	else
		usb_gadget_set_state(&dwc->gadget, USB_STATE_DEFAULT);

	return 0;
}

static int dwc3_ep0_delegate_req(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	int ret;

	spin_unlock(&dwc->lock);
	ret = dwc->gadget_driver->setup(&dwc->gadget, ctrl);
	spin_lock(&dwc->lock);
	return ret;
}

static int dwc3_ep0_set_config(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	enum usb_device_state state = dwc->gadget.state;
	u32 cfg;
	int ret;
	u32 reg;

	cfg = le16_to_cpu(ctrl->wValue);

	switch (state) {
	case USB_STATE_DEFAULT:
		return -EINVAL;

	case USB_STATE_ADDRESS:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		/* if the cfg matches and the cfg is non zero */
		if (cfg && (!ret || (ret == USB_GADGET_DELAYED_STATUS))) {

			/*
			 * only change state if set_config has already
			 * been processed. If gadget driver returns
			 * USB_GADGET_DELAYED_STATUS, we will wait
			 * to change the state on the next usb_ep_queue()
			 */
			if (ret == 0)
				usb_gadget_set_state(&dwc->gadget,
						USB_STATE_CONFIGURED);

			/*
			 * Enable transition to U1/U2 state when
			 * nothing is pending from application.
			 */
			reg = dwc3_readl(dwc->regs, DWC3_DCTL);
			//reg |= (DWC3_DCTL_ACCEPTU1ENA | DWC3_DCTL_ACCEPTU2ENA);
			dwc3_writel(dwc->regs, DWC3_DCTL, reg);
		}
		break;

	case USB_STATE_CONFIGURED:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		if (!cfg && !ret)
			usb_gadget_set_state(&dwc->gadget,
					USB_STATE_ADDRESS);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}

static void dwc3_ep0_set_sel_cmpl(struct usb_ep *ep, struct usb_request *req)
{
	struct dwc3_ep	*dep = to_dwc3_ep(ep);
	struct dwc3	*dwc = dep->dwc;

	u32		param = 0;
	u32		reg;

	struct timing {
		u8	u1sel;
		u8	u1pel;
		__le16	u2sel;
		__le16	u2pel;
	} __packed timing;

	int		ret;

	memcpy(&timing, req->buf, sizeof(timing));

	dwc->u1sel = timing.u1sel;
	dwc->u1pel = timing.u1pel;
	dwc->u2sel = le16_to_cpu(timing.u2sel);
	dwc->u2pel = le16_to_cpu(timing.u2pel);

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	if (reg & DWC3_DCTL_INITU2ENA)
		param = dwc->u2pel;
	if (reg & DWC3_DCTL_INITU1ENA)
		param = dwc->u1pel;

	/*
	 * According to Synopsys Databook, if parameter is
	 * greater than 125, a value of zero should be
	 * programmed in the register.
	 */
	if (param > 125)
		param = 0;

	/* now that we have the time, issue DGCMD Set Sel */
	ret = dwc3_send_gadget_generic_command(dwc,
			DWC3_DGCMD_SET_PERIODIC_PAR, param);
	WARN_ON(ret < 0);
}

static int dwc3_ep0_set_sel(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	struct dwc3_ep	*dep;
	enum usb_device_state state = dwc->gadget.state;
	u16		wLength;
	u16		wValue;

	if (state == USB_STATE_DEFAULT)
		return -EINVAL;

	wValue = le16_to_cpu(ctrl->wValue);
	wLength = le16_to_cpu(ctrl->wLength);

	if (wLength != 6) {
		dev_err(dwc->dev, "Set SEL should be 6 bytes, got %d\n",
				wLength);
		return -EINVAL;
	}

	/*
	 * To handle Set SEL we need to receive 6 bytes from Host. So let's
	 * queue a usb_request for 6 bytes.
	 *
	 * Remember, though, this controller can't handle non-wMaxPacketSize
	 * aligned transfers on the OUT direction, so we queue a request for
	 * wMaxPacketSize instead.
	 */
	dep = dwc->eps[0];
	dwc->ep0_usb_req.dep = dep;
	dwc->ep0_usb_req.request.length = dep->endpoint.maxpacket;
	dwc->ep0_usb_req.request.buf = dwc->setup_buf;
	dwc->ep0_usb_req.request.complete = dwc3_ep0_set_sel_cmpl;

	return __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_req);
}

static int dwc3_ep0_set_isoch_delay(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	u16		wLength;
	u16		wValue;
	u16		wIndex;

	wValue = le16_to_cpu(ctrl->wValue);
	wLength = le16_to_cpu(ctrl->wLength);
	wIndex = le16_to_cpu(ctrl->wIndex);

	if (wIndex || wLength)
		return -EINVAL;

	/*
	 * REVISIT It's unclear from Databook what to do with this
	 * value. For now, just cache it.
	 */
	dwc->isoch_delay = wValue;

	return 0;
}

static int dwc3_ep0_std_request(struct dwc3 *dwc, struct usb_ctrlrequest *ctrl)
{
	int ret;

	switch (ctrl->bRequest) {
	case USB_REQ_GET_STATUS:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_GET_STATUS");
		ret = dwc3_ep0_handle_status(dwc, ctrl);
		break;
	case USB_REQ_CLEAR_FEATURE:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_CLEAR_FEATURE");
		ret = dwc3_ep0_handle_feature(dwc, ctrl, 0);
		break;
	case USB_REQ_SET_FEATURE:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_SET_FEATURE");
		ret = dwc3_ep0_handle_feature(dwc, ctrl, 1);
		break;
	case USB_REQ_SET_ADDRESS:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_SET_ADDRESS");
		ret = dwc3_ep0_set_address(dwc, ctrl);
		break;
	case USB_REQ_SET_CONFIGURATION:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_SET_CONFIGURATION");
		ret = dwc3_ep0_set_config(dwc, ctrl);
		break;
	case USB_REQ_SET_SEL:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_SET_SEL");
		ret = dwc3_ep0_set_sel(dwc, ctrl);
		break;
	case USB_REQ_SET_ISOCH_DELAY:
		dwc3_trace(trace_dwc3_ep0, "USB_REQ_SET_ISOCH_DELAY");
		ret = dwc3_ep0_set_isoch_delay(dwc, ctrl);
		break;
	default:
		dwc3_trace(trace_dwc3_ep0, "Forwarding to gadget driver");
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		break;
	}

	return ret;
}

static void dwc3_ep0_inspect_setup(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	struct usb_ctrlrequest *ctrl = dwc->ctrl_req;
	int ret = -EINVAL;
	u32 len;

	if (!dwc->gadget_driver)
		goto out;

	trace_dwc3_ctrl_req(ctrl);

#ifdef DWC3_EP0_SCHEDULING
	if (dwc->ep0_wait_setup_recv) {
		complete(&dwc->ep0_comp);
		dwc->ep0_wait_setup_recv = false;
	}
#endif

	len = le16_to_cpu(ctrl->wLength);
	if (!len) {
		dwc->three_stage_setup = false;
		dwc->ep0_expect_in = false;
		dwc->ep0_next_event = DWC3_EP0_NRDY_STATUS;
	} else {
		dwc->three_stage_setup = true;
		dwc->ep0_expect_in = !!(ctrl->bRequestType & USB_DIR_IN);
		dwc->ep0_next_event = DWC3_EP0_NRDY_DATA;
	}

	if ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		ret = dwc3_ep0_std_request(dwc, ctrl);
	else
		ret = dwc3_ep0_delegate_req(dwc, ctrl);

	if (ret == USB_GADGET_DELAYED_STATUS)
		dwc->delayed_status = true;

out:
	if (ret < 0)
		dwc3_ep0_stall_and_restart(dwc);
}

static void dwc3_ep0_complete_data(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	struct dwc3_request	*r = NULL;
	struct usb_request	*ur;
	struct dwc3_trb		*trb;
	struct dwc3_ep		*ep0;
	unsigned		transfer_size = 0;
	unsigned		maxp;
	unsigned		remaining_ur_length;
	void			*buf;
	u32			transferred = 0;
	u32			status;
	u32			length;
	u8			epnum;

	epnum = event->endpoint_number;
	ep0 = dwc->eps[0];

	dwc->ep0_next_event = DWC3_EP0_NRDY_STATUS;

	trb = dwc->ep0_trb;

	trace_dwc3_complete_trb(ep0, trb);
#ifdef DWC3_TRACE_EP0
	printk(KERN_DEBUG "ep0_complete_trb: %d/%d trb %p buf %08x%08x size %d ctrl %08x (%c%c%c%c:%c%c:%s)",
		ep0->queued_requests, ep0->allocated_requests,
		trb, trb->bph, trb->bpl,
		trb->size, trb->ctrl,
		trb->ctrl & DWC3_TRB_CTRL_HWO ? 'H' : 'h',
		trb->ctrl & DWC3_TRB_CTRL_LST ? 'L' : 'l',
		trb->ctrl & DWC3_TRB_CTRL_CHN ? 'C' : 'c',
		trb->ctrl & DWC3_TRB_CTRL_CSP ? 'S' : 's',
		trb->ctrl & DWC3_TRB_CTRL_ISP_IMI ? 'S' : 's',
		trb->ctrl & DWC3_TRB_CTRL_IOC ? 'C' : 'c',
		dwc3_ep0_trb_type_string(trb->ctrl & 0x3f0));
#endif

	r = next_request(&ep0->pending_list);
	if (!r)
		return;

	status = DWC3_TRB_SIZE_TRBSTS(trb->size);
	if (status == DWC3_TRBSTS_SETUP_PENDING) {
		dwc->setup_packet_pending = true;

		dwc3_trace(trace_dwc3_ep0, "Setup Pending received");
#ifdef DWC3_TRACE_EP0
		printk(KERN_DEBUG "\t =Setup Pending received");
#endif
		if (r)
			dwc3_gadget_giveback(ep0, r, -ECONNRESET);

		return;
	}

	ur = &r->request;
	buf = ur->buf;
	remaining_ur_length = ur->length;

	length = trb->size & DWC3_TRB_SIZE_MASK;

	maxp = ep0->endpoint.maxpacket;

	if (dwc->ep0_bounced) {
		/*
		 * Handle the first TRB before handling the bounce buffer if
		 * the request length is greater than the bounce buffer size
		 */
		if (ur->length > DWC3_EP0_BOUNCE_SIZE) {
			transfer_size = ALIGN(ur->length - maxp, maxp);
			transferred = transfer_size - length;
			buf = (u8 *)buf + transferred;
			ur->actual += transferred;
			remaining_ur_length -= transferred;

			trb++;
			length = trb->size & DWC3_TRB_SIZE_MASK;

			ep0->trb_enqueue = 0;
		}

		transfer_size = roundup((ur->length - transfer_size),
					maxp);

		transferred = min_t(u32, remaining_ur_length,
				    transfer_size - length);
		memcpy(buf, dwc->ep0_bounce, transferred);
	} else {
		transferred = ur->length - length;
	}

	ur->actual += transferred;

	if ((epnum & 1) && ur->actual < ur->length) {
		/* for some reason we did not get everything out */

		dwc3_ep0_stall_and_restart(dwc);
	} else {
		dwc3_gadget_giveback(ep0, r, 0);

		if (IS_ALIGNED(ur->length, ep0->endpoint.maxpacket) &&
				ur->length && ur->zero) {
			int ret;

			dwc->ep0_next_event = DWC3_EP0_COMPLETE;

			dwc3_ep0_prepare_one_trb(dwc, epnum, dwc->ctrl_req_addr,
					0, DWC3_TRBCTL_CONTROL_DATA, false);
			ret = dwc3_ep0_start_trans(dwc, epnum);
			WARN_ON(ret < 0);
		}
	}
}

static void dwc3_ep0_complete_status(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	struct dwc3_request	*r;
	struct dwc3_ep		*dep;
	struct dwc3_trb		*trb;
	u32			status;

	dep = dwc->eps[0];
	trb = dwc->ep0_trb;

	trace_dwc3_complete_trb(dep, trb);
#ifdef DWC3_TRACE_EP0
	printk(KERN_DEBUG "ep0_complete_trb: %d/%d trb %p buf %08x%08x size %d ctrl %08x (%c%c%c%c:%c%c:%s)",
		dep->queued_requests, dep->allocated_requests,
		trb, trb->bph, trb->bpl,
		trb->size, trb->ctrl,
		trb->ctrl & DWC3_TRB_CTRL_HWO ? 'H' : 'h',
		trb->ctrl & DWC3_TRB_CTRL_LST ? 'L' : 'l',
		trb->ctrl & DWC3_TRB_CTRL_CHN ? 'C' : 'c',
		trb->ctrl & DWC3_TRB_CTRL_CSP ? 'S' : 's',
		trb->ctrl & DWC3_TRB_CTRL_ISP_IMI ? 'S' : 's',
		trb->ctrl & DWC3_TRB_CTRL_IOC ? 'C' : 'c',
		dwc3_ep0_trb_type_string(trb->ctrl & 0x3f0));
#endif

	if (!list_empty(&dep->pending_list)) {
		r = next_request(&dep->pending_list);

		dwc3_gadget_giveback(dep, r, 0);
	}

	if (dwc->test_mode) {
		int ret;

		ret = dwc3_gadget_set_test_mode(dwc, dwc->test_mode_nr);
		if (ret < 0) {
			dwc3_trace(trace_dwc3_ep0, "Invalid Test #%d",
					dwc->test_mode_nr);
			dwc3_ep0_stall_and_restart(dwc);
			return;
		}
	}

	status = DWC3_TRB_SIZE_TRBSTS(trb->size);
	if (status == DWC3_TRBSTS_SETUP_PENDING) {
		dwc->setup_packet_pending = true;
		dwc3_trace(trace_dwc3_ep0, "Setup Pending received");
#ifdef DWC3_TRACE_EP0
		printk(KERN_DEBUG "\t =Setup Pending received");
#endif
	}

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_start(dwc);
#ifdef DWC3_EP0_SCHEDULING
	if (dwc->ep0_scheduled) {
		complete(&dwc->ep0_comp); // ep0 xfer was scheduled & wait completion, wakeup up ep0 thread here
	}
#endif
}

static void dwc3_ep0_xfer_complete(struct dwc3 *dwc,
			const struct dwc3_event_depevt *event)
{
	struct dwc3_ep		*dep = dwc->eps[event->endpoint_number];

	dep->flags &= ~DWC3_EP_BUSY;
	dep->resource_index = 0;
	dwc->setup_packet_pending = false;

	switch (dwc->ep0state) {
	case EP0_SETUP_PHASE:
		dwc3_trace(trace_dwc3_ep0, "Setup Phase");
		dwc3_ep0_inspect_setup(dwc, event);
		break;

	case EP0_DATA_PHASE:
		dwc3_trace(trace_dwc3_ep0, "Data Phase");
		dwc3_ep0_complete_data(dwc, event);
#ifdef DWC3_EP0_SCHEDULING
		if (dwc->ep0_scheduled) {
			complete(&dwc->ep0_comp); // ep0 xfer was scheduled & wait completion, wakeup up ep0 thread here
		}
#endif
		break;

	case EP0_STATUS_PHASE:
		dwc3_trace(trace_dwc3_ep0, "Status Phase");
		dwc3_ep0_complete_status(dwc, event);
		break;
	default:
		WARN(true, "UNKNOWN ep0state %d\n", dwc->ep0state);
	}
}

static void __dwc3_ep0_do_control_data(struct dwc3 *dwc,
		struct dwc3_ep *dep, struct dwc3_request *req)
{
	int			ret;

	req->direction = !!dep->number;

	if (req->request.length == 0) {
		dwc3_ep0_prepare_one_trb(dwc, dep->number,
				dwc->ctrl_req_addr, 0,
				DWC3_TRBCTL_CONTROL_DATA, false);
		ret = dwc3_ep0_start_trans(dwc, dep->number);
	} else if (!IS_ALIGNED(req->request.length, dep->endpoint.maxpacket)
			&& (dep->number == 0)) {
		u32	transfer_size = 0;
		u32	maxpacket;

		ret = usb_gadget_map_request(&dwc->gadget, &req->request,
				dep->number);
		if (ret) {
			dwc3_trace(trace_dwc3_ep0, "failed to map request");
#ifdef DWC3_TRACE_EP0
			printk(KERN_DEBUG "\t =failed to map request");
#endif
			return;
		}

		maxpacket = dep->endpoint.maxpacket;

		if (req->request.length > DWC3_EP0_BOUNCE_SIZE) {
			transfer_size = ALIGN(req->request.length - maxpacket,
					      maxpacket);
			dwc3_ep0_prepare_one_trb(dwc, dep->number,
						   req->request.dma,
						   transfer_size,
						   DWC3_TRBCTL_CONTROL_DATA,
						   true);
		}

		transfer_size = roundup((req->request.length - transfer_size),
					maxpacket);

		dwc->ep0_bounced = true;

		dwc3_ep0_prepare_one_trb(dwc, dep->number,
				dwc->ep0_bounce_addr, transfer_size,
				DWC3_TRBCTL_CONTROL_DATA, false);
		ret = dwc3_ep0_start_trans(dwc, dep->number);
	} else {
		ret = usb_gadget_map_request(&dwc->gadget, &req->request,
				dep->number);
		if (ret) {
			dwc3_trace(trace_dwc3_ep0, "failed to map request");
#ifdef DWC3_TRACE_EP0
			printk(KERN_DEBUG "\t =failed to map request");
#endif
			return;
		}

		dwc3_ep0_prepare_one_trb(dwc, dep->number, req->request.dma,
				req->request.length, DWC3_TRBCTL_CONTROL_DATA,
				false);
		ret = dwc3_ep0_start_trans(dwc, dep->number);
	}

	WARN_ON(ret < 0);
}

static int dwc3_ep0_start_control_status(struct dwc3_ep *dep)
{
	struct dwc3		*dwc = dep->dwc;
	u32			type;

	type = dwc->three_stage_setup ? DWC3_TRBCTL_CONTROL_STATUS3
		: DWC3_TRBCTL_CONTROL_STATUS2;

	dwc3_ep0_prepare_one_trb(dwc, dep->number,
			dwc->ctrl_req_addr, 0, type, false);
	return dwc3_ep0_start_trans(dwc, dep->number);
}

static void __dwc3_ep0_do_control_status(struct dwc3 *dwc, struct dwc3_ep *dep)
{
	WARN_ON(dwc3_ep0_start_control_status(dep));
}

static void dwc3_ep0_do_control_status(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	struct dwc3_ep		*dep = dwc->eps[event->endpoint_number];

#ifdef DWC3_EP0_SCHEDULING
	// indicator flag hints that schedule contol status by ep0 thread is needed
	if (dwc->ep0_schedule_indicator) {
		dwc->ep0_scheduled = true;
		return;
	}
	else {
		dwc->ep0_scheduled = false;
	}
#endif
	__dwc3_ep0_do_control_status(dwc, dep);
}

static void dwc3_ep0_end_control_data(struct dwc3 *dwc, struct dwc3_ep *dep)
{
	struct dwc3_gadget_ep_cmd_params params;
	u32			cmd;
	int			ret;

	if (!dep->resource_index)
		return;

	cmd = DWC3_DEPCMD_ENDTRANSFER;
	cmd |= DWC3_DEPCMD_CMDIOC;
	cmd |= DWC3_DEPCMD_PARAM(dep->resource_index);
	memset(&params, 0, sizeof(params));
	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	WARN_ON_ONCE(ret);
	dep->resource_index = 0;
}

static void dwc3_ep0_xfernotready(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	switch (event->status) {
	case DEPEVT_STATUS_CONTROL_DATA:
		dwc3_trace(trace_dwc3_ep0, "Control Data");

		/*
		 * We already have a DATA transfer in the controller's cache,
		 * if we receive a XferNotReady(DATA) we will ignore it, unless
		 * it's for the wrong direction.
		 *
		 * In that case, we must issue END_TRANSFER command to the Data
		 * Phase we already have started and issue SetStall on the
		 * control endpoint.
		 */
		if (dwc->ep0_expect_in != event->endpoint_number) {
			struct dwc3_ep	*dep = dwc->eps[dwc->ep0_expect_in];

			dwc3_trace(trace_dwc3_ep0,
					"Wrong direction for Data phase");
#ifdef DWC3_TRACE_EP0
			printk(KERN_DEBUG "\t =Wrong direction for Data phase %d %d", dwc->ep0_expect_in, event->endpoint_number);
			printk(KERN_DEBUG "bRequestType %02x bRequest %02x wValue %04x wIndex %04x wLength %d",
				dwc->ctrl_req->bRequestType, dwc->ctrl_req->bRequest,
				dwc->ctrl_req->wValue, dwc->ctrl_req->wIndex,
				dwc->ctrl_req->wLength);
#endif
			dwc3_ep0_end_control_data(dwc, dep);
			dwc3_ep0_stall_and_restart(dwc);
			return;
		}

		break;

	case DEPEVT_STATUS_CONTROL_STATUS:
		if (dwc->ep0_next_event != DWC3_EP0_NRDY_STATUS)
			return;

		dwc3_trace(trace_dwc3_ep0, "Control Status");

		dwc->ep0state = EP0_STATUS_PHASE;

		if (dwc->delayed_status) {
			WARN_ON_ONCE(event->endpoint_number != 1);
#ifdef DWC3_EP0_SCHEDULING
			dwc->ep0_scheduled = false;
#endif
			dwc3_trace(trace_dwc3_ep0, "Delayed Status");
#ifdef DWC3_TRACE_EP0
			printk(KERN_DEBUG "\t =Delayed Status");
#endif
			return;
		}

		dwc3_ep0_do_control_status(dwc, event);
	}
}

void dwc3_ep0_interrupt(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	dwc3_trace(trace_dwc3_ep0, "%s: state '%s'",
			dwc3_ep_event_string(event),
			dwc3_ep0_state_string(dwc->ep0state));
#ifdef DWC3_TRACE_EP0
	printk(KERN_DEBUG "%s %s %x", dwc3_ep_event_string(event),
			dwc3_ep0_state_string(dwc->ep0state), event->status);
#endif

	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFERCOMPLETE:
		dwc3_ep0_xfer_complete(dwc, event);
		break;

	case DWC3_DEPEVT_XFERNOTREADY:
		dwc3_ep0_xfernotready(dwc, event);
		break;

	case DWC3_DEPEVT_XFERINPROGRESS:
	case DWC3_DEPEVT_RXTXFIFOEVT:
	case DWC3_DEPEVT_STREAMEVT:
	case DWC3_DEPEVT_EPCMDCMPLT:
		break;
	}
}

#ifdef DWC3_EP0_SCHEDULING
extern void dwc3_stop_active_transfer(struct dwc3 *dwc, u32 epnum, bool force);

int dwc3_ep0_thread(void *arg)
{
	struct dwc3 *dwc = (struct dwc3 *)arg;
	unsigned long	flags, completed;
	struct dwc3_ep	*ep0, *dep;

	while(!kthread_should_stop())
	{
		wait_for_completion(&dwc->ep0_comp);
		ep0 = dwc->eps[0];

		if (!dwc->ep0_scheduled)
			goto do_endxfer;

		spin_lock_irqsave(&dwc->lock, flags);
		if ((dwc->ep0state == EP0_SETUP_PHASE) && !list_empty(&ep0->pending_list) && dwc->three_stage_setup)
		{
			dwc->ep0state = EP0_DATA_PHASE;
			if (dwc->ep0_expect_in)
				dep = dwc->eps[1];
			else
				dep = dwc->eps[0];
			__dwc3_ep0_do_control_data(dwc, dep, next_request(&ep0->pending_list));
			spin_unlock_irqrestore(&dwc->lock, flags);
			wait_for_completion(&dwc->ep0_comp);
		}
		else if (dwc->ep0state == EP0_STATUS_PHASE && dwc->ep0_next_event == DWC3_EP0_NRDY_STATUS)
		{
			if (dwc->ep0_expect_in)
				dep = dwc->eps[0];
			else
				dep = dwc->eps[1];
			__dwc3_ep0_do_control_status(dwc, dep);
			spin_unlock_irqrestore(&dwc->lock, flags);
			wait_for_completion(&dwc->ep0_comp);
		}
		else {
			spin_unlock_irqrestore(&dwc->lock, flags);
		}
		spin_lock_irqsave(&dwc->lock, flags);
		if (!dwc->ep0_schedule_indicator) // no need to schedule ep0 xfer, let's handle ep0 in irq thread
			dwc->ep0_scheduled = false;
		spin_unlock_irqrestore(&dwc->lock, flags);

do_endxfer:
		if (dwc->isoc_in_ep_stopxfer) {
			u32 ep_num = 0;

			spin_lock_irqsave(&dwc->lock, flags);
			if (dwc->ep0state == EP0_SETUP_PHASE && dwc->ep0_next_event == DWC3_EP0_COMPLETE) {
				u32 reg = dwc3_readl(dwc->regs, DWC3_DSTS);
				if (!(reg & DWC3_DSTS_RXFIFOEMPTY)) { // RxFIFO is not empty, wait till setup xfer completed
#ifdef DWC3_TRACE_EP0
					printk(KERN_DEBUG"@Rx");
#endif
					dwc->ep0_wait_setup_recv = true;
					spin_unlock_irqrestore(&dwc->lock, flags);
					completed = wait_for_completion_timeout(&dwc->ep0_comp, __msecs_to_jiffies(10));
					if (!completed)
						dwc->ep0_wait_setup_recv = false;
#ifdef DWC3_TRACE_EP0
					printk(KERN_DEBUG"^Rx%ld", completed);
#endif
				}
				else {
					spin_unlock_irqrestore(&dwc->lock, flags);
				}
			}
			else {
				spin_unlock_irqrestore(&dwc->lock, flags);
			}

			spin_lock_irqsave(&dwc->lock, flags);
			ep_num = dwc->isoc_in_ep_stopxfer;
			dep = dwc->eps[ep_num];
			dwc3_stop_active_transfer(dwc, ep_num, true);
			dep->flags = DWC3_EP_ENABLED;
			dwc->isoc_in_ep_stopxfer = 0;
			if (dep->pending_requests || dep->queued_requests) {
				dwc->ep0_schedule_indicator = true;
#ifdef DWC3_ISOC_MONITOR
				dwc->isoc_in_ep_activated = false;
				// 35ms delayed work to monitor whether isoc xfer keeps in progressing
				mod_delayed_work(dwc->isoc_in_wq, &dwc->isoc_in_monitor, __msecs_to_jiffies(35));
#endif
			}
			spin_unlock_irqrestore(&dwc->lock, flags);
		}
	}
	return 0;
}
#endif
