/*
 * Copyright 2018-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DCFG_LSCH3_H
#define DCFG_LSCH3_H

/* dcfg block register offsets and bitfields */
#define DCFG_BOOTLOCPTRL_OFFSET		0x400
#define DCFG_BOOTLOCPTRH_OFFSET		0x404
#define DCFG_COREDISR_OFFSET		0x94
#define DCFG_COREDISABLEDSR_OFFSET	0x990
#define DCFG_PORSR1_OFFSET		0x00
#define DCFG_SCRATCHRW5_OFFSET		0x210
#define DCFG_SCRATCHRW6_OFFSET		0x214
#define DCFG_SCRATCHRW7_OFFSET		0x218
#define DCFG_SVR_OFFSET			0x0A4
#define RCW_SR1_OFFSET			0x100
#define RCW_SR27_OFFSET			0x168
#define RCWSR0_OFFSET			0x0100
#define RCWSR5_OFFSET			0x110
#define RCWSR9_OFFSET			0x120

#define SVR_SEC_MASK			0x100

/* DCFG regsiters bit masks */
#define RCWSR0_SYS_PLL_RAT_SHIFT	2
#define RCWSR0_SYS_PLL_RAT_MASK		0x1f
#define RCWSR0_MEM_PLL_RAT_SHIFT	10
#define RCWSR0_MEM_PLL_RAT_MASK		0x3f
#define RCWSR0_MEM2_PLL_RAT_SHIFT	18
#define RCWSR0_MEM2_PLL_RAT_MASK	0x3f

#define RCWSR_SB_EN_OFFSET		RCWSR9_OFFSET
#define RCWSR_SBEN_MASK			0x1
#define RCWSR_SBEN_SHIFT		10

#endif /*	DCFG_LSCH3_H	*/
