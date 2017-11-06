// © 2011. Ravi Teja Gudapati. All rights reserved.
/// Non-interrupt driven blocking communication over UART using UART0

#ifndef INCLUDE_DRIV_UART0_UART0_H_
#define INCLUDE_DRIV_UART0_UART0_H_

#include "types.h"

enum {
	Uart_Baudrate_1200 = 1200,
	Uart_Baudrate_2400 = 2400,
	Uart_Baudrate_4800 = 4800,
	Uart_Baudrate_19200 = 19200,
	Uart_Baudrate_38400 = 38400,
	Uart_Baudrate_57600 = 57600,
	Uart_Baudrate_115200 = 115200,
	Uart_Baudrate_230400 = 230400,
} uart_baudrates_t;

/// \brief Init UART0
/// \param[in] baud	Desired baudrate
extern bool_t uart0_init(uint32_t const baud);

/// \brief Turn off UART0
extern void uart0_off(void);

/// \brief Write single byte to UART0
///
///	Blocks until UART0 buffer is empty, then it writes the character to
///	UART and returns.
/// \param[in] data	Byte of data to send
extern void uart0_putc(uint8_t const data);

/// \brief Read single byte from UART0
///
/// \returns -1 if
extern int16_t uart0_getc(void);

/// \brief Writes [data] as hex characters to UART
/// \param[in] data Data
extern void uart0_print_hex(uint8_t const data);

/// \brief Writes [data] as hex characters to UART
/// \param[in] data Data
extern void uart0_print_hex_byte(uint8_t const data);

/// \brief Writes [data] as hex characters to UART
/// \param[in] data Data
extern void uart0_print_hex_halfword(uint16_t const data);

/// \brief Writes [data] as hex characters to UART
/// \param[in] data Data
extern void uart0_print_hex_word(uint32_t const data);

/// \brief Writes newline to UART
extern void uart0_print_newline(void);

#endif /* INCLUDE_DRIV_UART0_UART0_H_ */
