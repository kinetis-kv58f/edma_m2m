// © 2011. Ravi Teja Gudapati. All rights reserved.

///
/// OScillator 0 is run by EXTAL external clock source.
/// Use EXTAL as source to OSCCLK
/// Select external clock (OSCCLK/FRDIV) as clock source to FLL
/// Select PLL as source to MCGOUTCLK
///
/// Oscillator:
/// EXTAL = 50MHz
/// XTAL_CLK = EXTAL = 50MHz
/// OSCCLK = EXTAL
/// OSCERCLK = OSCCLK/1 = 50MHz
///
/// MCG_FLL:
/// FRDIV = 32
/// FLL = OSCCLK/FRDIV = 1562500
///
/// MCG_PLL:
/// VDIV = 24
/// PRDIV = 4
/// PLL = (OSCCLK * VDIV)/(PRDIV * 2) = 150000000
///
/// MCG_MCGOUTCLK:
/// MCGOUTCLK = PLL
///
/// SIM:
/// CoreCLK = MCGOUTCLK/OUTDIV1 = MCGOUTCLK/1 = 150000000
/// FastPhCLK = MCGOUTCLK/OUTDIV2 = MCGOUTCLK/2 = 75000000
/// FlexbusCLK = MCGOUTCLK/OUTDIV3 = MCGOUTCLK/2 = 75000000
/// BusFlashCLK = MCGOUTCLK/OUTDIV4 = MCGOUTCLK/6 = 25000000
///

#include "types.h"
#include "hw/hw.h"
#include "driv/cpu/cpu.h"

static uint8_t priv_get_oscRangeFromFreq(uint32_t const freq) {
	uint8_t range;

	if (freq <= 39063U) {
		range = 0U;
	} else if (freq <= 8000000U) {
		range = 1U;
	} else {
		range = 2U;
	}

	return range;
}

/// Configure clock dividers and peripheral clock selectors in SIM
static inline void priv_init_sim(void) {
	// OUTDIV1: /1;
	hw_sim->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV1_Mask;
	hw_sim->CLKDIV1 |= (uint32_t) 0x0 << SIM_CLKDIV1_OUTDIV1_Shift;

	// OUTDIV2: /2;
	hw_sim->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV2_Mask;
	hw_sim->CLKDIV1 |= (uint32_t) 0x1 << SIM_CLKDIV1_OUTDIV2_Shift;

	// OUTDIV3: /2
	hw_sim->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV3_Mask;
	hw_sim->CLKDIV1 |= (uint32_t) 0x1 << SIM_CLKDIV1_OUTDIV3_Shift;

	// OUTDIV4: /6
	hw_sim->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV4_Mask;
	hw_sim->CLKDIV1 |= (uint32_t) 0x05 << SIM_CLKDIV1_OUTDIV4_Shift;

	// Select PLL as clock source for ethernet module
	hw_sim->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_Mask;
	hw_sim->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MCGPLLCLK;

	// Select LPO as clock for LPTMR
	hw_sim->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_Mask;
	hw_sim->SOPT1 |= SIM_SOPT1_OSC32KSEL_LPO;
}

/// Configure the Internal reference clock (MCGIRCLK)
static void priv_setup_internalRefClk(void) {
	// Select slow internal clock as source to MCGIRCLK
	hw_mcg->C2 &= ~MCG_C2_IRCS_Mask;

	// Disable MCGIRCLK
	hw_mcg->C1 &= ~MCG_C1_IRCLKEN_Mask;
}

static inline void priv_init_pll(void) {
	// Temporarily, use external reference clock as MCGOUTCLK
	hw_mcg->C1 &= ~MCG_C1_CLKS_Mask;
	hw_mcg->C1 |= MCG_C1_CLKS_External;
	// Wait for changes to commit
	while ((hw_mcg->S & MCG_S_CLKST_Mask) != MCG_S_CLKST_External)
		;

	// Temporarily, switch PLLS to FLL
	hw_mcg->C6 &= ~MCG_C6_PLLS_Mask;
	// Wait for changes to commit
	while ((hw_mcg->S & MCG_S_PLLST_Mask) != 0)
		;

	// Configure PLL
	{
		// PRDIV = 0x3; PLLCLKEN = 0;
		hw_mcg->C5 = 0x3;
		hw_mcg->C6 &= ~MCG_C6_VDIV_Mask;
		// VDIV = 0x8
		hw_mcg->C6 |= 0x8;
		// Enable PLL
		hw_mcg->C5 |= MCG_C5_PLLCLKEN_Mask;

		// Wait for PLL to lock
		while ((hw_mcg->S & MCG_S_LOCK0_Mask) != MCG_S_LOCK0_Mask)
			;
	}

	// Switch PPLS to PLL
	hw_mcg->C6 |= MCG_C6_PLLS_Mask;
	// Wait for MCGOUTCLK to change to PLL
	while ((hw_mcg->S & MCG_S_PLLST_Mask) == 0)
		;

	/// Select FLL/PLL as source of MCGOUTCLK
	hw_mcg->C1 &= ~MCG_C1_CLKS_Mask;
	hw_mcg->C1 |= MCG_C1_CLKS_xLL;

	// Wait for changes to commit
	while ((hw_mcg->S & MCG_S_CLKST_Mask) != MCG_S_CLKST_PLL)
		;
}

static inline void priv_init_fll(void) {
	/// FRDIV = 0; FLL = 50000000/32 = 1562500Hz
	hw_mcg->C1 &= ~MCG_C1_FRDIV_Mask;

	// Set PEE mode
	// Disable low power
	hw_mcg->C2 &= ~MCG_C2_LP_Mask;

	// Select OSCCLK/FRDIV as source clock to FFL
	hw_mcg->C1 &= ~MCG_C1_IREFS_Mask;

	// Wait for changes to commit
	while ((hw_mcg->S & MCG_S_IREFST_Mask) != 0)
		;
}

/// Initializes oscillator, OSCCLK and OSCERCLK
///
/// OSCERCLK powers several on-chip peripherals (non-fast peripherals) on Kv58.
/// It continues to work in low power mode.
///
/// Sets capacitor load to 0 pF
/// Enables OSCERCLK
/// Sets OSCERCLK prescaler to 1
/// Selects external clock as source to OSCCLK
static inline void priv_init_osc(void) {
	// Sets the capacitor load configuration to 0pF
	hw_osc0->CR &= ~(OSC_CR_SC2P_Mask | OSC_CR_SC4P_Mask | OSC_CR_SC8P_Mask
			| OSC_CR_SC16P_Mask);
	// Enable OSCERCLK
	hw_osc0->CR |= OSC_CR_ERCLKEN_Mask;
	// ERPS = 0; Set OSCERCLK prescaler to 1
	hw_osc0->DIV = 0;

	// Select source of OSCCLK
	// External clock is selected as source to OSCCLK
	hw_mcg->C2 &= ~MCG_C2_EREFS_Mask;

	// Set crystal oscillator on low power operation
	hw_mcg->C2 &= ~MCG_C2_HGO_Mask;

	// Select crystal oscillator frequency range
	const uint8_t range = priv_get_oscRangeFromFreq(System_XTAL_CLK_Freq);
	hw_mcg->C2 &= ~MCG_C2_RANGE_Mask;
	hw_mcg->C2 |= range << MCG_C2_RANGE_Shift;

	// NOTE: Have to wait for clock to stabilize if oscillator is selected
}

/// Sets up system clock
static void priv_setup_clocks(void) {
	// Set the system clock dividers in SIM to safe value
	hw_sim->CLKDIV1 = 0x01170000U;

	// Initializes OSC0 according to board configuration
	priv_init_osc();

	priv_init_fll();

	priv_init_pll();

	// Setup internal reference clock
	priv_setup_internalRefClk();

	priv_init_sim();
}

static inline void priv_setup_nvic(void) {
	// Set interrupt group priority for I2C1 module
	hw_nvic->IP[NVIC_IRQn_I2C1] = NVIC_Prio_i2c << NVIC_IP_Prio_Shift;

	// Set interrupt group priority for UART0 (upccomm) module
	hw_nvic->IP[NVIC_IRQn_UART0_ERR] = NVIC_Prio_uart << NVIC_IP_Prio_Shift;
	hw_nvic->IP[NVIC_IRQn_UART0_RX_TX] = NVIC_Prio_uart << NVIC_IP_Prio_Shift;

	// Setup interrupt group priority for Plutobus CAN (pbcan) module
	hw_nvic->IP[NVIC_IRQn_CAN1_ORed_Message_buffer] = NVIC_Prio_can_plutobus << NVIC_IP_Prio_Shift;
	hw_nvic->IP[NVIC_IRQn_CAN1_Bus_Off] = NVIC_Prio_can_plutobus << NVIC_IP_Prio_Shift;
	hw_nvic->IP[NVIC_IRQn_CAN1_Error] = NVIC_Prio_can_plutobus << NVIC_IP_Prio_Shift;
	hw_nvic->IP[NVIC_IRQn_CAN1_Tx_Warning] = NVIC_Prio_can_plutobus << NVIC_IP_Prio_Shift;
	hw_nvic->IP[NVIC_IRQn_CAN1_Rx_Warning] = NVIC_Prio_can_plutobus << NVIC_IP_Prio_Shift;
	hw_nvic->IP[NVIC_IRQn_CAN1_Wake_Up] = NVIC_Prio_can_plutobus << NVIC_IP_Prio_Shift;

	// Setup interrupt priority for FTM1 (cycdynsched)
	hw_nvic->IP[NVIC_IRQn_FTM1] = NVIC_Prio_timer << NVIC_IP_Prio_Shift;

	// Setup interrupt priority for FTM2 (crgpmpsched)
	hw_nvic->IP[NVIC_IRQn_FTM2] = NVIC_Prio_chp << NVIC_IP_Prio_Shift;
	// TODO
}

void cpu_init(void) {
	priv_setup_clocks();
}

void cpu_preinit(void) {
	// Set CP10, CP11 Full Access
	hw_scb->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));

	// Disable watch dog
	// Perform WDOG registers unlock sequence
	// Key 1: 0xC520
	hw_wdog->UNLOCK = 0xC520;
	// Key 2: 0xD928
	hw_wdog->UNLOCK = 0xD928;

	/* WDOG->STCTRLH: ?=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,?=0,?=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
	hw_wdog->STCTRLH = WDOG_STCTRLH_ALLOWUPDATE_Mask | WDOG_STCTRLH_CLKSRC_Mask
			| 0x0100U;

	/* TODO
	// Disable ICache and DCache
	__asm volatile ("dsb 0xF":::"memory");
	__asm volatile ("isb 0xF":::"memory");
	hw_scb->CCR &= ~(uint32_t) SCB_CCR_IC_Mask; // disable I-Cache
	hw_scb->ICIALLU = 0UL; // invalidate I-Cache
	__asm volatile ("dsb 0xF":::"memory");
	__asm volatile ("isb 0xF":::"memory");
	{
		uint32_t ccsidr;
		uint32_t sets;
		uint32_t ways;

		hw_scb->CSSELR = (0U << 1U) | 0U; // Level 1 data cache
		__asm volatile ("dsb 0xF":::"memory");

		ccsidr = hw_scb->CCSIDR;

		hw_scb->CCR &= ~(uint32_t) SCB_CCR_DC_Mask; // disable D-Cache

		// clean & invalidate D-Cache
		sets = (uint32_t) ((ccsidr & SCB_CCSIDR_ASSOCIATIVITY_Mask) >> SCB_CCSIDR_ASSOCIATIVITY_Shift);
		do {
			ways = (uint32_t) ((ccsidr & SCB_CCSIDR_NUMSETS_Mask) >> SCB_CCSIDR_NUMSETS_Shift);
			do {
				hw_scb->DCCISW =
						(((sets << SCB_DCCISW_SET_Shift) & SCB_DCCISW_SET_Mask)
								| ((ways << SCB_DCCISW_WAY_Shift)
										& SCB_DCCISW_WAY_Mask));
			} while (ways--);
		} while (sets--);
	}
	__asm volatile ("dsb 0xF":::"memory");
	__asm volatile ("isb 0xF":::"memory");
	*/

	priv_setup_nvic();
}
