/*
 *
 * OCTEON SDK
 *
 * Copyright (c) 2011 Cavium Networks. All rights reserved.
 *
 * This file, which is part of the OCTEON SDK which also includes the
 * OCTEON SDK Package from Cavium Networks, contains proprietary and
 * confidential information of Cavium Networks and in some cases its
 * suppliers. 
 *
 * Any licensed reproduction, distribution, modification, or other use of
 * this file or the confidential information or patented inventions
 * embodied in this file is subject to your license agreement with Cavium
 * Networks. Unless you and Cavium Networks have agreed otherwise in
 * writing, the applicable license terms "OCTEON SDK License Type 5" can be found 
 * under the directory: $OCTEON_ROOT/components/driver/licenses/
 *
 * All other use and disclosure is prohibited.
 *
 * Contact Cavium Networks at info@caviumnetworks.com for more information.
 *
 */

/*! \file  cn63xx_device.h
    \brief Host Driver: Routines that perform CN63XX specific operations.
*/



#ifndef  __CN63XX_DEVICE_H__
#define  __CN63XX_DEVICE_H__


#include "cn63xx_regs.h"


/* Register address and configuration for a CN63XX device. */
typedef struct {

	/** PCI interrupt summary register for CN63xx */
	uint8_t            *intr_sum_reg64;

	/** PCI interrupt enable register for CN63xx */
	uint8_t            *intr_enb_reg64;

	/** The PCI interrupt mask used by interrupt handler for CN63xx */
	uint64_t            intr_mask64;

	cn63xx_config_t    *conf;

} octeon_cn63xx_t;




void  cn63xx_setup_global_output_regs(octeon_device_t  *oct);

void  cn63xx_check_config_space_error_regs(octeon_device_t  *oct);

int   setup_cn63xx_octeon_device(octeon_device_t  *oct);

int   validate_cn63xx_config_info(cn63xx_config_t  *conf63xx);


/* Takes a time value in micro seconds and returns the equivalent clock tick
   value to program into 56XX.
*/
uint32_t cn63xx_get_oq_ticks(octeon_device_t  *oct, uint32_t  time_intr_in_us);

uint32_t cn63xx_core_clock(octeon_device_t  *oct);

#endif

/* $Id: cn63xx_device.h 47454 2010-02-18 22:33:46Z panicker $ */
