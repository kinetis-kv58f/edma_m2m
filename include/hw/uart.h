// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_UART_H_
#define INCLUDE_HW_UART_H_

#include "types.h"
#include "hw/common.h"

enum {
	Uart_BDH_SBR_Mask = 0x1F,

	Uart_BDH_SBNS_Shift = 5,
	Uart_BDH_SBNS_Mask = 1 << Uart_BDH_SBNS_Shift,

	Uart_C1_PT_Mask = 1,

	Uart_C1_PE_Shift = 1,
	Uart_C1_PE_Mask = 1 << Uart_C1_PE_Shift,

	Uart_C2_TIE_Shift = 7,
	Uart_C2_TIE_Mask = 1 << Uart_C2_TIE_Shift,

	Uart_C2_TCIE_Shift = 6,
	Uart_C2_TCIE_Mask = 1 << Uart_C2_TCIE_Shift,

	Uart_C2_RIE_Shift = 5,
	Uart_C2_RIE_Mask = 1 << Uart_C2_RIE_Shift,

	Uart_C1_M_Shift = 4,
	Uart_C1_M_Mask = 1 << Uart_C1_M_Shift,

	Uart_C2_TE_Shift = 3,
	Uart_C2_TE_Mask = 1 << Uart_C2_TE_Shift,

	Uart_C2_RE_Shift = 2,
	Uart_C2_RE_Mask = 1 << Uart_C2_RE_Shift,

	Uart_S1_TDRE_Shift = 7,
	Uart_S1_TDRE_Mask = 1 << Uart_S1_TDRE_Shift,

	Uart_S1_TC_Shift = 6,
	Uart_S1_TC_Mask = 1 << Uart_S1_TC_Shift,

	Uart_S1_RDRF_Shift = 5,
	Uart_S1_RDRF_Mask = 1 << Uart_S1_RDRF_Shift,

	Uart_S1_OR_Shift = 3,
	Uart_S1_OR_Mask = 1 << Uart_S1_OR_Shift,

	Uart_S1_FE_Shift = 1,
	Uart_S1_FE_Mask = 1 << Uart_S1_FE_Shift,

	Uart_S1_PF_Mask = 1,

	Uart_C3_ORIE_Shift = 3,
	Uart_C3_ORIE_Mask = 1 << Uart_C3_ORIE_Shift,

	Uart_C3_FEIE_Shift = 1,
	Uart_C3_FEIE_Mask = 1 << Uart_C3_FEIE_Shift,

	Uart_C3_PEIE_Mask = 1,

	Uart_C4_BRFA_Mask = 0x1F,

	Uart_PFIFO_RXFE_Shift = 3,
	Uart_PFIFO_RXFE_Mask = 1 << Uart_PFIFO_RXFE_Shift,

	Uart_PFIFO_TXFE_Shift = 7,
	Uart_PFIFO_TXFE_Mask = 1 << Uart_PFIFO_TXFE_Shift,

	Uart_CFIFO_TXFLUSH_Shift = 7,
	Uart_CFIFO_TXFLUSH_Mask = 1 << Uart_CFIFO_TXFLUSH_Shift,

	Uart_CFIFO_RXFLUSH_Shift = 6,
	Uart_CFIFO_RXFLUSH_Mask = 1 << Uart_CFIFO_RXFLUSH_Shift,

	Uart_CFIFO_RXOFE_Shift = 2,
	Uart_CFIFO_RXOFE_Mask = 1 << Uart_CFIFO_RXOFE_Shift,

	Uart_CFIFO_TXFOFE_Shift = 1,
	Uart_CFIFO_TXFOFE_Mask = 1 << Uart_CFIFO_TXFOFE_Shift,

	Uart_CFIFO_RXUFE_Mask = 1,
} hw_uart_fields_t;

/// UART - Register Layout Typedef
typedef struct {
  __IO uint8_t BDH;                                /**< UART Baud Rate Registers: High, offset: 0x0 */
  __IO uint8_t BDL;                                /**< UART Baud Rate Registers: Low, offset: 0x1 */
  __IO uint8_t C1;                                 /**< UART Control Register 1, offset: 0x2 */
  __IO uint8_t C2;                                 /**< UART Control Register 2, offset: 0x3 */
  __I  uint8_t S1;                                 /**< UART Status Register 1, offset: 0x4 */
  __IO uint8_t S2;                                 /**< UART Status Register 2, offset: 0x5 */
  __IO uint8_t C3;                                 /**< UART Control Register 3, offset: 0x6 */
  __IO uint8_t D;                                  /**< UART Data Register, offset: 0x7 */
  __IO uint8_t MA1;                                /**< UART Match Address Registers 1, offset: 0x8 */
  __IO uint8_t MA2;                                /**< UART Match Address Registers 2, offset: 0x9 */
  __IO uint8_t C4;                                 /**< UART Control Register 4, offset: 0xA */
  __IO uint8_t C5;                                 /**< UART Control Register 5, offset: 0xB */
  __I  uint8_t ED;                                 /**< UART Extended Data Register, offset: 0xC */
  __IO uint8_t MODEM;                              /**< UART Modem Register, offset: 0xD */
  __IO uint8_t IR;                                 /**< UART Infrared Register, offset: 0xE */
       uint8_t RESERVED_0[1];
  __IO uint8_t PFIFO;                              /**< UART FIFO Parameters, offset: 0x10 */
  __IO uint8_t CFIFO;                              /**< UART FIFO Control Register, offset: 0x11 */
  __IO uint8_t SFIFO;                              /**< UART FIFO Status Register, offset: 0x12 */
  __IO uint8_t TWFIFO;                             /**< UART FIFO Transmit Watermark, offset: 0x13 */
  __I  uint8_t TCFIFO;                             /**< UART FIFO Transmit Count, offset: 0x14 */
  __IO uint8_t RWFIFO;                             /**< UART FIFO Receive Watermark, offset: 0x15 */
  __I  uint8_t RCFIFO;                             /**< UART FIFO Receive Count, offset: 0x16 */
       uint8_t RESERVED_1[1];
  __IO uint8_t C7816;                              /**< UART 7816 Control Register, offset: 0x18 */
  __IO uint8_t IE7816;                             /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  __IO uint8_t IS7816;                             /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  __IO uint8_t WP7816;                             /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  __IO uint8_t WN7816;                             /**< UART 7816 Wait N Register, offset: 0x1C */
  __IO uint8_t WF7816;                             /**< UART 7816 Wait FD Register, offset: 0x1D */
  __IO uint8_t ET7816;                             /**< UART 7816 Error Threshold Register, offset: 0x1E */
  __IO uint8_t TL7816;                             /**< UART 7816 Transmit Length Register, offset: 0x1F */
       uint8_t RESERVED_2[26];
  __IO uint8_t AP7816A_T0;                         /**< UART 7816 ATR Duration Timer Register A, offset: 0x3A */
  __IO uint8_t AP7816B_T0;                         /**< UART 7816 ATR Duration Timer Register B, offset: 0x3B */
  union {                                          /* offset: 0x3C */
    struct {                                         /* offset: 0x3C */
      __IO uint8_t WP7816A_T0;                         /**< UART 7816 Wait Parameter Register A, offset: 0x3C */
      __IO uint8_t WP7816B_T0;                         /**< UART 7816 Wait Parameter Register B, offset: 0x3D */
    } TYPE0;
    struct {                                         /* offset: 0x3C */
      __IO uint8_t WP7816A_T1;                         /**< UART 7816 Wait Parameter Register A, offset: 0x3C */
      __IO uint8_t WP7816B_T1;                         /**< UART 7816 Wait Parameter Register B, offset: 0x3D */
    } TYPE1;
  };
  __IO uint8_t WGP7816_T1;                         /**< UART 7816 Wait and Guard Parameter Register, offset: 0x3E */
  __IO uint8_t WP7816C_T1;                         /**< UART 7816 Wait Parameter Register C, offset: 0x3F */
} __attribute__((__packed__)) UART_Type;

volatile UART_Type * const volatile hw_uart0 = (UART_Type *) Memmap_UART0_Addr;

UART_Type * const hw_uart1 = (UART_Type *) Memmap_UART1_Addr;

UART_Type * const hw_uart2 = (UART_Type *) Memmap_UART2_Addr;

UART_Type * const hw_uart3 = (UART_Type *) Memmap_UART3_Addr;

UART_Type * const hw_uart4 = (UART_Type *) Memmap_UART4_Addr;

UART_Type * const hw_uart5 = (UART_Type *) Memmap_UART5_Addr;

#endif /* INCLUDE_HW_UART_H_ */
