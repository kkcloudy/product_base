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
/***********************license start***************
 * Copyright (c) 2003-2010  Cavium Networks (support@cavium.com). All rights 
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Networks nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.  

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries. 

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS" 
 * AND WITH ALL FAULTS AND CAVIUM  NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/




/*!
 * @file executive-config.h
 *
 * This file is a template for the executive-config.h file that each
 * application that uses the simple exec must provide.  Each application
 * should have an executive-config.h file in a directory named 'config'.
 * If the application uses other components, config files for those
 * components should be placed in the config directory as well.  The
 * macros defined in this file control the configuration and functionality
 * provided by the simple executive.  Available macros are commented out
 * and documented in this file.
 */

/*
 * File version info: $Id: executive-config.h 63001 2011-07-29 22:09:23Z panicker $
 *
 */
#ifndef __EXECUTIVE_CONFIG_H__
#define __EXECUTIVE_CONFIG_H__

/* Define to enable the use of simple executive DFA functions */
//#define CVMX_ENABLE_DFA_FUNCTIONS

/* Define to enable the use of simple executive packet output functions.
** For packet I/O setup enable the helper functions below. 
*/ 
#define CVMX_ENABLE_PKO_FUNCTIONS

/* Define to enable the use of simple executive timer bucket functions.
** Refer to cvmx-tim.[ch] for more information
*/
//#define CVMX_ENABLE_TIMER_FUNCTIONS

/* Define to enable the use of simple executive helper functions. These
** include many harware setup functions.  See cvmx-helper.[ch] for
** details.
*/
#define CVMX_ENABLE_HELPER_FUNCTIONS

/* CVMX_HELPER_FIRST_MBUFF_SKIP is the number of bytes to reserve before
** the beginning of the packet. If necessary, override the default  
** here.  See the IPD section of the hardware manual for MBUFF SKIP 
** details.*/ 
#define CVMX_HELPER_FIRST_MBUFF_SKIP 0

/* CVMX_HELPER_NOT_FIRST_MBUFF_SKIP is the number of bytes to reserve in each
** chained packet element. If necessary, override the default here */
#define CVMX_HELPER_NOT_FIRST_MBUFF_SKIP 0

/* CVMX_HELPER_ENABLE_IPD controls if the IPD is enabled in the helper
**  function. Once it is enabled the hardware starts accepting packets. You
**  might want to skip the IPD enable if configuration changes are need
**  from the default helper setup. If necessary, override the default here */
#define CVMX_HELPER_ENABLE_IPD 0

/* CVMX_HELPER_INPUT_TAG_TYPE selects the type of tag that the IPD assigns
** to incoming packets. */
#define CVMX_HELPER_INPUT_TAG_TYPE CVMX_POW_TAG_TYPE_ORDERED

/* The following select which fields are used by the PIP to generate
** the tag on INPUT
** 0: don't include
** 1: include */
#define CVMX_HELPER_INPUT_TAG_IPV6_SRC_IP	0
#define CVMX_HELPER_INPUT_TAG_IPV6_DST_IP   	0
#define CVMX_HELPER_INPUT_TAG_IPV6_SRC_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV6_DST_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV6_NEXT_HEADER 	0
#define CVMX_HELPER_INPUT_TAG_IPV4_SRC_IP	0
#define CVMX_HELPER_INPUT_TAG_IPV4_DST_IP   	0
#define CVMX_HELPER_INPUT_TAG_IPV4_SRC_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV4_DST_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV4_PROTOCOL	0
#define CVMX_HELPER_INPUT_TAG_INPUT_PORT	1

/* Select skip mode for input ports */
#define CVMX_HELPER_INPUT_PORT_SKIP_MODE	CVMX_PIP_PORT_CFG_MODE_SKIPL2

/* Define the number of queues per output port */
#define CVMX_HELPER_PKO_QUEUES_PER_PORT_INTERFACE0	1
#define CVMX_HELPER_PKO_QUEUES_PER_PORT_INTERFACE1	1

/* Configure PKO to use per-core queues (PKO lockless operation).
** Please see the related SDK documentation for PKO that illustrates
** how to enable and configure this option. */
//#define CVMX_ENABLE_PKO_LOCKLESS_OPERATION 1
//#define CVMX_HELPER_PKO_MAX_PORTS_INTERFACE0 8
//#define CVMX_HELPER_PKO_MAX_PORTS_INTERFACE1 8

/* Force backpressure to be disabled.  This overrides all other
** backpressure configuration */
#define CVMX_HELPER_DISABLE_RGMII_BACKPRESSURE 1

/* Disable the SPI4000's processing of backpressure packets and backpressure
** generation. When this is 1, the SPI4000 will not stop sending packets when
** receiving backpressure. It will also not generate backpressure packets when
** its internal FIFOs are full. */
#define CVMX_HELPER_DISABLE_SPI4000_BACKPRESSURE 1

/* CVMX_HELPER_SPI_TIMEOUT is used to determine how long the SPI initialization
** routines wait for SPI training. You can override the value using
** executive-config.h if necessary */
#define CVMX_HELPER_SPI_TIMEOUT 10

/* Select the number of low latency memory ports (interfaces) that
** will be configured.  Valid values are 1 and 2.
*/
#define CVMX_LLM_CONFIG_NUM_PORTS 2

/* Enable the fix for PKI-100 errata ("Size field is 8 too large in WQE and next
** pointers"). If CVMX_ENABLE_LEN_M8_FIX is set to 0, the fix for this errata will
** not be enabled.
** 0: Fix is not enabled
** 1: Fix is enabled, if supported by hardware
*/
//#define CVMX_ENABLE_LEN_M8_FIX  1

#if defined(CVMX_ENABLE_HELPER_FUNCTIONS) && !defined(CVMX_ENABLE_PKO_FUNCTIONS)
#define CVMX_ENABLE_PKO_FUNCTIONS
#endif

/* Enable setting up of TLB entries to trap NULL pointer references */
#define CVMX_CONFIG_NULL_POINTER_PROTECT	1

/* Enable debug and informational printfs */
#define CVMX_CONFIG_ENABLE_DEBUG_PRINTS 	1

/* Select IPD cache mode, default to get all blocks from DRAM (not cached in L2). */
#define CVMX_HELPER_IPD_DRAM_MODE               CVMX_IPD_OPC_MODE_STT

/* Allow attaching of the debugger to UART 1 or PCI debugging even when -debug is not
   supplied on the boot line. */
#define CVMX_DEBUG_ATTACH 1

/* Executive resource descriptions provided in cvmx-resources.config */
#include "cvmx-resources.config"

/* Resources used by components/common objects */
#include "common-config.h"

/* CVM PCI Driver resources in cvm-drv-resources.h */
#include "cvm-drv-resources.h"

#ifdef CAVIUM_COMPONENT_REQUIREMENT
/* global resource requirement */
cvmxconfig
{
	fau CVM_FAU_WQE_COUNT
		size = 8
		description = "Total Number of WQE received by all cores";

	fau CVM_FAU_WQE_LEN
		size = 8
		description = "Total Number of bytes in WQE received by all cores";

}
#endif

#endif

/* $Id: executive-config.h 63001 2011-07-29 22:09:23Z panicker $ */
