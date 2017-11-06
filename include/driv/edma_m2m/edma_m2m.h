// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_DRIV_EDMA_M2M_EDMA_M2M_H_
#define INCLUDE_DRIV_EDMA_M2M_EDMA_M2M_H_

#include "types.h"

enum {
	EdmaM2M_NumTransfers = 5,
} edmaM2M_consts_t;

static const uint8_t edmaM2MSrc[EdmaM2M_NumTransfers] = { 5, 6, 7, 8, 9 };

void edmaM2M_prepare(void);

bool_t edmaM2M_start(void);

bool_t edmaM2M_did_finish(void);

void edmaM2M_clear_dstBuffer(void);

void edmaM2M_print_dstBuffer(void);

int16_t edmaM2M_get_dstBuffer(uint8_t const index);

#endif /* INCLUDE_DRIV_EDMA_M2M_EDMA_M2M_H_ */
