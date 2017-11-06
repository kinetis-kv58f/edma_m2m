// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <stdint.h>

typedef uint8_t bool_t;

#define FALSE 0U

#define TRUE 1U

typedef unsigned int uint_t;

typedef int int_t;

#ifndef NULL
#define NULL ((void *) 0)
#endif

/// Returns lower byte of the halfword
/// \param data Input halfword
/// \returns Lower byte
static inline uint8_t uint16_get_hi_byte(uint16_t const data);
static inline uint8_t uint16_get_hi_byte(uint16_t const data) {
	return (uint8_t)(data >> 8U);
}

/// Returns higher byte of the halfword
/// \param data Input halfword
/// \returns Higher byte
static inline uint8_t uint16_get_lo_byte(uint16_t const data);
static inline uint8_t uint16_get_lo_byte(uint16_t const data) {
	return (uint8_t)(data & 0xFFU);
}

#endif /* SRC_TYPES_H_ */
