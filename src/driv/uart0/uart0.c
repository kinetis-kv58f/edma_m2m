// © 2011. Ravi Teja Gudapati. All rights reserved.

#include "hw/hw.h"
#include "driv/cpu/cpu.h"
#include "driv/uart0/uart0.h"

/// Pin number of UART RX pin
static const uint8_t rxPinNum = 0x0;

/// Pin number of UART TX pin
static const uint8_t txPinNum = 0x1;

void uart0_putc(uint8_t const data) {
	while ((hw_uart0->S1 & Uart_S1_TDRE_Mask) == 0)
		;

	hw_uart0->D = data;
}

int16_t uart0_getc(void) {
	// TODO
	return -1;
}

void uart0_print_hex(uint8_t const data) {
	if (data < 0xA) {
		uart0_putc(data + '0');
	} else if (data < 0x10) {
		uart0_putc(data - 0xA + 'A');
	}
}

void uart0_print_hex_byte(uint8_t const data) {
	uart0_print_hex((data >> 4) & 0xF);
	uart0_print_hex(data & 0xF);
}

void uart0_print_hex_halfword(uint16_t const data) {
	uart0_print_hex_byte(data >> 8);
	uart0_print_hex_byte(data >> 0);
}

void uart0_print_hex_word(uint32_t const data) {
	uart0_print_hex_byte(data >> 24);
	uart0_print_hex_byte(data >> 16);
	uart0_print_hex_byte(data >> 8);
	uart0_print_hex_byte(data >> 0);
}

void uart0_print_newline(void) {
	//uart0_putc('\n');
	uart0_putc('\r');
}

/// Sets up baudrate during UART initialization
static inline bool_t priv_setup_baudrate(const uint32_t baudrate) {
	uint32_t const srcClock_Hz = System_FastPhCLK_Freq;

	uint16_t const sbr = srcClock_Hz / (baudrate * 16);

	if (sbr == 0 || sbr > 0x1FFF) {
		return FALSE;
	}

	uint16_t const brfa = ((2 * srcClock_Hz) / baudrate) - 32 * sbr;

	if (brfa > 0x1F) {
		return FALSE;
	}

	// Calculate the baud rate based on the temporary SBR values and BRFA
	uint32_t const tempBaud = (srcClock_Hz * 2 / ((sbr * 32 + brfa)));

	uint32_t const baudDiff =
			(tempBaud > baudrate) ?
					(tempBaud - baudrate) : (baudrate - tempBaud);

	// Unacceptable baud rate difference of more than 3%?
	if (baudDiff > ((baudrate / 100) * 3)) {
		return FALSE;
	}

	// Set SBR
	hw_uart0->BDH = (hw_uart0->BDH & ~Uart_BDH_SBR_Mask)
			| uint16_get_hi_byte(sbr);
	hw_uart0->BDL = uint16_get_lo_byte(sbr);

	// Set BRFA
	hw_uart0->C4 &= ~Uart_C4_BRFA_Mask;
	hw_uart0->C4 |= brfa;

	return TRUE;
}

static inline void priv_setup_pins(void) {
	// Initialize port B clock
	hw_sim->SCGC5 |= SIM_SCGC5_PORTB_Mask;

	// Set RX pin port mux to UART
	{
		uint32_t pcr = hw_portB->PCR[rxPinNum];

		// Clear old Mux value
		pcr &= ~PortMuxMask;
		// Set Mux to GPIO functionality
		pcr |= ((uint32_t) Port_MuxAlt7 << PortMuxShift) & PortMuxMask;
		// Disable interrupt configuration
		pcr &= ~PortIrqCMask;
		// Disable pull resistor
		pcr &= ~PORT_PCR_PE_Mask;

		hw_portB->PCR[rxPinNum] = pcr;
	}

	// Set TX pin port mux to UART
	{
		uint32_t pcr = hw_portB->PCR[txPinNum];

		// Clear old Mux value
		pcr &= ~PortMuxMask;
		// Set Mux to GPIO functionality
		pcr |= ((uint32_t) Port_MuxAlt7 << PortMuxShift) & PortMuxMask;
		// Disable interrupt configuration
		pcr &= ~PortIrqCMask;
		// Disable pull resistor
		pcr &= ~PORT_PCR_PE_Mask;

		hw_portB->PCR[txPinNum] = pcr;
	}
}

bool_t uart0_init(uint32_t const baudrate) {
	priv_setup_pins();

	uart0_off();

	// Enable clock to UART
	hw_sim->SCGC4 |= SIM_SCGC4_Uart0_Mask;

	// Select source for UART0 RX and TX (Only for UART0 & UART1)
	hw_sim->SOPT5 &= ~(SIM_SOPT5_UART0RXSR_Mask | SIM_SOPT5_UART0TXSR_Mask);

	if (priv_setup_baudrate(baudrate) == FALSE) {
		return FALSE;
	}

	// 1 stop bit
	hw_uart0->BDH &= ~Uart_BDH_SBNS_Mask;

	// No parity
	hw_uart0->C1 &= ~(Uart_C1_PE_Mask | Uart_C1_PT_Mask);

	// 8-bits word length
	hw_uart0->C1 &= ~Uart_C1_M_Mask;

	// FIFO
	// Set FIFO watermark
	hw_uart0->TWFIFO = 1;
	hw_uart0->RWFIFO = 1;
	// Enable FIFOs
	hw_uart0->PFIFO |= (Uart_PFIFO_TXFE_Mask | Uart_PFIFO_RXFE_Mask);
	// Flash FIFOs
	hw_uart0->CFIFO |= (Uart_CFIFO_TXFLUSH_Mask | Uart_CFIFO_RXFLUSH_Mask);

	// Enable RX and TX
	hw_uart0->C2 |= Uart_C2_TE_Mask | Uart_C2_RE_Mask;
	//Enable RX interrupt
	hw_uart0->C2 |= Uart_C2_RIE_Mask;
	/// Enable error interrupts
	hw_uart0->C3 |= Uart_C3_ORIE_Mask | Uart_C3_FEIE_Mask | Uart_C3_PEIE_Mask;

	// Enable IRQ channel for UART0 ERR
	hw_nvic->ISER[NVIC_IRQn_UART0_ERR >> 5] = (uint32_t) 0x1
			<< (NVIC_IRQn_UART0_ERR & 0x1F);

	// Enable IRQ channel for UART0 RX/TX
	hw_nvic->ISER[NVIC_IRQn_UART0_RX_TX >> 5] = (uint32_t) 0x1
			<< (NVIC_IRQn_UART0_RX_TX & 0x1F);

	return TRUE;
}

void uart0_off(void) {
	// Enable clock to UART
	hw_sim->SCGC4 |= SIM_SCGC4_Uart0_Mask;

	// TODO Wait for transmit FIFO to be empty

	// Disable module
	// Disable TX and RX interrupts
	// Disable TX and RX
	hw_uart0->C2 = 0;

	// Enable IRQ channel for UART0 ERR
	hw_nvic->ISER[NVIC_IRQn_UART0_ERR >> 5] &= ~((uint32_t) 0x1
			<< (NVIC_IRQn_UART0_ERR & 0x1F));

	// Enable IRQ channel for UART0 RX/TX
	hw_nvic->ISER[NVIC_IRQn_UART0_RX_TX >> 5] &= ~((uint32_t) 0x1
			<< (NVIC_IRQn_UART0_RX_TX & 0x1F));

	/// Disable error interrupts
	hw_uart0->C3 &=
			~(Uart_C3_ORIE_Mask | Uart_C3_FEIE_Mask | Uart_C3_PEIE_Mask);

	// Disable FIFO overflow/underflow interrupts
	hw_uart0->CFIFO &= ~(Uart_CFIFO_RXOFE_Mask | Uart_CFIFO_TXFOFE_Mask
			| Uart_CFIFO_RXUFE_Mask);

	// Flash FIFOs
	hw_uart0->CFIFO |= (Uart_CFIFO_TXFLUSH_Mask | Uart_CFIFO_RXFLUSH_Mask);

	// Disable clock to UART
	hw_sim->SCGC4 &= ~SIM_SCGC4_Uart0_Mask;
}
