// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_WDOG_H_
#define INCLUDE_HW_WDOG_H_

#include "types.h"
#include "hw/common.h"

/** WDOG - Register Layout Typedef */
typedef struct {
  __IO uint16_t STCTRLH;                           /**< Watchdog Status and Control Register High, offset: 0x0 */
  __IO uint16_t STCTRLL;                           /**< Watchdog Status and Control Register Low, offset: 0x2 */
  __IO uint16_t TOVALH;                            /**< Watchdog Time-out Value Register High, offset: 0x4 */
  __IO uint16_t TOVALL;                            /**< Watchdog Time-out Value Register Low, offset: 0x6 */
  __IO uint16_t WINH;                              /**< Watchdog Window Register High, offset: 0x8 */
  __IO uint16_t WINL;                              /**< Watchdog Window Register Low, offset: 0xA */
  __IO uint16_t REFRESH;                           /**< Watchdog Refresh register, offset: 0xC */
  __IO uint16_t UNLOCK;                            /**< Watchdog Unlock register, offset: 0xE */
  __IO uint16_t TMROUTH;                           /**< Watchdog Timer Output Register High, offset: 0x10 */
  __IO uint16_t TMROUTL;                           /**< Watchdog Timer Output Register Low, offset: 0x12 */
  __IO uint16_t RSTCNT;                            /**< Watchdog Reset Count register, offset: 0x14 */
  __IO uint16_t PRESC;                             /**< Watchdog Prescaler register, offset: 0x16 */
} __attribute__((__packed__)) WDOG_Type;

WDOG_Type * const hw_wdog = (WDOG_Type *) Memmap_WDOG_Addr;

enum {
	WDOG_STCTRLH_WAITEN_Shift = 7,
	WDOG_STCTRLH_WAITEN_Mask = 1 << WDOG_STCTRLH_WAITEN_Shift,

	WDOG_STCTRLH_STOPEN_Shift = 6,
	WDOG_STCTRLH_STOPEN_Mask = 1 << WDOG_STCTRLH_STOPEN_Shift,

	WDOG_STCTRLH_ALLOWUPDATE_Shift = 4,
	WDOG_STCTRLH_ALLOWUPDATE_Mask = 1 << WDOG_STCTRLH_ALLOWUPDATE_Shift,

	WDOG_STCTRLH_IRQRSTEN_Shift = 2,
	WDOG_STCTRLH_IRQRSTEN_Mask = 1 << WDOG_STCTRLH_IRQRSTEN_Shift,

	WDOG_STCTRLH_CLKSRC_Shift = 1,
	WDOG_STCTRLH_CLKSRC_Mask = 1 << WDOG_STCTRLH_CLKSRC_Shift
} wdog_fields_t;

#endif /* INCLUDE_HW_WDOG_H_ */
