#include "pinctrl.h"
#include "pinctrl_osdep.h"
#include "board_config.h"

/* PINCTRL_FUNC */
PINCTRL_FUNC(GPIO19, 0, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(UART1_TX, 0, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(GPIO20, 1, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(UART1_RX, 1, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(GPIO21, 2, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(I2C1_SDA, 2, FUNC1, PUPD_NONE, 3);
PINCTRL_FUNC(GPIO25, 3, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI1_TXD, 3, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI2_TXD, 3, FUNC2, PUPD_DOWN, 3);
PINCTRL_FUNC(GPIO26, 4, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI1_RXD, 4, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI2_RXD, 4, FUNC2, PUPD_DOWN, 3);
PINCTRL_FUNC(GPIO27, 5, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI1_CLK, 5, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI2_CLK, 5, FUNC2, PUPD_DOWN, 3);
PINCTRL_FUNC(GPIO28, 6, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI1_CSN_0, 6, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI2_CSN, 6, FUNC2, PUPD_DOWN, 3);
PINCTRL_FUNC(USB_DBG_CLK, 6, FUNC3, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI0_D2, 7, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO50, 7, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(I2C1_SDA, 7, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(UART1_TX, 7, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI0_D3, 8, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO51, 8, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(I2C1_SCL, 8, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(UART1_RX, 8, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(GPIO22, 9, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(I2C1_SCL, 9, FUNC1, PUPD_NONE, 3);
PINCTRL_FUNC(GPIO23, 10, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(AC_MCLK, 10, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(GPIO24, 11, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(USB_PWREN, 11, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(MAC_RMII_CLK, 15, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO15, 15, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_CLK, 15, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM0, 15, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_CLK, 15, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_CLK, 15, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(MAC_REF_CLK, 16, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(MAC_MDC, 17, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO34, 17, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_WP, 17, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(RTC_CLK, 17, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(AC_MCLK, 17, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(USB_PWREN, 17, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(MAC_MDIO, 18, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO17, 18, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(ARM_JTAG_TDO, 18, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM7, 18, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(MAC_RXD_0, 22, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO16, 22, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_0, 22, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM1, 22, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_RXD, 22, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_RXD, 22, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(MAC_RXD_1, 23, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO38, 23, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_1, 23, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM2, 23, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_CSN_0, 23, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_CSN, 23, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(MAC_RXDV, 26, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO41, 26, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_CD, 26, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM3, 26, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(MAC_TXD_0, 28, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO42, 28, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_2, 28, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM4, 28, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(MAC_TXD_1, 29, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO43, 29, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_3, 29, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM5, 29, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_CSN_0, 29, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_CSN, 29, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(MAC_TXEN, 32, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO46, 32, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD1_CMD_RSP, 32, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM6, 32, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_TXD, 32, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_TXD, 32, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(ARM_JTAG_TRSTN, 35, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO0, 35, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_TXD, 35, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_TXD, 35, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(AC_I2S_DO, 35, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(DW_I2S_DO, 35, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(ACIP_ADDAT, 35, FUNC6, PUPD_UP, 3);
PINCTRL_FUNC(ARM_JTAG_TMS, 36, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO1, 36, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_RXD, 36, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_RXD, 36, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(AC_I2S_DI, 36, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(DW_I2S_DI, 36, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(ARM_JTAG_TCK, 37, FUNC0, PUPD_DOWN, 3);
PINCTRL_FUNC(GPIO2, 37, FUNC1, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI1_CLK, 37, FUNC2, PUPD_DOWN, 3);
PINCTRL_FUNC(SSI2_CLK, 37, FUNC3, PUPD_DOWN, 3);
PINCTRL_FUNC(AC_I2S_CLK, 37, FUNC4, PUPD_DOWN, 3);
PINCTRL_FUNC(DW_I2S_CLK, 37, FUNC5, PUPD_DOWN, 3);
PINCTRL_FUNC(ACIP_BCLK, 37, FUNC6, PUPD_DOWN, 3);
PINCTRL_FUNC(ARM_JTAG_TDI, 38, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO3, 38, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_CSN_0, 38, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(SSI2_CSN, 38, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(AC_I2S_WS, 38, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(DW_I2S_WS, 38, FUNC5, PUPD_UP, 3);
PINCTRL_FUNC(ACIP_ADLRC, 38, FUNC6, PUPD_UP, 3);
PINCTRL_FUNC(GPIO4, 39, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_CLK, 39, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM0, 39, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO5, 40, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_0, 40, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM1, 40, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO6, 41, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_1, 41, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM2, 41, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO7, 42, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_CD, 42, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM3, 42, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO8, 43, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_2, 43, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM4, 43, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO9, 44, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_DATA_3, 44, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM5, 44, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO10, 45, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_CMD_RSP, 45, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM6, 45, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(GPIO11, 46, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD1_WP, 46, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM7, 46, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM0, 47, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO12, 47, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(CIS_CLK, 47, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PWM1, 48, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO13, 48, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(PWM2, 49, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO14, 49, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(UART0_RX, 50, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO48, 50, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(UART0_TX, 51, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO49, 51, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(I2C0_SCL, 52, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(GPIO57, 52, FUNC1, PUPD_NONE, 3);
PINCTRL_FUNC(I2C0_SDA, 53, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(GPIO56, 53, FUNC1, PUPD_NONE, 3);
PINCTRL_FUNC(SSI0_CLK, 56, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(SSI0_TXD, 57, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SSI0_CSN_0, 58, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO54, 58, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SSI0_CSN_1, 59, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO55, 59, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SSI0_RXD, 60, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(SD0_CD, 61, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO52, 61, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(ARC_JTAG_TRSTN, 61, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PAE_JTAG_TRSTN, 61, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SD0_WP, 62, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO53, 62, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(SD0_CLK, 63, FUNC0, PUPD_NONE, 3);
PINCTRL_FUNC(GPIO63, 63, FUNC1, PUPD_NONE, 3);
PINCTRL_FUNC(ARC_JTAG_TMS, 63, FUNC2, PUPD_NONE, 3);
PINCTRL_FUNC(PAE_JTAG_TMS, 63, FUNC3, PUPD_NONE, 3);
PINCTRL_FUNC(SSI1_CLK, 63, FUNC4, PUPD_NONE, 3);
PINCTRL_FUNC(SD0_CMD_RSP, 64, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO29, 64, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(ARC_JTAG_TCK, 64, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PAE_JTAG_TCK, 64, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_TXD, 64, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SD0_DATA_0, 65, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO62, 65, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(ARC_JTAG_TDI, 65, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(PAE_JTAG_TDI, 65, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_RXD, 65, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SD0_DATA_1, 66, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO61, 66, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(USB_PWREN, 66, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(AC_MCLK, 66, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_CSN_0, 66, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SD0_DATA_2, 67, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO60, 67, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(I2C1_SDA, 67, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(UART1_TX, 67, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(ARC_JTAG_TDO, 67, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SD0_DATA_3, 68, FUNC0, PUPD_UP, 3);
PINCTRL_FUNC(GPIO18, 68, FUNC1, PUPD_UP, 3);
PINCTRL_FUNC(I2C1_SCL, 68, FUNC2, PUPD_UP, 3);
PINCTRL_FUNC(UART1_RX, 68, FUNC3, PUPD_UP, 3);
PINCTRL_FUNC(PAE_JTAG_TDO, 68, FUNC4, PUPD_UP, 3);
PINCTRL_FUNC(SSI1_CSN_0, 68, FUNC5, PUPD_UP, 3);


/* PINCTRL_MUX */

PINCTRL_MUX(ACIP_ADDAT, 0, &PAD35_ACIP_ADDAT);
PINCTRL_MUX(ACIP_ADLRC, 0, &PAD38_ACIP_ADLRC);
PINCTRL_MUX(ACIP_BCLK, 0, &PAD37_ACIP_BCLK);

PINCTRL_MUX(AC_I2S_CLK, 0, &PAD37_AC_I2S_CLK);
PINCTRL_MUX(AC_I2S_DI, 0, &PAD36_AC_I2S_DI);
PINCTRL_MUX(AC_I2S_DO, 0, &PAD35_AC_I2S_DO);
PINCTRL_MUX(AC_I2S_WS, 0, &PAD38_AC_I2S_WS);
PINCTRL_MUX(AC_MCLK, 2, &PAD10_AC_MCLK, &PAD17_AC_MCLK, &PAD66_AC_MCLK);

PINCTRL_MUX(ARC_JTAG_TCK, 0, &PAD64_ARC_JTAG_TCK);
PINCTRL_MUX(ARC_JTAG_TDI, 0, &PAD65_ARC_JTAG_TDI);
PINCTRL_MUX(ARC_JTAG_TDO, 0, &PAD67_ARC_JTAG_TDO);
PINCTRL_MUX(ARC_JTAG_TMS, 0, &PAD63_ARC_JTAG_TMS);
PINCTRL_MUX(ARC_JTAG_TRSTN, 0, &PAD61_ARC_JTAG_TRSTN);

PINCTRL_MUX(ARM_JTAG_TCK, 0, &PAD37_ARM_JTAG_TCK);
PINCTRL_MUX(ARM_JTAG_TDI, 0, &PAD38_ARM_JTAG_TDI);
PINCTRL_MUX(ARM_JTAG_TDO, 0, &PAD18_ARM_JTAG_TDO);
PINCTRL_MUX(ARM_JTAG_TMS, 0, &PAD36_ARM_JTAG_TMS);
PINCTRL_MUX(ARM_JTAG_TRSTN, 0, &PAD35_ARM_JTAG_TRSTN);

PINCTRL_MUX(CIS_CLK, 0, &PAD47_CIS_CLK);

PINCTRL_MUX(DW_I2S_CLK, 0, &PAD37_DW_I2S_CLK);
PINCTRL_MUX(DW_I2S_DI, 0, &PAD36_DW_I2S_DI);
PINCTRL_MUX(DW_I2S_DO, 0, &PAD35_DW_I2S_DO);
PINCTRL_MUX(DW_I2S_WS, 0, &PAD38_DW_I2S_WS);

PINCTRL_MUX(I2C0_SCL, 0, &PAD52_I2C0_SCL);
PINCTRL_MUX(I2C0_SDA, 0, &PAD53_I2C0_SDA);

PINCTRL_MUX(I2C1_SCL, 2, &PAD8_I2C1_SCL, &PAD9_I2C1_SCL, &PAD68_I2C1_SCL);
PINCTRL_MUX(I2C1_SDA, 2, &PAD2_I2C1_SDA, &PAD7_I2C1_SDA, &PAD67_I2C1_SDA);

PINCTRL_MUX(MAC_MDC, 0, &PAD17_MAC_MDC);
PINCTRL_MUX(MAC_MDIO, 0, &PAD18_MAC_MDIO);
PINCTRL_MUX(MAC_REF_CLK, 0, &PAD16_MAC_REF_CLK);
PINCTRL_MUX(MAC_RMII_CLK, 0, &PAD15_MAC_RMII_CLK);
PINCTRL_MUX(MAC_RXDV, 0, &PAD26_MAC_RXDV);
PINCTRL_MUX(MAC_RXD_0, 0, &PAD22_MAC_RXD_0);
PINCTRL_MUX(MAC_RXD_1, 0, &PAD23_MAC_RXD_1);
PINCTRL_MUX(MAC_TXD_0, 0, &PAD28_MAC_TXD_0);
PINCTRL_MUX(MAC_TXD_1, 0, &PAD29_MAC_TXD_1);
PINCTRL_MUX(MAC_TXEN, 0, &PAD32_MAC_TXEN);

PINCTRL_MUX(PAE_JTAG_TCK, 0, &PAD64_PAE_JTAG_TCK);
PINCTRL_MUX(PAE_JTAG_TDI, 0, &PAD65_PAE_JTAG_TDI);
PINCTRL_MUX(PAE_JTAG_TDO, 0, &PAD68_PAE_JTAG_TDO);
PINCTRL_MUX(PAE_JTAG_TMS, 0, &PAD63_PAE_JTAG_TMS);
PINCTRL_MUX(PAE_JTAG_TRSTN, 0, &PAD61_PAE_JTAG_TRSTN);

PINCTRL_MUX(PWM0, 0, &PAD15_PWM0, &PAD39_PWM0, &PAD47_PWM0);
PINCTRL_MUX(PWM1, 0, &PAD22_PWM1, &PAD40_PWM1, &PAD48_PWM1);
PINCTRL_MUX(PWM2, 0, &PAD23_PWM2, &PAD41_PWM2, &PAD49_PWM2);
PINCTRL_MUX(PWM3, 0, &PAD26_PWM3, &PAD42_PWM3);
PINCTRL_MUX(PWM4, 0, &PAD28_PWM4, &PAD43_PWM4);
PINCTRL_MUX(PWM5, 0, &PAD29_PWM5, &PAD44_PWM5);
PINCTRL_MUX(PWM6, 0, &PAD32_PWM6, &PAD45_PWM6);
PINCTRL_MUX(PWM7, 0, &PAD18_PWM7, &PAD46_PWM7);

PINCTRL_MUX(RTC_CLK, 0, &PAD17_RTC_CLK);

PINCTRL_MUX(SD0_CD, 0, &PAD61_SD0_CD);
PINCTRL_MUX(SD0_CLK, 0, &PAD63_SD0_CLK);
PINCTRL_MUX(SD0_CMD_RSP, 0, &PAD64_SD0_CMD_RSP);
PINCTRL_MUX(SD0_DATA_0, 0, &PAD65_SD0_DATA_0);
PINCTRL_MUX(SD0_DATA_1, 0, &PAD66_SD0_DATA_1);
PINCTRL_MUX(SD0_DATA_2, 0, &PAD67_SD0_DATA_2);
PINCTRL_MUX(SD0_DATA_3, 0, &PAD68_SD0_DATA_3);
PINCTRL_MUX(SD0_WP, 0, &PAD62_SD0_WP);

PINCTRL_MUX(SD1_CD, 0, &PAD26_SD1_CD, &PAD42_SD1_CD);
PINCTRL_MUX(SD1_CLK, 0, &PAD15_SD1_CLK, &PAD39_SD1_CLK);
PINCTRL_MUX(SD1_CMD_RSP, 0, &PAD32_SD1_CMD_RSP, &PAD45_SD1_CMD_RSP);
PINCTRL_MUX(SD1_DATA_0, 0, &PAD22_SD1_DATA_0, &PAD40_SD1_DATA_0);
PINCTRL_MUX(SD1_DATA_1, 0, &PAD23_SD1_DATA_1, &PAD41_SD1_DATA_1);
PINCTRL_MUX(SD1_DATA_2, 0, &PAD28_SD1_DATA_2, &PAD43_SD1_DATA_2);
PINCTRL_MUX(SD1_DATA_3, 0, &PAD29_SD1_DATA_3, &PAD44_SD1_DATA_3);
PINCTRL_MUX(SD1_WP, 0, &PAD17_SD1_WP, &PAD46_SD1_WP);

PINCTRL_MUX(SSI0_CLK, 0, &PAD56_SSI0_CLK);
PINCTRL_MUX(SSI0_CSN_0, 0, &PAD58_SSI0_CSN_0);
PINCTRL_MUX(SSI0_CSN_1, 0, &PAD59_SSI0_CSN_1);
PINCTRL_MUX(SSI0_D2, 0, &PAD7_SSI0_D2);
PINCTRL_MUX(SSI0_D3, 0, &PAD8_SSI0_D3);
PINCTRL_MUX(SSI0_RXD, 0, &PAD60_SSI0_RXD);
PINCTRL_MUX(SSI0_TXD, 0, &PAD57_SSI0_TXD);

PINCTRL_MUX(SSI1_CLK, 2, &PAD5_SSI1_CLK, &PAD15_SSI1_CLK, &PAD37_SSI1_CLK,
		&PAD63_SSI1_CLK);
PINCTRL_MUX(SSI1_CSN_0, 3, &PAD6_SSI1_CSN_0, &PAD23_SSI1_CSN_0,
		&PAD29_SSI1_CSN_0, &PAD38_SSI1_CSN_0, &PAD66_SSI1_CSN_0,
		&PAD68_SSI1_CSN_0);
PINCTRL_MUX(SSI1_RXD, 2, &PAD4_SSI1_RXD, &PAD22_SSI1_RXD, &PAD36_SSI1_RXD,
		&PAD65_SSI1_RXD);
PINCTRL_MUX(SSI1_TXD, 2, &PAD3_SSI1_TXD, &PAD32_SSI1_TXD, &PAD35_SSI1_TXD,
		&PAD64_SSI1_TXD);

PINCTRL_MUX(SSI2_CLK, 2, &PAD5_SSI2_CLK, &PAD15_SSI2_CLK, &PAD37_SSI2_CLK);
PINCTRL_MUX(SSI2_CSN, 3, &PAD6_SSI2_CSN, &PAD23_SSI2_CSN, &PAD29_SSI2_CSN,
		&PAD38_SSI2_CSN);
PINCTRL_MUX(SSI2_RXD, 2, &PAD4_SSI2_RXD, &PAD22_SSI2_RXD, &PAD36_SSI2_RXD);
PINCTRL_MUX(SSI2_TXD, 2, &PAD3_SSI2_TXD, &PAD32_SSI2_TXD, &PAD35_SSI2_TXD);

PINCTRL_MUX(UART0_RX, 0, &PAD50_UART0_RX);
PINCTRL_MUX(UART0_TX, 0, &PAD51_UART0_TX);

PINCTRL_MUX(UART1_RX, 1, &PAD1_UART1_RX, &PAD8_UART1_RX, &PAD68_UART1_RX);
PINCTRL_MUX(UART1_TX, 1, &PAD0_UART1_TX, &PAD7_UART1_TX, &PAD67_UART1_TX);

PINCTRL_MUX(USB_DBG_CLK, 0, &PAD6_USB_DBG_CLK);
PINCTRL_MUX(USB_PWREN, 1, &PAD11_USB_PWREN, &PAD17_USB_PWREN, &PAD66_USB_PWREN);

PINCTRL_MUX(GPIO0, 0, &PAD35_GPIO0);
PINCTRL_MUX(GPIO1, 0, &PAD36_GPIO1);
PINCTRL_MUX(GPIO2, 0, &PAD37_GPIO2);
PINCTRL_MUX(GPIO3, 0, &PAD38_GPIO3);
PINCTRL_MUX(GPIO4, 0, &PAD39_GPIO4);
PINCTRL_MUX(GPIO5, 0, &PAD40_GPIO5);
PINCTRL_MUX(GPIO6, 0, &PAD41_GPIO6);
PINCTRL_MUX(GPIO7, 0, &PAD42_GPIO7);
PINCTRL_MUX(GPIO8, 0, &PAD43_GPIO8);
PINCTRL_MUX(GPIO9, 0, &PAD44_GPIO9);
PINCTRL_MUX(GPIO10, 0, &PAD45_GPIO10);
PINCTRL_MUX(GPIO11, 0, &PAD46_GPIO11);
PINCTRL_MUX(GPIO12, 0, &PAD47_GPIO12);
PINCTRL_MUX(GPIO13, 0, &PAD48_GPIO13);
PINCTRL_MUX(GPIO14, 0, &PAD49_GPIO14);
PINCTRL_MUX(GPIO15, 0, &PAD15_GPIO15);
PINCTRL_MUX(GPIO16, 0, &PAD22_GPIO16);
PINCTRL_MUX(GPIO17, 0, &PAD18_GPIO17);
PINCTRL_MUX(GPIO18, 0, &PAD68_GPIO18);
PINCTRL_MUX(GPIO19, 0, &PAD0_GPIO19);
PINCTRL_MUX(GPIO20, 0, &PAD1_GPIO20);
PINCTRL_MUX(GPIO21, 0, &PAD2_GPIO21);
PINCTRL_MUX(GPIO22, 0, &PAD9_GPIO22);
PINCTRL_MUX(GPIO23, 0, &PAD10_GPIO23);
PINCTRL_MUX(GPIO24, 0, &PAD11_GPIO24);
PINCTRL_MUX(GPIO25, 0, &PAD3_GPIO25);
PINCTRL_MUX(GPIO26, 0, &PAD4_GPIO26);
PINCTRL_MUX(GPIO27, 0, &PAD5_GPIO27);
PINCTRL_MUX(GPIO28, 0, &PAD6_GPIO28);
PINCTRL_MUX(GPIO29, 0, &PAD64_GPIO29);
PINCTRL_MUX(GPIO34, 0, &PAD17_GPIO34);
PINCTRL_MUX(GPIO38, 0, &PAD23_GPIO38);
PINCTRL_MUX(GPIO41, 0, &PAD26_GPIO41);
PINCTRL_MUX(GPIO42, 0, &PAD28_GPIO42);
PINCTRL_MUX(GPIO43, 0, &PAD29_GPIO43);
PINCTRL_MUX(GPIO46, 0, &PAD32_GPIO46);
PINCTRL_MUX(GPIO48, 0, &PAD50_GPIO48);
PINCTRL_MUX(GPIO49, 0, &PAD51_GPIO49);
PINCTRL_MUX(GPIO50, 0, &PAD7_GPIO50);
PINCTRL_MUX(GPIO51, 0, &PAD8_GPIO51);
PINCTRL_MUX(GPIO52, 0, &PAD61_GPIO52);
PINCTRL_MUX(GPIO53, 0, &PAD62_GPIO53);
PINCTRL_MUX(GPIO54, 0, &PAD58_GPIO54);
PINCTRL_MUX(GPIO55, 0, &PAD59_GPIO55);
PINCTRL_MUX(GPIO56, 0, &PAD53_GPIO56);
PINCTRL_MUX(GPIO57, 0, &PAD52_GPIO57);
PINCTRL_MUX(GPIO60, 0, &PAD67_GPIO60);
PINCTRL_MUX(GPIO61, 0, &PAD66_GPIO61);
PINCTRL_MUX(GPIO62, 0, &PAD65_GPIO62);
PINCTRL_MUX(GPIO63, 0, &PAD63_GPIO63);

PINCTRL_MUX(SD1_CLK_RMII, 0, &PAD15_SD1_CLK, &PAD39_SD1_CLK);
PINCTRL_MUX(SD1_CD_RMII, 0, &PAD26_SD1_CD, &PAD42_SD1_CD);
PINCTRL_MUX(SD1_CMD_RSP_RMII, 0, &PAD32_SD1_CMD_RSP, &PAD45_SD1_CMD_RSP);
PINCTRL_MUX(SD1_WP_RMII, 0, &PAD17_SD1_WP, &PAD46_SD1_WP);
PINCTRL_MUX(SD1_DATA_0_RMII, 0, &PAD22_SD1_DATA_0, &PAD40_SD1_DATA_0);
PINCTRL_MUX(SD1_DATA_1_RMII, 0, &PAD23_SD1_DATA_1, &PAD41_SD1_DATA_1);
PINCTRL_MUX(SD1_DATA_2_RMII, 0, &PAD28_SD1_DATA_2, &PAD43_SD1_DATA_2);
PINCTRL_MUX(SD1_DATA_3_RMII, 0, &PAD29_SD1_DATA_3, &PAD44_SD1_DATA_3);

/* PINCTRL_DEVICE */
PINCTRL_DEVICE(ACI2S, 5, &MUX_AC_I2S_CLK, &MUX_AC_I2S_DI, &MUX_AC_I2S_DO,
		&MUX_AC_I2S_WS, &MUX_AC_MCLK);
PINCTRL_DEVICE(ACIP, 3, &MUX_ACIP_ADDAT, &MUX_ACIP_ADLRC, &MUX_ACIP_BCLK);
PINCTRL_DEVICE(ARCJTAG, 5, &MUX_ARC_JTAG_TCK, &MUX_ARC_JTAG_TDI,
		&MUX_ARC_JTAG_TDO, &MUX_ARC_JTAG_TMS, &MUX_ARC_JTAG_TRSTN);
PINCTRL_DEVICE(ARMJTAG, 5, &MUX_ARM_JTAG_TCK, &MUX_ARM_JTAG_TDI,
		&MUX_ARM_JTAG_TDO, &MUX_ARM_JTAG_TMS, &MUX_ARM_JTAG_TRSTN);
PINCTRL_DEVICE(DWI2S, 4, &MUX_DW_I2S_CLK, &MUX_DW_I2S_DI, &MUX_DW_I2S_DO,
		&MUX_DW_I2S_WS);
PINCTRL_DEVICE(I2C0, 2, &MUX_I2C0_SCL, &MUX_I2C0_SDA);
PINCTRL_DEVICE(I2C1, 2, &MUX_I2C1_SCL, &MUX_I2C1_SDA);
PINCTRL_DEVICE(MIPI, 1, &MUX_CIS_CLK);
PINCTRL_DEVICE(PAEJTAG, 5, &MUX_PAE_JTAG_TCK, &MUX_PAE_JTAG_TDI,
		&MUX_PAE_JTAG_TDO, &MUX_PAE_JTAG_TMS, &MUX_PAE_JTAG_TRSTN);
PINCTRL_DEVICE(PWM0, 1, &MUX_PWM0);
PINCTRL_DEVICE(PWM1, 1, &MUX_PWM1);
PINCTRL_DEVICE(PWM2, 1, &MUX_PWM2);
PINCTRL_DEVICE(PWM3, 1, &MUX_PWM3);
PINCTRL_DEVICE(PWM4, 1, &MUX_PWM4);
PINCTRL_DEVICE(PWM5, 1, &MUX_PWM5);
PINCTRL_DEVICE(PWM6, 1, &MUX_PWM6);
PINCTRL_DEVICE(PWM7, 1, &MUX_PWM7);
PINCTRL_DEVICE(RMII, 10, &MUX_MAC_MDC, &MUX_MAC_MDIO, &MUX_MAC_REF_CLK,
		&MUX_MAC_RMII_CLK, &MUX_MAC_RXDV, &MUX_MAC_RXD_0, &MUX_MAC_RXD_1,
		&MUX_MAC_TXD_0, &MUX_MAC_TXD_1, &MUX_MAC_TXEN);
PINCTRL_DEVICE(SD0, 8, &MUX_SD0_CD, &MUX_SD0_CLK, &MUX_SD0_CMD_RSP,
		&MUX_SD0_DATA_0, &MUX_SD0_DATA_1, &MUX_SD0_DATA_2, &MUX_SD0_DATA_3,
		&MUX_SD0_WP);
PINCTRL_DEVICE(SD0_1BIT_NO_WP, 4, &MUX_SD0_CD, &MUX_SD0_CLK, &MUX_SD0_CMD_RSP,
		&MUX_SD0_DATA_0);
PINCTRL_DEVICE(SD0_NO_WP, 7, &MUX_SD0_CD, &MUX_SD0_CLK, &MUX_SD0_CMD_RSP,
		&MUX_SD0_DATA_0, &MUX_SD0_DATA_1, &MUX_SD0_DATA_2, &MUX_SD0_DATA_3);
PINCTRL_DEVICE(SD1, 8, &MUX_SD1_CD, &MUX_SD1_CLK, &MUX_SD1_CMD_RSP,
		&MUX_SD1_DATA_0, &MUX_SD1_DATA_1, &MUX_SD1_DATA_2, &MUX_SD1_DATA_3,
		&MUX_SD1_WP);
PINCTRL_DEVICE(SD1_NO_WP, 7, &MUX_SD1_CD, &MUX_SD1_CLK, &MUX_SD1_CMD_RSP,
		&MUX_SD1_DATA_0, &MUX_SD1_DATA_1, &MUX_SD1_DATA_2, &MUX_SD1_DATA_3);
PINCTRL_DEVICE(SSI0, 4, &MUX_GPIO54, &MUX_SSI0_CLK, &MUX_SSI0_RXD,
		&MUX_SSI0_TXD);
PINCTRL_DEVICE(SSI0_4BIT, 6, &MUX_GPIO54, &MUX_SSI0_CLK, &MUX_SSI0_D2,
		&MUX_SSI0_D3, &MUX_SSI0_RXD, &MUX_SSI0_TXD);
PINCTRL_DEVICE(SSI1, 4, &MUX_SSI1_CLK, &MUX_SSI1_CSN_0, &MUX_SSI1_RXD,
		&MUX_SSI1_TXD);
PINCTRL_DEVICE(SSI2, 4, &MUX_SSI2_CLK, &MUX_SSI2_CSN, &MUX_SSI2_RXD,
		&MUX_SSI2_TXD);
PINCTRL_DEVICE(UART0, 2, &MUX_UART0_RX, &MUX_UART0_TX);
PINCTRL_DEVICE(UART1, 2, &MUX_UART1_RX, &MUX_UART1_TX);
PINCTRL_DEVICE(USB, 1, &MUX_USB_PWREN);
PINCTRL_DEVICE(GPIO0, 1, &MUX_GPIO0);
PINCTRL_DEVICE(GPIO1, 1, &MUX_GPIO1);
PINCTRL_DEVICE(GPIO2, 1, &MUX_GPIO2);
PINCTRL_DEVICE(GPIO3, 1, &MUX_GPIO3);
PINCTRL_DEVICE(GPIO4, 1, &MUX_GPIO4);
PINCTRL_DEVICE(GPIO5, 1, &MUX_GPIO5);
PINCTRL_DEVICE(GPIO6, 1, &MUX_GPIO6);
PINCTRL_DEVICE(GPIO7, 1, &MUX_GPIO7);
PINCTRL_DEVICE(GPIO8, 1, &MUX_GPIO8);
PINCTRL_DEVICE(GPIO9, 1, &MUX_GPIO9);
PINCTRL_DEVICE(GPIO10, 1, &MUX_GPIO10);
PINCTRL_DEVICE(GPIO11, 1, &MUX_GPIO11);
PINCTRL_DEVICE(GPIO12, 1, &MUX_GPIO12);
PINCTRL_DEVICE(GPIO13, 1, &MUX_GPIO13);
PINCTRL_DEVICE(GPIO14, 1, &MUX_GPIO14);
PINCTRL_DEVICE(GPIO15, 1, &MUX_GPIO15);
PINCTRL_DEVICE(GPIO16, 1, &MUX_GPIO16);
PINCTRL_DEVICE(GPIO17, 1, &MUX_GPIO17);
PINCTRL_DEVICE(GPIO18, 1, &MUX_GPIO18);
PINCTRL_DEVICE(GPIO19, 1, &MUX_GPIO19);
PINCTRL_DEVICE(GPIO20, 1, &MUX_GPIO20);
PINCTRL_DEVICE(GPIO21, 1, &MUX_GPIO21);
PINCTRL_DEVICE(GPIO22, 1, &MUX_GPIO22);
PINCTRL_DEVICE(GPIO23, 1, &MUX_GPIO23);
PINCTRL_DEVICE(GPIO24, 1, &MUX_GPIO24);
PINCTRL_DEVICE(GPIO25, 1, &MUX_GPIO25);
PINCTRL_DEVICE(GPIO26, 1, &MUX_GPIO26);
PINCTRL_DEVICE(GPIO27, 1, &MUX_GPIO27);
PINCTRL_DEVICE(GPIO28, 1, &MUX_GPIO28);
PINCTRL_DEVICE(GPIO29, 1, &MUX_GPIO29);
PINCTRL_DEVICE(GPIO34, 1, &MUX_GPIO34);
PINCTRL_DEVICE(GPIO38, 1, &MUX_GPIO38);
PINCTRL_DEVICE(GPIO41, 1, &MUX_GPIO41);
PINCTRL_DEVICE(GPIO42, 1, &MUX_GPIO42);
PINCTRL_DEVICE(GPIO43, 1, &MUX_GPIO43);
PINCTRL_DEVICE(GPIO46, 1, &MUX_GPIO46);
PINCTRL_DEVICE(GPIO48, 1, &MUX_GPIO48);
PINCTRL_DEVICE(GPIO49, 1, &MUX_GPIO49);
PINCTRL_DEVICE(GPIO50, 1, &MUX_GPIO50);
PINCTRL_DEVICE(GPIO51, 1, &MUX_GPIO51);
PINCTRL_DEVICE(GPIO52, 1, &MUX_GPIO52);
PINCTRL_DEVICE(GPIO53, 1, &MUX_GPIO53);
PINCTRL_DEVICE(GPIO54, 1, &MUX_GPIO54);
PINCTRL_DEVICE(GPIO55, 1, &MUX_GPIO55);
PINCTRL_DEVICE(GPIO56, 1, &MUX_GPIO56);
PINCTRL_DEVICE(GPIO57, 1, &MUX_GPIO57);
PINCTRL_DEVICE(GPIO60, 1, &MUX_GPIO60);
PINCTRL_DEVICE(GPIO61, 1, &MUX_GPIO61);
PINCTRL_DEVICE(GPIO62, 1, &MUX_GPIO62);
PINCTRL_DEVICE(GPIO63, 1, &MUX_GPIO63);

PINCTRL_DEVICE(SD1_WIFI_RMII, 7, &MUX_SD1_CLK_RMII, &MUX_SD1_CD_RMII,
		&MUX_SD1_CMD_RSP_RMII, &MUX_SD1_DATA_0_RMII, &MUX_SD1_DATA_1_RMII,
		&MUX_SD1_DATA_2_RMII, &MUX_SD1_DATA_3_RMII);

void fh_pinctrl_init_devicelist(OS_LIST *list)
{
	OS_LIST_EMPTY(list);

	/*PINCTRL_ADD_DEVICE*/
	PINCTRL_ADD_DEVICE(ACI2S);
	PINCTRL_ADD_DEVICE(ACIP);
	PINCTRL_ADD_DEVICE(ARCJTAG);
	PINCTRL_ADD_DEVICE(ARMJTAG);
	PINCTRL_ADD_DEVICE(DWI2S);
	PINCTRL_ADD_DEVICE(I2C0);
	PINCTRL_ADD_DEVICE(I2C1);
	PINCTRL_ADD_DEVICE(MIPI);
	PINCTRL_ADD_DEVICE(PAEJTAG);
	PINCTRL_ADD_DEVICE(PWM0);
	PINCTRL_ADD_DEVICE(PWM1);
	PINCTRL_ADD_DEVICE(PWM2);
	PINCTRL_ADD_DEVICE(PWM3);
	PINCTRL_ADD_DEVICE(PWM4);
	PINCTRL_ADD_DEVICE(PWM5);
	PINCTRL_ADD_DEVICE(PWM6);
	PINCTRL_ADD_DEVICE(PWM7);
	PINCTRL_ADD_DEVICE(RMII);
	PINCTRL_ADD_DEVICE(SD0);
	PINCTRL_ADD_DEVICE(SD0_1BIT_NO_WP);
	PINCTRL_ADD_DEVICE(SD0_NO_WP);
	PINCTRL_ADD_DEVICE(SD1);
	PINCTRL_ADD_DEVICE(SD1_NO_WP);
	PINCTRL_ADD_DEVICE(SSI0);
	PINCTRL_ADD_DEVICE(SSI0_4BIT);
	PINCTRL_ADD_DEVICE(SSI1);
	PINCTRL_ADD_DEVICE(SSI2);
	PINCTRL_ADD_DEVICE(UART0);
	PINCTRL_ADD_DEVICE(UART1);
	PINCTRL_ADD_DEVICE(USB);
	PINCTRL_ADD_DEVICE(GPIO0);
	PINCTRL_ADD_DEVICE(GPIO1);
	PINCTRL_ADD_DEVICE(GPIO2);
	PINCTRL_ADD_DEVICE(GPIO3);
	PINCTRL_ADD_DEVICE(GPIO4);
	PINCTRL_ADD_DEVICE(GPIO5);
	PINCTRL_ADD_DEVICE(GPIO6);
	PINCTRL_ADD_DEVICE(GPIO7);
	PINCTRL_ADD_DEVICE(GPIO8);
	PINCTRL_ADD_DEVICE(GPIO9);
	PINCTRL_ADD_DEVICE(GPIO10);
	PINCTRL_ADD_DEVICE(GPIO11);
	PINCTRL_ADD_DEVICE(GPIO12);
	PINCTRL_ADD_DEVICE(GPIO13);
	PINCTRL_ADD_DEVICE(GPIO14);
	PINCTRL_ADD_DEVICE(GPIO15);
	PINCTRL_ADD_DEVICE(GPIO16);
	PINCTRL_ADD_DEVICE(GPIO17);
	PINCTRL_ADD_DEVICE(GPIO18);
	PINCTRL_ADD_DEVICE(GPIO19);
	PINCTRL_ADD_DEVICE(GPIO20);
	PINCTRL_ADD_DEVICE(GPIO21);
	PINCTRL_ADD_DEVICE(GPIO22);
	PINCTRL_ADD_DEVICE(GPIO23);
	PINCTRL_ADD_DEVICE(GPIO24);
	PINCTRL_ADD_DEVICE(GPIO25);
	PINCTRL_ADD_DEVICE(GPIO26);
	PINCTRL_ADD_DEVICE(GPIO27);
	PINCTRL_ADD_DEVICE(GPIO28);
	PINCTRL_ADD_DEVICE(GPIO29);
	PINCTRL_ADD_DEVICE(GPIO34);
	PINCTRL_ADD_DEVICE(GPIO38);
	PINCTRL_ADD_DEVICE(GPIO41);
	PINCTRL_ADD_DEVICE(GPIO42);
	PINCTRL_ADD_DEVICE(GPIO43);
	PINCTRL_ADD_DEVICE(GPIO46);
	PINCTRL_ADD_DEVICE(GPIO48);
	PINCTRL_ADD_DEVICE(GPIO49);
	PINCTRL_ADD_DEVICE(GPIO50);
	PINCTRL_ADD_DEVICE(GPIO51);
	PINCTRL_ADD_DEVICE(GPIO52);
	PINCTRL_ADD_DEVICE(GPIO53);
	PINCTRL_ADD_DEVICE(GPIO54);
	PINCTRL_ADD_DEVICE(GPIO55);
	PINCTRL_ADD_DEVICE(GPIO56);
	PINCTRL_ADD_DEVICE(GPIO57);
	PINCTRL_ADD_DEVICE(GPIO60);
	PINCTRL_ADD_DEVICE(GPIO61);
	PINCTRL_ADD_DEVICE(GPIO62);
	PINCTRL_ADD_DEVICE(GPIO63);

	PINCTRL_ADD_DEVICE(SD1_WIFI_RMII);
}

char* fh_pinctrl_selected_devices[] =
{
	CONFIG_PINCTRL_SELECT
};
