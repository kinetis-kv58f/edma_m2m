// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_PORT_H_
#define INCLUDE_HW_PORT_H_

#include "hw/common.h"
#include "types.h"

/// PORT - Register Layout Typedef
typedef struct {
	/// Pin Control Register n, array offset: 0x0, array step: 0x4
	__IO uint32_t PCR[32];

	/// Global Pin Control Low Register, offset: 0x80
	__O uint32_t GPCLR;

	/// Global Pin Control High Register, offset: 0x84
	__O uint32_t GPCHR;

	uint8_t RESERVED_0[24];

	/// Interrupt Status Flag Register, offset: 0xA0
	__IO uint32_t ISFR;

	uint8_t RESERVED_1[28];

	/// Digital Filter Enable Register, offset: 0xC0
	__IO uint32_t DFER;

	/// Digital Filter Clock Register, offset: 0xC4
	__IO uint32_t DFCR;

	/// Digital Filter Width Register, offset: 0xC8
	__IO uint32_t DFWR;
} hw_port_t;

typedef enum _port_mux {
	Port_PinDisabledOrAnalog = 0U, /*!< Corresponding pin is disabled, but is used as an analog pin. */
	Port_MuxAsGpio = 1U, /*!< Corresponding pin is configured as GPIO. */
	Port_MuxAlt2 = 2U, /*!< Chip-specific */
	Port_MuxAlt3 = 3U, /*!< Chip-specific */
	Port_MuxAlt4 = 4U, /*!< Chip-specific */
	Port_MuxAlt5 = 5U, /*!< Chip-specific */
	Port_MuxAlt6 = 6U, /*!< Chip-specific */
	Port_MuxAlt7 = 7U, /*!< Chip-specific */
	Port_MuxAlt8 = 8U, /*!< Chip-specific */
	Port_MuxAlt9 = 9U, /*!< Chip-specific */
	Port_MuxAlt10 = 10U, /*!< Chip-specific */
	Port_MuxAlt11 = 11U, /*!< Chip-specific */
	Port_MuxAlt12 = 12U, /*!< Chip-specific */
	Port_MuxAlt13 = 13U, /*!< Chip-specific */
	Port_MuxAlt14 = 14U, /*!< Chip-specific */
	Port_MuxAlt15 = 15U, /*!< Chip-specific */
} port_mux_t;

enum {
	/// Peripheral PORTA base address
	PortABaseAddr = 0x40049000u,

	/// Peripheral PORTB base address
	PortBBaseAddr = 0x4004A000u,

	/// Peripheral PORTC base address
	PortCBaseAddr = 0x4004B000u,

	/// Peripheral PORTD base address
	PortDBaseAddr = 0x4004C000u,

	/// Peripheral PORTE base address
	PortEBaseAddr = 0x4004D000u,

	PORT_PCR_ODE_Shift = 5,
	PORT_PCR_ODE_Mask = 1 << PORT_PCR_ODE_Shift,

	PORT_PCR_PE_Shift = 1U,
	PORT_PCR_PE_Mask = 1 << PORT_PCR_PE_Shift,


	PORT_PCR_PS_Mask = 1,

	PORT_PCR_PS_Down = 0,
	PORT_PCR_PS_Up = 1,

	PortMuxShift = 8,
	PortMuxMask = 0xF00U,

	PortIrqCMask = 0xF0000U,

	PortIrqCShift = 16,
} hw_port_dummy_enums_t;

volatile hw_port_t * const volatile hw_portA = (hw_port_t *) Memmap_PORTA_Addr;

volatile hw_port_t * const volatile hw_portB = (hw_port_t *) Memmap_PORTB_Addr;

volatile hw_port_t * const volatile hw_portC = (hw_port_t *) Memmap_PORTC_Addr;

volatile hw_port_t * const volatile hw_portD = (hw_port_t *) Memmap_PORTD_Addr;

volatile hw_port_t * const volatile hw_portE = (hw_port_t *) Memmap_PORTE_Addr;

#endif /* INCLUDE_HW_PORT_H_ */
