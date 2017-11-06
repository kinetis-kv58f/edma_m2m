// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_SCB_H_
#define INCLUDE_HW_SCB_H_

#include "types.h"
#include "hw/common.h"

typedef struct {
	/// CPUID Base Register
	__IM uint32_t CPUID;
	/// Interrupt Control and State Register
	__IOM uint32_t ICSR;
	/// Vector Table Offset Register
	__IOM uint32_t VTOR;
	/// Application Interrupt and Reset Control Register
	__IOM uint32_t AIRCR;
	/// System Control Register
	__IOM uint32_t SCR;
	/// Configuration Control Register
	__IOM uint32_t CCR;
	/// System Handlers Priority Registers (4-7, 8-11, 12-15)
	__IOM uint8_t SHPR[12U];
	/// System Handler Control and State Register
	__IOM uint32_t SHCSR;
	/// Configurable Fault Status Register
	__IOM uint32_t CFSR;
	/// HardFault Status Register
	__IOM uint32_t HFSR;
	/// Debug Fault Status Register
	__IOM uint32_t DFSR;
	__IOM uint32_t MMFAR; /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
	__IOM uint32_t BFAR; /*!< Offset: 0x038 (R/W)  BusFault Address Register */
	__IOM uint32_t AFSR; /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
	__IM uint32_t ID_PFR[2U]; /*!< Offset: 0x040 (R/ )  Processor Feature Register */
	__IM uint32_t ID_DFR; /*!< Offset: 0x048 (R/ )  Debug Feature Register */
	__IM uint32_t ID_AFR; /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
	__IM uint32_t ID_MFR[4U]; /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
	__IM uint32_t ID_ISAR[5U]; /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
	uint32_t RESERVED0[1U];__IM uint32_t CLIDR; /*!< Offset: 0x078 (R/ )  Cache Level ID register */
	__IM uint32_t CTR; /*!< Offset: 0x07C (R/ )  Cache Type register */
	__IM uint32_t CCSIDR; /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
	__IOM uint32_t CSSELR; /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
	__IOM uint32_t CPACR; /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
	uint32_t RESERVED3[93U];__OM uint32_t STIR; /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
	uint32_t RESERVED4[15U];__IM uint32_t MVFR0; /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
	__IM uint32_t MVFR1; /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
	__IM uint32_t MVFR2; /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 1 */
	uint32_t RESERVED5[1U];__OM uint32_t ICIALLU; /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
	uint32_t RESERVED6[1U];__OM uint32_t ICIMVAU; /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
	__OM uint32_t DCIMVAC; /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
	__OM uint32_t DCISW; /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
	__OM uint32_t DCCMVAU; /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
	__OM uint32_t DCCMVAC; /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
	__OM uint32_t DCCSW; /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
	__OM uint32_t DCCIMVAC; /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
	__OM uint32_t DCCISW; /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
	uint32_t RESERVED7[6U];__IOM uint32_t ITCMCR; /*!< Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
	/// Data Tightly-Coupled Memory Control Registers
	__IOM uint32_t DTCMCR;
	/// AHBP Control Register
	__IOM uint32_t AHBPCR;
	/// L1 Cache Control Register
	__IOM uint32_t CACR;
	/// AHB Slave Control Register
	__IOM uint32_t AHBSCR;
	uint32_t RESERVED8[1U];
	/// Auxiliary Bus Fault Status Register
	__IOM uint32_t ABFSR;
} SCB_Type;

enum {
	SCB_CCR_IC_Shift = 17U,
	SCB_CCR_IC_Mask = 1UL << SCB_CCR_IC_Shift,
	SCB_CCR_DC_Shift = 16U,
	SCB_CCR_DC_Mask = 1UL << SCB_CCR_DC_Shift,
	SCB_CCSIDR_NUMSETS_Shift = 13U,
	SCB_CCSIDR_NUMSETS_Mask = 0x7FFFUL << SCB_CCSIDR_NUMSETS_Shift,
	SCB_CCSIDR_ASSOCIATIVITY_Shift = 3U,
	SCB_CCSIDR_ASSOCIATIVITY_Mask = 0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_Shift,

	SCB_DCCISW_WAY_Shift = 30U,
	SCB_DCCISW_WAY_Mask = 3UL << SCB_DCCISW_WAY_Shift,
	SCB_DCCISW_SET_Shift = 5U,
	SCB_DCCISW_SET_Mask = 0x1FFUL << SCB_DCCISW_SET_Shift,
} scb_fields_t;

SCB_Type * const hw_scb = (SCB_Type *) Memmap_SCB_Addr;

#endif /* INCLUDE_HW_SCB_H_ */
