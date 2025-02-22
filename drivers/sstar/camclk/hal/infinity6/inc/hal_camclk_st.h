/* Copyright (c) 2018-2019 Sigmastar Technology Corp.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
Sigmastar Technology Corp. and be kept in strict confidence
(Sigmastar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of Sigmastar Confidential
Information is unlawful and strictly prohibited. Sigmastar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
*/

#ifndef __HAL_CAMCLK_ST_H__
#define __HAL_CAMCLK_ST_H__


typedef struct
{
    u32 u32Rate;
    u32 u32ParentRate;
}HalCamClkSetComplexRate_t;
typedef struct
{
    u32 u32Rate;
    u32 u32ParentRate;
}HalCamClkGetComplexRate_t;
typedef struct
{
    u32 u32Rate;
    u32 u32RoundRate;
}HalCamClkGetComplexRoundRate_t;
typedef struct
{
    u8 bEn;
}HalCamClkComplexOnOff_t;
#endif /* MHAL_DIP_H */
