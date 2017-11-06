// © 2011. Ravi Teja Gudapati. All rights reserved.

#include <hw/dma.h>
#include "hw/sim.h"
#include "hw/port.h"
#include "driv/uart0/uart0.h"
#include "driv/edma_m2m/edma_m2m.h"

uint8_t edmaM2MDest[EdmaM2M_NumTransfers] = { 0 };

void edmaM2M_prepare(void) {
	edmaM2M_clear_dstBuffer();

	// Enable clock for DMAMUX hardware
	hw_sim->SCGC6 |= SIM_SCGC6_DMAMUX_Mask;
	// Enable clock for DMA hardware
	hw_sim->SCGC7 |= SIM_SCGC6_DMA_Mask;

	// Always enabled source. No trigger.
	hw_dmamux->CHCFG[0] = DMAMUX_CHCFG_ENBL_Mask
			| DMAMUX_CHCFG_SOURCE_Group0_AlwaysOn0;
	// Source address. Constant buffer in RAM holding channels to read.
	hw_dma->TCD[0].SADDR = (uint32_t) &edmaM2MSrc[0];
	// Source address increment. Data is 1 byte.
	hw_dma->TCD[0].SOFF = 0x01;
	// Source address reload after major loop finish.
	hw_dma->TCD[0].SLAST = -sizeof(edmaM2MSrc);
	// Destination address. ADC0 control register.
	hw_dma->TCD[0].DADDR = (uint32_t) &edmaM2MDest[0];
	// Destination address increment. No increment.
	hw_dma->TCD[0].DOFF = 0x01;
	// Destination address reload after major loop finish. No address reload needed.
	hw_dma->TCD[0].DLAST_SGA = -sizeof(edmaM2MDest);
	// Number of bytes for minor loop (one data transfer).
	hw_dma->TCD[0].NBYTES_MLNO = 0x01;
	// Channel linking and major loop setting.
	// No linking after minor loop.
	// Number of minor loops in a major loop: Number of ADC channels to read.
	hw_dma->TCD[0].BITER_ELINKNO = EdmaM2M_NumTransfers;
	// Channel linking and major loop setting reload value after major loop finish.
	// No linking after minor loop.
	// Number of minor loops in a major loop: Number of ADC channels to read.
	hw_dma->TCD[0].CITER_ELINKNO = EdmaM2M_NumTransfers;
	// Source and destination data width specification.
	// No circular buffer.
	// Both source and destination sizes are 8-bit.
	hw_dma->TCD[0].ATTR = 0;
	// Common channel setting.
	// No bandwidth control. No linking after major loop.
	// Disable channel after major loop completion.
	// No IRQ request enable.
	hw_dma->TCD[0].CSR = EDMA_TCD_CSR_DREQ_Mask;
}

bool_t edmaM2M_start(void) {
	if (hw_dma->TCD[0].CSR & EDMA_TCD_CSR_ACTIVE_Mask) {
		return FALSE;
	}

	// Enable request on DMA channels 0 and 16
	hw_dma->ERQ |= ((uint32_t) 1 << 0);

	return TRUE;
}

bool_t edmaM2M_did_finish(void) {
	return hw_dma->TCD[0].CSR & EDMA_TCD_CSR_DONE_Mask;
}

void edmaM2M_clear_dstBuffer(void) {
	for (uint32_t i = 0; i < EdmaM2M_NumTransfers; i++) {
		edmaM2MDest[i] = 0;
	}
}

void edmaM2M_print_dstBuffer(void) {
	for (uint32_t i = 0; i < EdmaM2M_NumTransfers; i++) {
		uart0_print_hex(edmaM2MDest[i]);
	}
}

int16_t edmaM2M_get_dstBuffer(uint8_t const index) {
	if (index >= EdmaM2M_NumTransfers)
		return -1;
	return edmaM2MDest[index];
}
