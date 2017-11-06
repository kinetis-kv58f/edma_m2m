// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_MEMMAP_H_
#define INCLUDE_HW_MEMMAP_H_

#include "types.h"

/// Contains memory map of HW registers in memory
enum {
	/// Peripheral SIM base address
	Memmap_SIM_Addr = 0x40047000u,

	/// Peripheral SIM base address
	Memmap_FTFE_Addr = 0x40020000u,

	Memmap_DMAMUX_Addr = 0x40021000u,

	Memmap_FTM0_Addr = 0x40038000u,

	Memmap_FTM1_Addr = 0x40039000u,

	Memmap_FTM2_Addr = 0x4003A000u,

	Memmap_ADC0_Addr = 0x4003B000,

	Memmap_FTM3_Addr = 0x40026000u,

	Memmap_GPIOA_Addr = 0x400FF000u,

	Memmap_GPIOB_Addr = 0x400FF040u,

	Memmap_GPIOC_Addr = 0x400FF080u,

	Memmap_GPIOD_Addr = 0x400FF0C0u,

	Memmap_GPIOE_Addr = 0x400FF100u,

	Memamp_MCG_Addr = 0x40064000u,

	Memmap_OSC0_Addr = 0x40065000u,

	Memmap_PORTA_Addr = 0x40049000u,

	Memmap_PORTB_Addr = 0x4004A000u,

	Memmap_PORTC_Addr = 0x4004B000u,

	Memmap_PORTD_Addr = 0x4004C000u,

	Memmap_PORTE_Addr = 0x4004D000u,

	Memmap_UART0_Addr = 0x4006A000u,

	Memmap_UART1_Addr = 0x4006B000u,

	Memmap_UART2_Addr = 0x4006C000u,

	Memmap_UART3_Addr = 0x4006D000u,

	Memmap_I2C0_Addr = 0x40066000u,

	Memmap_I2C1_Addr = 0x40067000u,

	Memmap_DMA0_Addr = 0x40008000,

	Memmap_UART4_Addr = 0x400EA000u,

	Memmap_UART5_Addr = 0x400EB000u,

	Memmap_WDOG_Addr = 0x40052000u,

	Memmap_SCS_Addr = 0xE000E000UL,

	Memmap_ITM_Addr = 0xE0000000UL,

	Memmap_DWT_Addr = 0xE0001000UL,

	Memmap_TPI_Addr = 0xE0040000UL,

	Memmap_CoreDebug_Addr = 0xE000EDF0UL,

	Memmap_SysTick_Addr = Memmap_SCS_Addr + 0x0010UL,

	Memmap_NVIC_Addr = Memmap_SCS_Addr + 0x0100UL,

	Memmap_SCB_Addr = Memmap_SCS_Addr + 0x0D00UL,

	/// Peripheral CAN0 base address
	Memmap_CAN0_Addr = 0x40024000u,

	/// Peripheral CAN1 base pointer
	Memmap_CAN1_Addr = 0x40025000u,

	/// Peripheral CAN2 base pointer
	Memmap_CAN2_Addr = 0x400A4000u,
} hw_memmap_t;

#endif /* INCLUDE_HW_MEMMAP_H_ */
