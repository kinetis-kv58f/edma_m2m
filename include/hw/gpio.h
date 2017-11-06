// © 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_HW_GPIO_H_
#define INCLUDE_HW_GPIO_H_

#include "hw/common.h"
#include "types.h"

/// GPIO - Register Layout Typedef
typedef struct {
	__IO uint32_t PDOR; /**< Port Data Output Register, offset: 0x0 */
	__O uint32_t PSOR; /**< Port Set Output Register, offset: 0x4 */
	__O uint32_t PCOR; /**< Port Clear Output Register, offset: 0x8 */
	__O uint32_t PTOR; /**< Port Toggle Output Register, offset: 0xC */
	__I uint32_t PDIR; /**< Port Data Input Register, offset: 0x10 */
	__IO uint32_t PDDR; /**< Port Data Direction Register, offset: 0x14 */
} hw_gpio_t;

hw_gpio_t * const hw_gpioA = (hw_gpio_t *) Memmap_GPIOA_Addr;

hw_gpio_t * const hw_gpioB = (hw_gpio_t *) Memmap_GPIOB_Addr;

hw_gpio_t * const hw_gpioC = (hw_gpio_t *) Memmap_GPIOC_Addr;

hw_gpio_t * const hw_gpioD = (hw_gpio_t *) Memmap_GPIOD_Addr;

hw_gpio_t * const hw_gpioE = (hw_gpio_t *) Memmap_GPIOE_Addr;

#endif /* INCLUDE_HW_GPIO_H_ */
