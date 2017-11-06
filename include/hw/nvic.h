// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_NVIC_H_
#define INCLUDE_HW_NVIC_H_

#include "types.h"
#include "hw/common.h"

/// Low value = High prio. Range 0(highest) - 15(lowest)
enum {
	/// Charge pump Input Capture timer
	NVIC_Prio_chp = 1,
	/// Output Compare timer
	NVIC_Prio_timer = 2,
	/// General timers
	NVIC_Prio_general_timer = 3,
	/// Debug UART
	NVIC_Prio_uart = 4,
	/// IIC
	NVIC_Prio_i2c = 5,
	/// CAN Pluto bus
	NVIC_Prio_can_plutobus = 6,
	/// CAN AUX
	NVIC_Prio_can_aux = 7,
	/// Delay
	NVIC_Prio_delay = 10,
	/// Delayed interrupt - Lowest priority
	NVIC_Prio_delayed = 15
};

typedef enum IRQn {
  /* Auxiliary constants */
  NVIC_IRQn_NotAvail                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NVIC_IRQn_NonMaskableInt          = -14,              /**< Non Maskable Interrupt */
  NVIC_IRQn_HardFault               = -13,              /**< Cortex-M7 SV Hard Fault Interrupt */
  NVIC_IRQn_MemoryManagement        = -12,              /**< Cortex-M7 Memory Management Interrupt */
  NVIC_IRQn_BusFault                = -11,              /**< Cortex-M7 Bus Fault Interrupt */
  NVIC_IRQn_UsageFault              = -10,              /**< Cortex-M7 Usage Fault Interrupt */
  NVIC_IRQn_SVCall                  = -5,               /**< Cortex-M7 SV Call Interrupt */
  NVIC_IRQn_DebugMonitor            = -4,               /**< Cortex-M7 Debug Monitor Interrupt */
  NVIC_IRQn_PendSV                  = -2,               /**< Cortex-M7 Pend SV Interrupt */
  NVIC_IRQn_SysTick                 = -1,               /**< Cortex-M7 System Tick Interrupt */

  /* Device specific interrupts */
  NVIC_IRQn_DMA0_DMA16              = 0,                /**< DMA channel 0/16 transfer complete */
  NVIC_IRQn_DMA1_DMA17              = 1,                /**< DMA channel 1/17 transfer complete */
  NVIC_IRQn_DMA2_DMA18              = 2,                /**< DMA channel 2/18 transfer complete */
  NVIC_IRQn_DMA3_DMA19              = 3,                /**< DMA channel 3/19 transfer complete */
  NVIC_IRQn_DMA4_DMA20              = 4,                /**< DMA channel 4/20 transfer complete */
  NVIC_IRQn_DMA5_DMA21              = 5,                /**< DMA channel 5/21 transfer complete */
  NVIC_IRQn_DMA6_DMA22              = 6,                /**< DMA channel 6/22 transfer complete */
  NVIC_IRQn_DMA7_DMA23              = 7,                /**< DMA channel 7/23 transfer complete */
  NVIC_IRQn_DMA8_DMA24              = 8,                /**< DMA channel 8/24 transfer complete */
  NVIC_IRQn_DMA9_DMA25              = 9,                /**< DMA channel 9/25 transfer complete */
  NVIC_IRQn_DMA10_DMA26             = 10,               /**< DMA channel 10/26 transfer complete */
  NVIC_IRQn_DMA11_DMA27             = 11,               /**< DMA channel 11/27 transfer complete */
  NVIC_IRQn_DMA12_DMA28             = 12,               /**< DMA channel 12/28 transfer complete */
  NVIC_IRQn_DMA13_DMA29             = 13,               /**< DMA channel 13/29 transfer complete */
  NVIC_IRQn_DMA14_DMA30             = 14,               /**< DMA channel 14/30 transfer complete */
  NVIC_IRQn_DMA15_DMA31             = 15,               /**< DMA channel 15/31 transfer complete */
  NVIC_IRQn_DMA_Error               = 16,               /**< DMA error interrupt channels 0-31 */
  NVIC_IRQn_MCM                     = 17,               /**< MCM normal interrupt */
  NVIC_IRQn_FTFE                    = 18,               /**< FTFL command complete */
  NVIC_IRQn_Read_Collision          = 19,               /**< FTFL read collision */
  NVIC_IRQn_PMC                     = 20,               /**< PMC controller low-voltage detect, low-voltage warning */
  NVIC_IRQn_LLWU                    = 21,               /**< Low leakage wakeup */
  NVIC_IRQn_WDOG_EWM                = 22,               /**< Single interrupt vector for  WDOG and EWM */
  NVIC_IRQn_TRNG0                   = 23,               /**< True randon number generator */
  NVIC_IRQn_I2C0                    = 24,               /**< Inter-integrated circuit 0 */
  NVIC_IRQn_I2C1                    = 25,               /**< Inter-integrated circuit 1 */
  NVIC_IRQn_SPI0                    = 26,               /**< Serial peripheral Interface 0 */
  NVIC_IRQn_SPI1                    = 27,               /**< Serial peripheral Interface 1 */
  NVIC_IRQn_UART5_RX_TX             = 28,               /**< UART5 receive/transmit interrupt */
  NVIC_IRQn_UART5_ERR               = 29,               /**< UART5 error interrupt */
  NVIC_IRQn_Reserved46              = 30,               /**< Reserved interrupt */
  NVIC_IRQn_UART0_RX_TX             = 31,               /**< UART0 receive/transmit interrupt */
  NVIC_IRQn_UART0_ERR               = 32,               /**< UART0 error interrupt */
  NVIC_IRQn_UART1_RX_TX             = 33,               /**< UART1 receive/transmit interrupt */
  NVIC_IRQn_UART1_ERR               = 34,               /**< UART1 error interrupt */
  NVIC_IRQn_UART2_RX_TX             = 35,               /**< UART2 receive/transmit interrupt */
  NVIC_IRQn_UART2_ERR               = 36,               /**< UART2 error interrupt */
  NVIC_IRQn_ADC0                    = 37,               /**< Analog-to-digital converter 0 */
  NVIC_IRQn_HSADC_ERR               = 38,               /**< High speed analog-to-digital converter zero cross */
  NVIC_IRQn_HSADC0_CCA              = 39,               /**< High speed analog-to-digital converter 0 submodule A scan complete */
  NVIC_IRQn_CMP0                    = 40,               /**< Comparator 0 */
  NVIC_IRQn_CMP1                    = 41,               /**< Comparator 1 */
  NVIC_IRQn_FTM0                    = 42,               /**< FlexTimer module 0 fault, overflow and channels interrupt */
  NVIC_IRQn_FTM1                    = 43,               /**< FlexTimer module 1 fault, overflow and channels interrupt */
  NVIC_IRQn_UART3_RX_TX             = 44,               /**< UART3 receive/transmit interrupt */
  NVIC_IRQn_UART3_ERR               = 45,               /**< UART3 error interrupt */
  NVIC_IRQn_UART4_RX_TX             = 46,               /**< UART4 receive/transmit interrupt */
  NVIC_IRQn_UART4_ERR               = 47,               /**< UART4 error interrupt */
  NVIC_IRQn_PIT0                    = 48,               /**< Periodic interrupt timer channel 0 */
  NVIC_IRQn_PIT1                    = 49,               /**< Periodic interrupt timer channel 1 */
  NVIC_IRQn_PIT2                    = 50,               /**< Periodic interrupt timer channel 2 */
  NVIC_IRQn_PIT3                    = 51,               /**< Periodic interrupt timer channel 3 */
  NVIC_IRQn_PDB0                    = 52,               /**< Programmable delay block 0 */
  NVIC_IRQn_FTM2                    = 53,               /**< FlexTimer module 2 fault, overflow and channels interrupt */
  NVIC_IRQn_XBARA                   = 54,               /**< Inter-peripheral crossbar switch A */
  NVIC_IRQn_PDB1                    = 55,               /**< Programmable delay block 1 */
  NVIC_IRQn_DAC0                    = 56,               /**< Digital-to-analog converter 0 */
  NVIC_IRQn_MCG                     = 57,               /**< Multipurpose clock generator */
  NVIC_IRQn_LPTMR0                  = 58,               /**< Low power timer interrupt */
  NVIC_IRQn_PORTA                   = 59,               /**< Port A interrupt */
  NVIC_IRQn_PORTB                   = 60,               /**< Port B interrupt */
  NVIC_IRQn_PORTC                   = 61,               /**< Port C interrupt */
  NVIC_IRQn_PORTD                   = 62,               /**< Port D interrupt */
  NVIC_IRQn_PORTE                   = 63,               /**< Port E interrupt */
  NVIC_IRQn_SWI                     = 64,               /**< Software interrupt */
  NVIC_IRQn_SPI2                    = 65,               /**< Serial peripheral Interface 2 */
  NVIC_IRQn_ENC_COMPARE             = 66,               /**< ENC Compare */
  NVIC_IRQn_ENC_HOME                = 67,               /**< ENC Home */
  NVIC_IRQn_ENC_WDOG_SAB            = 68,               /**< ENC Wdog/SAB */
  NVIC_IRQn_ENC_INDEX               = 69,               /**< ENC Index/Roll over/Roll Under */
  NVIC_IRQn_CMP2                    = 70,               /**< Comparator 2 */
  NVIC_IRQn_FTM3                    = 71,               /**< FlexTimer module 3 fault, overflow and channels */
  NVIC_IRQn_Reserved88              = 72,               /**< Reserved interrupt */
  NVIC_IRQn_HSADC0_CCB              = 73,               /**< High speed analog-to-digital converter 0 submodule B scan complete */
  NVIC_IRQn_HSADC1_CCA              = 74,               /**< High speed analog-to-digital converter 1 submodule A scan complete */
  NVIC_IRQn_CAN0_ORed_Message_buffer = 75,              /**< Flex controller area network 0 message buffer */
  NVIC_IRQn_CAN0_Bus_Off            = 76,               /**< Flex controller area network 0 bus off */
  NVIC_IRQn_CAN0_Error              = 77,               /**< Flex controller area network 0 error */
  NVIC_IRQn_CAN0_Tx_Warning         = 78,               /**< Flex controller area network 0 transmit */
  NVIC_IRQn_CAN0_Rx_Warning         = 79,               /**< Flex controller area network 0 receive */
  NVIC_IRQn_CAN0_Wake_Up            = 80,               /**< Flex controller area network 0 wake up */
  NVIC_IRQn_PWM0_CMP0               = 81,               /**< Pulse width modulator 0 channel 0 compare */
  NVIC_IRQn_PWM0_RELOAD0            = 82,               /**< Pulse width modulator 0 channel 0 reload */
  NVIC_IRQn_PWM0_CMP1               = 83,               /**< Pulse width modulator 0 channel 1 compare */
  NVIC_IRQn_PWM0_RELOAD1            = 84,               /**< Pulse width modulator 0 channel 1 reload */
  NVIC_IRQn_PWM0_CMP2               = 85,               /**< Pulse width modulator 0 channel 2 compare */
  NVIC_IRQn_PWM0_RELOAD2            = 86,               /**< Pulse width modulator 0 channel 2 reload */
  NVIC_IRQn_PWM0_CMP3               = 87,               /**< Pulse width modulator 0 channel 3 compare */
  NVIC_IRQn_PWM0_RELOAD3            = 88,               /**< Pulse width modulator 0 channel 3 reload */
  NVIC_IRQn_PWM0_CAP                = 89,               /**< Pulse width modulator 0 capture */
  NVIC_IRQn_PWM0_RERR               = 90,               /**< Pulse width modulator 0 reload error */
  NVIC_IRQn_PWM0_FAULT              = 91,               /**< Pulse width modulator 0 fault */
  NVIC_IRQn_CMP3                    = 92,               /**< Comparator 3 */
  NVIC_IRQn_HSADC1_CCB              = 93,               /**< High speed analog-to-digital converter 1 submodule B scan complete */
  NVIC_IRQn_CAN1_ORed_Message_buffer = 94,              /**< Flex controller area network 1 message buffer */
  NVIC_IRQn_CAN1_Bus_Off            = 95,               /**< Flex controller area network 1 bus off */
  NVIC_IRQn_CAN1_Error              = 96,               /**< Flex controller area network 1 error */
  NVIC_IRQn_CAN1_Tx_Warning         = 97,               /**< Flex controller area network 1 transmit */
  NVIC_IRQn_CAN1_Rx_Warning         = 98,               /**< Flex controller area network 1 receive */
  NVIC_IRQn_CAN1_Wake_Up            = 99,               /**< Flex controller area network 1 wake up */
  NVIC_IRQn_ENET_1588_Timer         = 100,              /**< Ethernet MAC IEEE 1588 timer */
  NVIC_IRQn_ENET_Transmit           = 101,              /**< Ethernet MAC transmit */
  NVIC_IRQn_ENET_Receive            = 102,              /**< Ethernet MAC receive */
  NVIC_IRQn_ENET_Error              = 103,              /**< Ethernet MAC error and miscelaneous */
  NVIC_IRQn_PWM1_CMP0               = 104,              /**< Pulse width modulator 1 channel 0 compare */
  NVIC_IRQn_PWM1_RELOAD0            = 105,              /**< Pulse width modulator 1 channel 0 reload */
  NVIC_IRQn_PWM1_CMP1               = 106,              /**< Pulse width modulator 1 channel 1 compare */
  NVIC_IRQn_PWM1_RELOAD1            = 107,              /**< Pulse width modulator 1 channel 1 reload */
  NVIC_IRQn_PWM1_CMP2               = 108,              /**< Pulse width modulator 1 channel 2 compare */
  NVIC_IRQn_PWM1_RELOAD2            = 109,              /**< Pulse width modulator 1 channel 2 reload */
  NVIC_IRQn_PWM1_CMP3               = 110,              /**< Pulse width modulator 1 channel 3 compare */
  NVIC_IRQn_PWM1_RELOAD3            = 111,              /**< Pulse width modulator 1 channel 3 reload */
  NVIC_IRQn_PWM1_CAP                = 112,              /**< Pulse width modulator 1 capture */
  NVIC_IRQn_PWM1_RERR               = 113,              /**< Pulse width modulator 1 reload error */
  NVIC_IRQn_PWM1_FAULT              = 114,              /**< Pulse width modulator 1 fault */
  NVIC_IRQn_CAN2_ORed_Message_buffer = 115,             /**< Flex controller area network 2 message buffer */
  NVIC_IRQn_CAN2_Bus_Off            = 116,              /**< Flex controller area network 2 bus off */
  NVIC_IRQn_CAN2_Error              = 117,              /**< Flex controller area network 2 error */
  NVIC_IRQn_CAN2_Tx_Warning         = 118,              /**< Flex controller area network 2 transmit */
  NVIC_IRQn_CAN2_Rx_Warning         = 119,              /**< Flex controller area network 2 receive */
  NVIC_IRQn_CAN2_Wake_Up            = 120               /**< Flex controller area network 2 wake up */
} IRQn_Type;

typedef struct {
	/// Interrupt Set Enable Register
	__IOM uint32_t ISER[8U];
	uint32_t RESERVED0[24U];
	/// Interrupt Clear Enable Register
	__IOM uint32_t ICER[8U];
	uint32_t RSERVED1[24U];
	/// Interrupt Set Pending Register
	__IOM uint32_t ISPR[8U];
	uint32_t RESERVED2[24U];
	/// Interrupt Clear Pending Register
	__IOM uint32_t ICPR[8U];
	uint32_t RESERVED3[24U];
	/// Interrupt Active bit Register
	__IOM uint32_t IABR[8U];
	uint32_t RESERVED4[56U];
	/// Interrupt Priority Register (8Bit wide)
	__IOM uint8_t IP[240U];
	uint32_t RESERVED5[644U];
	/// Software Trigger Interrupt Register
	__OM uint32_t STIR;
} NVIC_Type;

enum {
	NVIC_IP_Prio_Shift = 4,
	NVIC_IP_Prio_Mask = 0xF << NVIC_IP_Prio_Shift,
} nvic_fields_t;

volatile NVIC_Type * volatile const hw_nvic = (NVIC_Type *) Memmap_NVIC_Addr;

#endif /* INCLUDE_HW_NVIC_H_ */
