// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_COMMON_H_
#define INCLUDE_HW_COMMON_H_

#include "hw/memmap.h"

/// Defines 'read only' permissions
#define   __I     volatile const

/// Defines 'write only' permissions
#define     __O     volatile

/// Defines 'read / write' permissions
#define     __IO    volatile

/// Defines 'read only' structure member permissions
#define     __IM     volatile const

/// Defines 'write only' structure member permissions
#define     __OM     volatile

/// Defines 'read / write' structure member permissions
#define     __IOM    volatile

#endif /* INCLUDE_HW_COMMON_H_ */
