// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_SIM_H_
#define INCLUDE_HW_SIM_H_

#include "hw/common.h"
#include "types.h"

/** SIM - Register Layout Typedef */
typedef struct {
	/// System Options Register 1
	__IO uint32_t SOPT1;
	uint8_t RESERVED_0[4096];
	/// System Options Register 2
	__IO uint32_t SOPT2;
	uint8_t RESERVED_1[4];
	/// System Options Register 4
	__IO uint32_t SOPT4;
	/// System Options Register 5
	__IO uint32_t SOPT5;
	uint8_t RESERVED_2[4];
	/// System Options Register 7
	__IO uint32_t SOPT7;
	/// System Options Register 8
	__IO uint32_t SOPT8;
	/// System Options Register 9
	__IO uint32_t SOPT9;
	/// System Device Identification Register
	__I uint32_t SDID;__IO uint32_t SCGC1; /**< System Clock Gating Control Register 1, offset: 0x1028 */
	__IO uint32_t SCGC2; /**< System Clock Gating Control Register 2, offset: 0x102C */
	__IO uint32_t SCGC3; /**< System Clock Gating Control Register 3, offset: 0x1030 */
	__IO uint32_t SCGC4; /**< System Clock Gating Control Register 4, offset: 0x1034 */
	__IO uint32_t SCGC5; /**< System Clock Gating Control Register 5, offset: 0x1038 */
	__IO uint32_t SCGC6; /**< System Clock Gating Control Register 6, offset: 0x103C */
	__IO uint32_t SCGC7; /**< System Clock Gating Control Register 7, offset: 0x1040 */
	__IO uint32_t CLKDIV1; /**< System Clock Divider Register 1, offset: 0x1044 */
	uint8_t RESERVED_3[4];__IO uint32_t FCFG1; /**< Flash Configuration Register 1, offset: 0x104C */
	__I uint32_t FCFG2; /**< Flash Configuration Register 2, offset: 0x1050 */
	__I uint32_t UIDH; /**< Unique Identification Register High, offset: 0x1054 */
	__I uint32_t UIDMH; /**< Unique Identification Register Mid-High, offset: 0x1058 */
	__I uint32_t UIDML; /**< Unique Identification Register Mid Low, offset: 0x105C */
	__I uint32_t UIDL; /**< Unique Identification Register Low, offset: 0x1060 */
	uint8_t RESERVED_4[4];__IO uint32_t CLKDIV4; /**< System Clock Divider Register 4, offset: 0x1068 */
	__IO uint32_t MISCTRL0; /**< Miscellaneous Control Register 0, offset: 0x106C */
	__IO uint32_t MISCTRL1; /**< Miscellaneous Control Register 1, offset: 0x1070 */
	uint8_t RESERVED_5[140];__IO uint32_t WDOGC; /**< WDOG Control Register, offset: 0x1100 */
	__IO uint32_t PWRC; /**< Power Control Register, offset: 0x1104 */
	__IO uint32_t ADCOPT; /**< ADC Additional Option Register, offset: 0x1108 */
} hw_sim_t;

enum {
	SIM_SOPT1_OSC32KSEL_Shift = 18,
	SIM_SOPT1_OSC32KSEL_Mask = 3 << SIM_SOPT1_OSC32KSEL_Shift,
	SIM_SOPT1_OSC32KSEL_OSC32KCLK = 0 << SIM_SOPT1_OSC32KSEL_Shift,
	SIM_SOPT1_OSC32KSEL_LPO = 3 << SIM_SOPT1_OSC32KSEL_Shift,

	SIM_SOPT2_PLLFLLSEL_Shift = 16,
	SIM_SOPT2_PLLFLLSEL_Mask = 3 << SIM_SOPT2_PLLFLLSEL_Shift,
	SIM_SOPT2_PLLFLLSEL_MCGFLLCLK = 0 << SIM_SOPT2_PLLFLLSEL_Shift,
	SIM_SOPT2_PLLFLLSEL_MCGPLLCLK = 1 << SIM_SOPT2_PLLFLLSEL_Shift,

	SIM_SOPT5_UART0TXSR_Mask = 3,
	SIM_SOPT5_UART0RXSR_Shift = 2,
	SIM_SOPT5_UART0RXSR_Mask = 3 << SIM_SOPT5_UART0RXSR_Shift,
	SIM_SOPT5_UART1TXSR_Shift = 4,
	SIM_SOPT5_UART1TXSR_Mask = 3 << SIM_SOPT5_UART1TXSR_Shift,
	SIM_SOPT5_UART1RXSR_Shift = 6,
	SIM_SOPT5_UART1RXSR_Mask = 3 << SIM_SOPT5_UART1RXSR_Shift,

	SIM_SCGC4_I2C0_Shift = 6,
	SIM_SCGC4_I2C0_Mask = 1 << SIM_SCGC4_I2C0_Shift,
	SIM_SCGC4_I2C1_Shift = 7,
	SIM_SCGC4_I2C1_Mask = 1 << SIM_SCGC4_I2C1_Shift,
	SIM_SCGC4_Uart0_Shift = 10,
	SIM_SCGC4_Uart0_Mask = 1 << SIM_SCGC4_Uart0_Shift,
	SIM_SCGC4_Uart1_Shift = 11,
	SIM_SCGC4_Uart1_Mask = 1 << SIM_SCGC4_Uart1_Shift,
	SIM_SCGC4_Uart2_Shift = 12,
	SIM_SCGC4_Uart2_Mask = 1 << SIM_SCGC4_Uart2_Shift,
	SIM_SCGC4_Uart3_Shift = 13,
	SIM_SCGC4_Uart3_Mask = 1 << SIM_SCGC4_Uart3_Shift,

	// Ports
	SIM_SCGC5_PORTA_Shift = 9,
	SIM_SCGC5_PORTA_Mask = 1 << SIM_SCGC5_PORTA_Shift,
	SIM_SCGC5_PORTB_Shift = 10,
	SIM_SCGC5_PORTB_Mask = 1 << SIM_SCGC5_PORTB_Shift,
	SIM_SCGC5_PORTC_Shift = 11,
	SIM_SCGC5_PORTC_Mask = 1 << SIM_SCGC5_PORTC_Shift,
	SIM_SCGC5_PORTD_Shift = 12,
	SIM_SCGC5_PORTD_Mask = 1 << SIM_SCGC5_PORTD_Shift,
	SIM_SCGC5_PORTE_Shift = 13,
	SIM_SCGC5_PORTE_Mask = 1 << SIM_SCGC5_PORTE_Shift,

	SIM_SCGC6_ADC0_Shift = 27,
	SIM_SCGC6_ADC0_Mask = 1 << SIM_SCGC6_ADC0_Shift,

	// FTMs
	SIM_SCGC6_FTM0_Shift = 24,
	SIM_SCGC6_FTM0_Mask = 1 << SIM_SCGC6_FTM0_Shift,
	SIM_SCGC6_FTM1_Shift = 25,
	SIM_SCGC6_FTM1_Mask = 1 << SIM_SCGC6_FTM1_Shift,
	SIM_SCGC6_FTM2_Shift = 26,
	SIM_SCGC6_FTM2_Mask = 1 << SIM_SCGC6_FTM2_Shift,
	SIM_SCGC6_FTM3_Shift = 6,
	SIM_SCGC6_FTM3_Mask = 1 << SIM_SCGC6_FTM3_Shift,

	// FlexCAN
	SIM_SCGC6_FLEXCAN0_Shift = 4,
	SIM_SCGC6_FLEXCAN0_Mask = 1 << SIM_SCGC6_FLEXCAN0_Shift,
	SIM_SCGC6_FLEXCAN1_Shift = 5,
	SIM_SCGC6_FLEXCAN1_Mask = 1 << SIM_SCGC6_FLEXCAN1_Shift,

	// SPI
	SIM_SCGC6_SPI0_Shift = 4,
	SIM_SCGC6_SPI0_Mask = 1 << SIM_SCGC6_SPI0_Shift,
	SIM_SCGC6_SPI1_Shift = 5,
	SIM_SCGC6_SPI1_Mask = 1 << SIM_SCGC6_SPI1_Shift,

	SIM_SCGC6_DMAMUX_Shift = 1,
	SIM_SCGC6_DMAMUX_Mask = 1 << SIM_SCGC6_DMAMUX_Shift,
	SIM_SCGC6_FTF_Mask = 1,

	SIM_SCGC6_DMA_Shift = 8,
	SIM_SCGC6_DMA_Mask = 1 << SIM_SCGC6_DMA_Shift,

	SIM_CLKDIV1_OUTDIV1_Shift = 28,
	SIM_CLKDIV1_OUTDIV1_Mask = 0xF << SIM_CLKDIV1_OUTDIV1_Shift,
	SIM_CLKDIV1_OUTDIV2_Shift = 24,
	SIM_CLKDIV1_OUTDIV2_Mask = 0xF << SIM_CLKDIV1_OUTDIV2_Shift,
	SIM_CLKDIV1_OUTDIV3_Shift = 20,
	SIM_CLKDIV1_OUTDIV3_Mask = 0xF << SIM_CLKDIV1_OUTDIV3_Shift,
	SIM_CLKDIV1_OUTDIV4_Shift = 16,
	SIM_CLKDIV1_OUTDIV4_Mask = 0xF << SIM_CLKDIV1_OUTDIV4_Shift,
} hm_sim_fields_t;

hw_sim_t * const hw_sim = (hw_sim_t *) Memmap_SIM_Addr;

#endif /* INCLUDE_HW_SIM_H_ */
