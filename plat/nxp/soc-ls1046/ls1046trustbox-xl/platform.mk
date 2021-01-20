# Copyright 2021 Scalys B.V.
# opensource@scalys.com
#
# SPDX-License-Identifier:	GPL-2.0+

# board-specific build parameters
BOOT_MODE	:= qspi
BOARD		:= trustbox-xl

 # get SoC common build parameters
include plat/nxp/soc-ls1046/soc.mk

BL2_SOURCES	+=	${BOARD_PATH}/ddr_init.c

