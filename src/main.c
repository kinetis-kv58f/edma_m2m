// © 2011. Ravi Teja Gudapati. All rights reserved.

#include <driv/uart0/uart0.h>
#include "driv/cpu/cpu.h"
#include "driv/edma_m2m/edma_m2m.h"

int main(void) {
	cpu_init();

	uart0_init(Uart_Baudrate_4800);

	// Print start
	uart0_putc('s');
	uart0_print_newline();

	edmaM2M_prepare();

	if(edmaM2M_start()) {
		// Wait for completion
		while(edmaM2M_did_finish() == FALSE);

		edmaM2M_print_dstBuffer();

		for (uint32_t i = 0; i < EdmaM2M_NumTransfers; i++) {
			if(edmaM2M_get_dstBuffer(i) != (5 + i)) {
				// Print error
				uart0_putc('x');
				uart0_putc('1');
				uart0_print_newline();
				break;
			}
		}
	} else {
		// Print error
		uart0_putc('x');
		uart0_putc('1');
		uart0_print_newline();
	}

	// Print finish
	uart0_putc('k');
	uart0_print_newline();

	while(1);
}
