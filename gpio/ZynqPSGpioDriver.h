#ifndef ZynqPSGpioDriver_H
#define ZynqPSGpioDriver_H

#include "GpioDriver.h"

typedef struct ZynqPSGpioDriverStruct * ZynqPSGpioDriver;

GpioDriver ZynqPSGpioDriver_Create(uint16_t bank, uint32_t address);

/************************** Constant Definitions *****************************/

/** @name Register offsets for the GPIO. Each register is 32 bits.
 *  @{
 */
#define XGPIOPS_DATA_LSW_OFFSET  0x000  /* Mask and Data Register LSW, WO */
#define XGPIOPS_DATA_MSW_OFFSET  0x004  /* Mask and Data Register MSW, WO */
#define XGPIOPS_DATA_OFFSET	 0x040  /* Data Register, RW */
#define XGPIOPS_DATA_RO_OFFSET	 0x060  /* Data Register - Input, RO */
#define XGPIOPS_DIRM_OFFSET	 0x204  /* Direction Mode Register, RW */
#define XGPIOPS_OUTEN_OFFSET	 0x208  /* Output Enable Register, RW */
#define XGPIOPS_INTMASK_OFFSET	 0x20C  /* Interrupt Mask Register, RO */
#define XGPIOPS_INTEN_OFFSET	 0x210  /* Interrupt Enable Register, WO */
#define XGPIOPS_INTDIS_OFFSET	 0x214  /* Interrupt Disable Register, WO*/
#define XGPIOPS_INTSTS_OFFSET	 0x218  /* Interrupt Status Register, RO */
#define XGPIOPS_INTTYPE_OFFSET	 0x21C  /* Interrupt Type Register, RW */
#define XGPIOPS_INTPOL_OFFSET	 0x220  /* Interrupt Polarity Register, RW */
#define XGPIOPS_INTANY_OFFSET	 0x224  /* Interrupt On Any Register, RW */
/* @} */

/** @name Register offsets for each Bank.
 *  @{
 */
#define XGPIOPS_DATA_MASK_OFFSET 0x8  /* Data/Mask Registers offset */
#define XGPIOPS_DATA_BANK_OFFSET 0x4  /* Data Registers offset */
#define XGPIOPS_REG_MASK_OFFSET 0x40  /* Registers offset */
/* @} */

/* For backwards compatibility */
#define XGPIOPS_BYPM_MASK_OFFSET	XGPIOPS_REG_MASK_OFFSET

/** @name Interrupt type reset values for each bank
 *  @{
 */
#define XGPIOPS_INTTYPE_BANK0_RESET  0xFFFFFFFF
#define XGPIOPS_INTTYPE_BANK1_RESET  0x3FFFFFFF
#define XGPIOPS_INTTYPE_BANK2_RESET  0xFFFFFFFF
#define XGPIOPS_INTTYPE_BANK3_RESET  0xFFFFFFFF
/* @} */



#endif  /*ZynqPSGpioDriver_H */
