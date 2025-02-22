/*
* mdrv_miu.h- Sigmastar
*
* Copyright (C) 2018 Sigmastar Technology Corp.
*
* Author: karl.xiao <karl.xiao@sigmastar.com.tw>
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/
#ifndef __MDRV_MIU_H__
#define __MDRV_MIU_H__

#ifdef CONFIG_64BIT
    typedef unsigned long       phy_addr;                   // 4 bytes
#else
    typedef unsigned long long  phy_addr;                   // 8 bytes
#endif

//-------------------------------------------------------------------------------------------------
//  Enumeration Define
//-------------------------------------------------------------------------------------------------

typedef enum
{
    // group 0
    MIU_CLIENT_NONE,  //none can access
    MIU_CLIENT_VEN_R,
    MIU_CLIENT_VEN_W,
    MIU_CLIENT_DUMMY_G0C3,
    MIU_CLIENT_JPE_R,
    MIU_CLIENT_JPE_W,
    MIU_CLIENT_BACH_RW,
    MIU_CLIENT_AESDMA_RW,
    MIU_CLIENT_USB20_RW,
    MIU_CLIENT_EMAC_RW,
    MIU_CLIENT_MCU51_RW,
    MIU_CLIENT_URDMA_RW,
    MIU_CLIENT_BDMA_RW,
    MIU_CLIENT_MOVDMA0_RW,
    MIU_CLIENT_GOP3_R,
    MIU_CLIENT_DUMMY_G0CF,
    // group 1
    MIU_CLIENT_CMDQ_R,
    MIU_CLIENT_ISP_DMA_W,
    MIU_CLIENT_ISP_DMA_R,
    MIU_CLIENT_ISP_ROT_R,
    MIU_CLIENT_ISP_MLOAD_STA,
    MIU_CLIENT_GOP,
    MIU_CLIENT_DUMMY_G1C6,
    MIU_CLIENT_DIP0_R,
    MIU_CLIENT_DIP0_W,
    MIU_CLIENT_SC0_FRAME_W,
    MIU_CLIENT_DUMMY_G1CA,
    MIU_CLIENT_SC0_DBG_R,
    MIU_CLIENT_SC1_FRAME_W,
    MIU_CLIENT_SC2_FRAME_W,
    MIU_CLIENT_SD30_RW,
    MIU_CLIENT_SDIO30_RW,
    // group 2
    MIU_CLIENT_DUMMY_G2C0,
    MIU_CLIENT_DUMMY_G2C1,
    MIU_CLIENT_DUMMY_G2C2,
    MIU_CLIENT_DUMMY_G2C3,
    MIU_CLIENT_GOP1_R,
    MIU_CLIENT_GOP2_R,
    MIU_CLIENT_USB20_H_RW,
    MIU_CLIENT_IVE_RW,
    MIU_CLIENT_MIIC1_RW,
    MIU_CLIENT_3DNR0_W,
    MIU_CLIENT_3DNR0_R,
    MIU_CLIENT_DUMMY_G2CB,
    MIU_CLIENT_DUMMY_G2CC,
    MIU_CLIENT_DUMMY_G2CD,
    MIU_CLIENT_DUMMY_G2CE,
    MIU_CLIENT_DUMMY_G2CF,
    // group 3
    MIU_CLIENT_DUMMY_G3C0,
    MIU_CLIENT_DUMMY_G3C1,
    MIU_CLIENT_DUMMY_G3C2,
    MIU_CLIENT_DUMMY_G3C3,
    MIU_CLIENT_DUMMY_G3C4,
    MIU_CLIENT_DUMMY_G3C5,
    MIU_CLIENT_DUMMY_G3C6,
    MIU_CLIENT_DUMMY_G3C7,
    MIU_CLIENT_DUMMY_G3C8,
    MIU_CLIENT_DUMMY_G3C9,
    MIU_CLIENT_DUMMY_G3CA,
    MIU_CLIENT_DUMMY_G3CB,
    MIU_CLIENT_DUMMY_G3CC,
    MIU_CLIENT_DUMMY_G3CD,
    MIU_CLIENT_DUMMY_G3CE,
    MIU_CLIENT_DUMMY_G3CF,
    // group 4
    MIU_CLIENT_DUMMY_G4C0,
    MIU_CLIENT_DUMMY_G4C1,
    MIU_CLIENT_DUMMY_G4C2,
    MIU_CLIENT_DUMMY_G4C3,
    MIU_CLIENT_DUMMY_G4C4,
    MIU_CLIENT_DUMMY_G4C5,
    MIU_CLIENT_DUMMY_G4C6,
    MIU_CLIENT_DUMMY_G4C7,
    MIU_CLIENT_DUMMY_G4C8,
    MIU_CLIENT_DUMMY_G4C9,
    MIU_CLIENT_DUMMY_G4CA,
    MIU_CLIENT_DUMMY_G4CB,
    MIU_CLIENT_DUMMY_G4CC,
    MIU_CLIENT_DUMMY_G4CD,
    MIU_CLIENT_DUMMY_G4CE,
    MIU_CLIENT_DUMMY_G4CF,
    // group 5
    MIU_CLIENT_DUMMY_G5C0,
    MIU_CLIENT_DUMMY_G5C1,
    MIU_CLIENT_DUMMY_G5C2,
    MIU_CLIENT_DUMMY_G5C3,
    MIU_CLIENT_DUMMY_G5C4,
    MIU_CLIENT_DUMMY_G5C5,
    MIU_CLIENT_DUMMY_G5C6,
    MIU_CLIENT_DUMMY_G5C7,
    MIU_CLIENT_DUMMY_G5C8,
    MIU_CLIENT_DUMMY_G5C9,
    MIU_CLIENT_DUMMY_G5CA,
    MIU_CLIENT_DUMMY_G5CB,
    MIU_CLIENT_DUMMY_G5CC,
    MIU_CLIENT_DUMMY_G5CD,
    MIU_CLIENT_DUMMY_G5CE,
    MIU_CLIENT_DUMMY_G5CF,
    // group 6
    MIU_CLIENT_DUMMY_G6C0,
    MIU_CLIENT_DUMMY_G6C1,
    MIU_CLIENT_DUMMY_G6C2,
    MIU_CLIENT_DUMMY_G6C3,
    MIU_CLIENT_DUMMY_G6C4,
    MIU_CLIENT_DUMMY_G6C5,
    MIU_CLIENT_DUMMY_G6C6,
    MIU_CLIENT_DUMMY_G6C7,
    MIU_CLIENT_DUMMY_G6C8,
    MIU_CLIENT_DUMMY_G6C9,
    MIU_CLIENT_DUMMY_G6CA,
    MIU_CLIENT_DUMMY_G6CB,
    MIU_CLIENT_DUMMY_G6CC,
    MIU_CLIENT_DUMMY_G6CD,
    MIU_CLIENT_DUMMY_G6CE,
    MIU_CLIENT_DUMMY_G6CF,
    // group 7
    MIU_CLIENT_MIPS_RW,
    MIU_CLIENT_DUMMY_G7C1,
    MIU_CLIENT_DUMMY_G7C2,
    MIU_CLIENT_DUMMY_G7C3,
    MIU_CLIENT_DUMMY_G7C4,
    MIU_CLIENT_DUMMY_G7C5,
    MIU_CLIENT_DUMMY_G7C6,
    MIU_CLIENT_DUMMY_G7C7,
    MIU_CLIENT_DUMMY_G7C8,
    MIU_CLIENT_DUMMY_G7C9,
    MIU_CLIENT_DUMMY_G7CA,
    MIU_CLIENT_DUMMY_G7CB,
    MIU_CLIENT_DUMMY_G7CC,
    MIU_CLIENT_DUMMY_G7CD,
    MIU_CLIENT_DUMMY_G7CE,
    MIU_CLIENT_DUMMY_G7CF,
} eMIUClientID;

typedef enum
{
    E_MIU_0 = 0,
    E_MIU_1,
    E_MIU_2,
    E_MIU_3,
    E_MIU_NUM,
} MIU_ID;

typedef enum
{
    E_PROTECT_0 = 0,
    E_PROTECT_1,
    E_PROTECT_2,
    E_PROTECT_3,
    E_PROTECT_4,
    E_SLIT_0 = 16,
    E_MIU_PROTECT_NUM,
} PROTECT_ID;

//-------------------------------------------------------------------------------------------------
//  Structure Define
//-------------------------------------------------------------------------------------------------

typedef struct
{
    unsigned char   bHit;
    unsigned char   u8Group;
    unsigned char   u8ClientID;
    unsigned char   u8Block;
    unsigned int    uAddress;
} MIU_PortectInfo;

typedef struct
{
    unsigned int    size;           // bytes
    unsigned int    dram_freq;      // MHz
    unsigned int    miupll_freq;    // MHz
    unsigned char   type;           // 2:DDR2, 3:DDR3
    unsigned char   data_rate;      // 4:4x mode, 8:8x mode,
    unsigned char   bus_width;      // 16:16bit, 32:32bit, 64:64bit
    unsigned char   ssc;            // 0:off, 1:on
} MIU_DramInfo;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

#define CONFIG_MP_CMA_PATCH_DEBUG_STATIC_MIU_PROTECT

unsigned char MDrv_MIU_Init(void);
unsigned short* MDrv_MIU_GetDefaultClientID_KernelProtect(void);
unsigned short* MDrv_MIU_GetClientID_KernelProtect(unsigned char u8MiuSel);

unsigned char MDrv_MIU_Protect( unsigned char   u8Blockx,
                                unsigned short  *pu8ProtectId,
                                phy_addr        u64BusStart,
                                phy_addr        u64BusEnd,
                                unsigned char   bSetFlag);
#ifdef CONFIG_MP_CMA_PATCH_DEBUG_STATIC_MIU_PROTECT
unsigned char MDrv_MIU_GetProtectInfo(unsigned char u8MiuDev, MIU_PortectInfo *pInfo);
#endif
unsigned char MDrv_MIU_Slits(unsigned char u8Blockx, phy_addr u64SlitsStart, phy_addr u65SlitsEnd, unsigned char bSetFlag);
unsigned char MDrv_MIU_Get_IDEnables_Value(unsigned char u8MiuDev, unsigned char u8Blockx, unsigned char u8ClientIndex);
unsigned int MDrv_MIU_ProtectDramSize(void);
int MDrv_MIU_ClientIdToName(unsigned short clientId, char *clientName);
int MDrv_MIU_Info(MIU_DramInfo *pDramInfo);

#endif // __MDRV_MIU_H__
