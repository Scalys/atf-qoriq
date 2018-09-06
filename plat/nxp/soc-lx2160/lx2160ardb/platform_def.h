/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Authors: Ruchika Gupta <ruchika.gupta@nxp.com>
 *	    Pankaj Gupta <pankaj.gupta@nxp.com>
 */

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <arch.h>
/* Certain ARM files require defines from this file */
#include <tbbr_img_def.h>
/* From ARM :-> Has some common defines ARM requires */
#include <common_def.h>
/* Soc specific defines */
#include <soc.h>

#if defined(IMAGE_BL2)
#define SEC_MEM_NON_COHERENT
#endif
/* Special value used to verify platform parameters from BL2 to BL31 */

/* TBD -- Check and get back if this value is same for all platforms */
#define LS_BL31_PLAT_PARAM_VAL		0x0f1e2d3c4b5a6978ULL

/******************************************************************************
 *  Board specific defines
 *****************************************************************************/

#define NXP_SYSCLK_FREQ		100000000
#define NXP_DDRCLK_FREQ		100000000

/* UART related definition */
#define NXP_CONSOLE_ADDR	NXP_UART_ADDR
#define NXP_CONSOLE_BAUDRATE	115200

#define NXP_SPD_EEPROM0		0x51

#define DDRC_NUM_DIMM		2	
#define CONFIG_DDR_ECC_EN
#define CONFIG_DDR_ADDR_DEC	/* enable address decoding feature */

#define PLAT_DEF_DRAM0_SIZE	0x80000000	/*  2G */

/* Board specific - size of QSPI Flash on board */
#if FLEXSPI_NOR_BOOT
#define NXP_FLEXSPI_FLASH_SIZE	0x40000000
#endif
/* TBD Put all memory specific defines here */

/******************************************************************************
 * Required platform porting definitions common to all ARM standard platforms
 *****************************************************************************/

/* Size of cacheable stacks */
#if defined(IMAGE_BL2)
#define PLATFORM_STACK_SIZE	0x1000
#elif defined(IMAGE_BL31)
#define PLATFORM_STACK_SIZE	0x1000
#endif

#define FIRMWARE_WELCOME_STR_LS_BL2	"Welcome to LX2160 BL2 Phase\n"
#define FIRMWARE_WELCOME_STR_LS_BL31	"Welcome to LX2160 BL31 Phase\n"

/* This is common for all platforms where
 * 64K is reserved for Secure memory
 */
/* 64M Secure Memory */
#define NXP_SECURE_DRAM_SIZE	(64 * 1024 * 1024)

/* 2M Secure EL1 Payload Shared Memory */
#define NXP_SP_SHRD_DRAM_SIZE	(2 * 1024 * 1024)

/* Non secure memory */
#define NXP_NS_DRAM_SIZE	(NXP_DRAM0_SIZE - \
				(NXP_SECURE_DRAM_SIZE + NXP_SP_SHRD_DRAM_SIZE))

#define NXP_NS_DRAM_ADDR	NXP_DRAM0_ADDR

#define NXP_SECURE_DRAM_ADDR	(NXP_NS_DRAM_ADDR + NXP_DRAM0_SIZE - \
				(NXP_SECURE_DRAM_SIZE  + NXP_SP_SHRD_DRAM_SIZE))

#define NXP_SP_SHRD_DRAM_ADDR	(NXP_NS_DRAM_ADDR + NXP_DRAM0_SIZE \
				- NXP_SP_SHRD_DRAM_SIZE)

#define BL2_BASE		(NXP_OCRAM_ADDR + NXP_ROM_RSVD)
#define BL2_LIMIT		(NXP_OCRAM_ADDR + NXP_OCRAM_SIZE)
#define BL2_TEXT_LIMIT		(BL2_LIMIT - NXP_ROM_RSVD - CSF_HDR_SZ)

/* 2 MB reserved in secure memory for DDR */
#define BL31_BASE		NXP_SECURE_DRAM_ADDR
#define BL31_SIZE		(0x200000)
#define BL31_LIMIT		(BL31_BASE + BL31_SIZE)

/* Put BL32 in secure memory */
#define BL32_BASE		(NXP_SECURE_DRAM_ADDR + BL31_SIZE)
#define BL32_LIMIT		(NXP_SECURE_DRAM_ADDR + \
				NXP_SECURE_DRAM_SIZE + NXP_SP_SHRD_DRAM_SIZE)

/* BL33 memory region */
/* Hardcoded based on current address in u-boot */
#define BL33_BASE		0x82000000
#define BL33_LIMIT		(NXP_NS_DRAM_ADDR + NXP_NS_DRAM_SIZE)

/* SD block buffer */
#define NXP_SD_BLOCK_BUF_ADDR	ULL(0x80000000)
#define NXP_SD_BLOCK_BUF_SIZE	0x00100000

#define PHY_GEN2_FW_IMAGE_BUFFER	ULL(0x18000000)

/* IO defines as needed by IO driver framework */
/* TBD Add how to reach these numbers */
#define MAX_IO_DEVICES		4
#define MAX_IO_BLOCK_DEVICES	1
#define MAX_IO_HANDLES		4

#define MAX_FIP_DEVICES		2

/*
 * FIP image defines - Offset at which FIP Image would be present
 * Image would include Bl31 , Bl33 and Bl32 (optional)
 */
#define PLAT_FIP_OFFSET		0x100000
#define PLAT_FIP_MAX_SIZE	0x400000

/* Check if this size can be determined from array size */
#if defined(IMAGE_BL2)
#define MAX_MMAP_REGIONS	8
#define MAX_XLAT_TABLES		6
#elif defined(IMAGE_BL31)
#define MAX_MMAP_REGIONS	9
#define MAX_XLAT_TABLES		9
#elif defined(IMAGE_BL32)
#define MAX_MMAP_REGIONS	8
#define MAX_XLAT_TABLES		9
#endif

/******************************************************************************/
// PSCI specific defines BL31
/******************************************************************************/
/* TBD -- MACROS below are for pSCI,picked them as it is from Jiafei
 * needs cleanup by Rod
 */

/* Platform supports max power level at cluster */
#define PLAT_MAX_PWR_LVL		MPIDR_AFFLVL1

/*
 *  Macros for local power states in ARM platforms encoded by State-ID field
 *  within the power-state parameter.
 */
/* Local power state for power domains in Run state. */
#define LS_LOCAL_STATE_RUN	0

/* Local power state for retention. Valid only for CPU power domains */
#define LS_LOCAL_STATE_RET	1

/*
 * Local power state for OFF/power-down. Valid for CPU and cluster power
 * domains
 */
#define LS_LOCAL_STATE_OFF	2

/*
 * This macro defines the deepest retention state possible. A higher state
 * id will represent an invalid or a power down state.
 */
#define PLAT_MAX_RET_STATE		LS_LOCAL_STATE_RET

/*
 * This macro defines the deepest power down states possible. Any state ID
 * higher than this is invalid.
 */
#define PLAT_MAX_OFF_STATE		LS_LOCAL_STATE_OFF

/*
 * Some data must be aligned on the biggest cache line size in the platform.
 * This is known only to the platform as it might have a combination of
 * integrated and external caches.
 */
#define CACHE_WRITEBACK_GRANULE		(1 << 6)

/*
 * One cache line needed for bakery locks on ARM platforms
 */
#define PLAT_PERCPU_BAKERY_LOCK_SIZE		(1 * CACHE_WRITEBACK_GRANULE)

/******************************************************************************/
/*
 * ID of the secure physical generic timer interrupt used by the BL32.
 */
#define BL32_IRQ_SEC_PHY_TIMER	29

#define BL31_WDOG_SEC		89
/*
 * Define properties of Group 1 Secure and Group 0 interrupts as per GICv3
 * terminology. On a GICv2 system or mode, the lists will be merged and treated
 * as Group 0 interrupts.
 */
#define PLAT_LS_G1S_IRQ_PROPS(grp) \
	INTR_PROP_DESC(BL32_IRQ_SEC_PHY_TIMER, GIC_HIGHEST_SEC_PRIORITY, grp, \
			GIC_INTR_CFG_EDGE)

/* SGI 15 and Secure watchdog interrupts assigned to Group 0 */
#define PLAT_LS_G0_IRQ_PROPS(grp)	\
	INTR_PROP_DESC(BL31_WDOG_SEC, GIC_HIGHEST_SEC_PRIORITY, grp, \
			GIC_INTR_CFG_EDGE), \
	INTR_PROP_DESC(15, GIC_HIGHEST_SEC_PRIORITY, grp, \
			GIC_INTR_CFG_LEVEL)


#endif 
