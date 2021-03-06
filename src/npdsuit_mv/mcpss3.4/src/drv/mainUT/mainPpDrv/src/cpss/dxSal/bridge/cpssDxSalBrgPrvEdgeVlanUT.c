/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
* cpssDxSalBrgPrvEdgeVlanUT.c
*
* DESCRIPTION:
*       Unit tests for cpssDxSalBrgPrvEdgeVlan, that provides
*       cpss Dx-Salsa implementation for Prestera Private Edge VLANs.
*
* FILE REVISION NUMBER:
*       $Revision: 1.1.1.1 $
*******************************************************************************/
/* includes */

#include <cpss/dxSal/bridge/cpssDxSalBrgPrvEdgeVlan.h>

#include <utf/utfMain.h>
#include <utf/private/prvUtfExtras.h>

/* Maximum value for trunk id. The max value from all searched sources where taken   */
#define MAX_TRUNK_ID_CNS             128

/* Default valid value for physical port id */
#define BRG_EDGE_VALID_PHY_PORT_CNS  0

/*----------------------------------------------------------------------------*/
/*
GT_STATUS cpssDxSalBrgPrvEdgeVlanEnable
(
    IN GT_U8    devNum,
    IN GT_BOOL  enable
)
*/
UTF_TEST_CASE_MAC(cpssDxSalBrgPrvEdgeVlanEnable)
{
/*
ITERATE_DEVICES
1.1. Call function with enable [GT_FALSE and GT_TRUE]. Expected: GT_OK for Salsa devices and GT_BAD_PARAM for others.
*/

    GT_STATUS                   st = GT_OK;

    GT_U8                       dev;
    GT_BOOL                     enable;

    /* prepare device iterator */
    st = prvUtfNextDeviceReset(&dev, UTF_DXSAL_FAMILY_SET_CNS);
    UTF_VERIFY_EQUAL0_PARAM_MAC(GT_OK, st);

    /* 1. Go over all active devices. */
    while (GT_OK == prvUtfNextDeviceGet(&dev, GT_TRUE))
    {
        /* 1.1. Call function with enable [GT_FALSE and GT_TRUE].           */
        /* Expected: GT_OK for Salsa devices and GT_BAD_PARAM for others.   */

        /* Call function with [enable==GT_FALSE] */
        enable = GT_FALSE;

        st = cpssDxSalBrgPrvEdgeVlanEnable(dev, enable);
        UTF_VERIFY_EQUAL2_STRING_MAC(GT_OK, st, "Salsa device: %d, %d",
                                     dev, enable);

        /* Call function with [enable==GT_TRUE] */
        enable = GT_TRUE;

        st = cpssDxSalBrgPrvEdgeVlanEnable(dev, enable);
        UTF_VERIFY_EQUAL2_STRING_MAC(GT_OK, st, "Salsa device: %d, %d",
                                     dev, enable);
    }

    /* 2. For not active devices check that function returns GT_BAD_PARAM. */

    /* prepare device iterator */
    st = prvUtfNextDeviceReset(&dev, UTF_DXSAL_FAMILY_SET_CNS);
    UTF_VERIFY_EQUAL0_PARAM_MAC(GT_OK, st);

    enable = GT_TRUE;

    /* go over all non active devices */
    while(GT_OK == prvUtfNextDeviceGet(&dev, GT_FALSE))
    {
        st = cpssDxSalBrgPrvEdgeVlanEnable(dev, enable);
        UTF_VERIFY_EQUAL1_PARAM_MAC(GT_NOT_APPLICABLE_DEVICE, st, dev);
    }

    /* 3. Call function with out of bound value for device id.*/

    dev = PRV_CPSS_MAX_PP_DEVICES_CNS;
    /* enable == GT_TRUE */

    st = cpssDxSalBrgPrvEdgeVlanEnable(dev, enable);
    UTF_VERIFY_EQUAL1_PARAM_MAC(GT_BAD_PARAM, st, dev);
}

/*----------------------------------------------------------------------------*/
/*
GT_STATUS cpssDxSalBrgPrvEdgeVlanPortEnable
(
    IN GT_U8      devNum,
    IN GT_U8      portNum,
    IN GT_BOOL    enable,
    IN GT_U8      dstPort,
    IN GT_U8      dstDev,
    IN GT_BOOL    dstTrunk
)
*/
UTF_TEST_CASE_MAC(cpssDxSalBrgPrvEdgeVlanPortEnable)
{
/*
ITERATE_DEVICES_PHY_PORTS (devNum, portNum)
1.1.1. Call function with enable [GT_FALSE] and dstPort [PRV_CPSS_MAX_PP_PORTS_NUM_CNS] (should be ignored), dstDev [PRV_CPSS_MAX_PP_DEVICES_CNS] (should be ignored), dstTrunk [GT_TRUE and GT_FALSE]. Expected: GT_OK for Salsa devices and GT_BAD_PARAM for others.
1.1.2. Check for out of range dstDev.  For Salsa device call function with enable [GT_TRUE], dstTrunk [GT_FALSE], dstDev [PRV_CPSS_MAX_PP_DEVICES_CNS], dstPort [0]. Expected: GT_BAD_PARAM.
1.1.3. Check for out of range dstPort.  For Salsa device call function with enable [GT_TRUE], dstTrunk [GT_FALSE], dstDev [0], dstPort [PRV_CPSS_MAX_PP_DEVICES_CNS]. Expected: GT_BAD_PARAM.
1.1.4. Check for trunk-reference support. Call function with enable [GT_TRUE], dstTrunk [GT_TRUE] and dstPort [15], destDev [PRV_CPSS_MAX_PP_DEVICES_CNS] (should be ignored). Expected: GT_OK for Salsa device and GT_BAD_PARAM for others.
1.1.5. Check for out of range trunk id while it's used. For Salsa device call function with enable [GT_TRUE], dstTrunk [GT_TRUE] and dstPort [MAX_TRUNK_ID_CNS = 128] (trunkId), dstDev [0]. Expected: NON GT_OK.
*/
    GT_STATUS                   st = GT_OK;

    GT_BOOL                     enable;
    GT_U8                       portNum;
    GT_U8                       devNum;
    GT_U8                       dstPort;
    GT_U8                       dstDev;
    GT_BOOL                     dstTrunk;

    st = prvUtfNextDeviceReset(&devNum, UTF_DXSAL_FAMILY_SET_CNS);
    UTF_VERIFY_EQUAL0_PARAM_MAC(GT_OK, st);

    /* 1. Go over all active devices (devNum). */
    while (GT_OK == prvUtfNextDeviceGet(&devNum, GT_TRUE))
    {
        st = prvUtfNextPhyPortReset(&portNum, devNum);
        UTF_VERIFY_EQUAL0_PARAM_MAC(GT_OK, st);

        /* 1.1. For each active device (devNum) id go over all active Physical portNums. */
        while (GT_OK == prvUtfNextPhyPortGet(&portNum, GT_TRUE))
        {
            /* 1.1.1. Call function with enable [GT_FALSE] and dstPort      */
            /* [PRV_CPSS_MAX_PP_PORTS_NUM_CNS] (should be ignored),         */
            /* dstDev [PRV_CPSS_MAX_PP_DEVICES_CNS] (should be ignored),    */
            /* dstTrunk [GT_TRUE and GT_FALSE].                             */
            /* Expected: GT_OK for Salsa and GT_BAD_PARAM for others.       */

            enable = GT_FALSE;

            dstPort = PRV_CPSS_MAX_PP_PORTS_NUM_CNS;
            dstDev = PRV_CPSS_MAX_PP_DEVICES_CNS;

            dstTrunk = GT_TRUE;

            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);
            UTF_VERIFY_EQUAL6_STRING_MAC(GT_OK, st,
                              "Salsa device: %d, %d, %d, %d, %d, %d",
                              devNum, portNum, enable, dstPort, dstDev, dstTrunk);

            dstTrunk = GT_FALSE;

            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);

            UTF_VERIFY_EQUAL6_STRING_MAC(GT_OK, st,
                     "Salsa device: %d, %d, %d, %d, %d, %d",
                     devNum, portNum, enable, dstPort, dstDev, dstTrunk);

            /* 1.1.2. Check for out of range dstDev.  For Salsa device call
               function with enable [GT_TRUE], dstTrunk [GT_FALSE], dstDev
               [PRV_CPSS_MAX_PP_DEVICES_CNS], dstPort [0].
               Expected: GT_BAD_PARAM.  */

            enable = GT_TRUE;
            dstTrunk = GT_FALSE;
            dstDev = PRV_CPSS_MAX_PP_DEVICES_CNS;
            dstPort = 0;

            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);
            UTF_VERIFY_EQUAL6_STRING_MAC(GT_BAD_PARAM, st,
                     "Salsa device: %d, %d, %d, %d, %d, %d",
                     devNum, portNum, enable, dstPort, dstDev, dstTrunk);

            /* 1.1.3. Check for out of range dstPort.  For Salsa device
               call function with enable [GT_TRUE], dstTrunk [GT_FALSE],
               dstDev [0], dstPort [PRV_CPSS_MAX_PP_DEVICES_CNS].
               Expected: GT_BAD_PARAM.  */

            enable = GT_TRUE;
            dstTrunk = GT_FALSE;
            dstDev = 0;
            dstPort = PRV_CPSS_MAX_PP_DEVICES_CNS;

            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);
            UTF_VERIFY_EQUAL6_STRING_MAC(GT_BAD_PARAM, st,
                     "Salsa device: %d, %d, %d, %d, %d, %d",
                     devNum, portNum, enable, dstPort, dstDev, dstTrunk);

            /* 1.1.4. Check for trunk-reference support. Call function
               with enable [GT_TRUE], dstTrunk [GT_TRUE] and dstPort [15],
               destDev [PRV_CPSS_MAX_PP_DEVICES_CNS] (should be ignored).
               Expected: GT_OK for Salsa device and GT_BAD_PARAM for others.*/

            enable = GT_TRUE;
            dstTrunk = GT_TRUE;
            dstDev = PRV_CPSS_MAX_PP_DEVICES_CNS;
            dstPort = 15;

            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);
            UTF_VERIFY_EQUAL6_STRING_MAC(GT_OK, st,
                     "Salsa device: %d, %d, %d, %d, %d, %d",
                     devNum, portNum, enable, dstPort, dstDev, dstTrunk);

            /* 1.1.5. Check for out of range trunk id while it's used.
               For Salsa device call function with enable [GT_TRUE],
               dstTrunk [GT_TRUE] and dstPort [MAX_TRUNK_ID_CNS = 128]
               (trunkId), dstDev [0]. Expected: NON GT_OK.  */

            enable = GT_TRUE;
            dstTrunk = GT_TRUE;
            dstDev = 0;
            dstPort = MAX_TRUNK_ID_CNS;

            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);
            UTF_VERIFY_NOT_EQUAL6_STRING_MAC(GT_OK, st,
                                  "Salsa device: %d, %d, %d, %d, %d, %d",
                                  devNum, portNum, enable, dstPort, dstDev, dstTrunk);
        }

        /* Only for Salsa test non-active/out-of-range PhyPort */
        enable = GT_FALSE;
        dstPort = 0;
        dstDev = 0;
        dstTrunk = GT_FALSE;

        st = prvUtfNextPhyPortReset(&portNum, devNum);
        UTF_VERIFY_EQUAL0_PARAM_MAC(GT_OK, st);

        /* 1.2. Go over all non active Physical portNums and active device id (devNum). */
        while (GT_OK == prvUtfNextPhyPortGet(&portNum, GT_FALSE))
        {
            /* 1.2.1. <Call function for non active portNum and valid parameters>.     */
            /* Expected: GT_BAD_PARAM.                                                 */
            st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                                  dstPort, dstDev, dstTrunk);
            UTF_VERIFY_EQUAL2_PARAM_MAC(GT_BAD_PARAM, st, devNum, portNum);
        }

        /* 1.3. Call with out of range for Physical portNum.                       */
        /* Expected: GT_BAD_PARAM.                                                */

        portNum = PRV_CPSS_MAX_PP_PORTS_NUM_CNS;
        /* enable == GT_FALSE   */
        /* dstPort == 0         */
        /* dstDev == 0          */
        /* dstTrunk == GT_FALSE */

        st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                              dstPort, dstDev, dstTrunk);
        UTF_VERIFY_EQUAL2_PARAM_MAC(GT_BAD_PARAM, st, devNum, portNum);

        /* 1.4. For active device check that function returns GT_OK        */
        /* for CPU port number.                                            */
        portNum = CPSS_CPU_PORT_NUM_CNS;

        st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                              dstPort, dstDev, dstTrunk);
        UTF_VERIFY_EQUAL2_PARAM_MAC(GT_BAD_PARAM, st, devNum, portNum);
    }

    portNum = BRG_EDGE_VALID_PHY_PORT_CNS;

    enable = GT_FALSE;
    dstPort = 0;
    dstDev = 0;
    dstTrunk = GT_FALSE;

    st = prvUtfNextDeviceReset(&devNum, UTF_DXSAL_FAMILY_SET_CNS);
    UTF_VERIFY_EQUAL0_PARAM_MAC(GT_OK, st);

    /*2. Go over all non active devices (devNum). */

    while(GT_OK == prvUtfNextDeviceGet(&devNum, GT_FALSE))
    {
        /* 2.1. <Call function for non active device (devNum) and valid parameters>. */
        /* Expected: GT_BAD_PARAM.                                          */

        st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                              dstPort, dstDev, dstTrunk);
        UTF_VERIFY_EQUAL1_PARAM_MAC(GT_NOT_APPLICABLE_DEVICE, st, devNum);
    }

    /* 3. Call function with out of range device id (devNum).   */
    /* Expected: GT_BAD_PARAM.                                  */
    devNum = PRV_CPSS_MAX_PP_DEVICES_CNS;
    /* enable == GT_FALSE   */
    /* dstPort == 0         */
    /* dstDev == 0          */
    /* dstTrunk == GT_FALSE */
    /* portNum == 0         */

    st = cpssDxSalBrgPrvEdgeVlanPortEnable(devNum, portNum, enable,
                                          dstPort, dstDev, dstTrunk);
    UTF_VERIFY_EQUAL1_PARAM_MAC(GT_BAD_PARAM, st, devNum);
}


/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*
 * Configuration of cpssDxSalBrgPrvEdgeVlan suit
 */
UTF_SUIT_BEGIN_TESTS_MAC(cpssDxSalBrgPrvEdgeVlan)
    UTF_SUIT_DECLARE_TEST_MAC(cpssDxSalBrgPrvEdgeVlanEnable)
    UTF_SUIT_DECLARE_TEST_MAC(cpssDxSalBrgPrvEdgeVlanPortEnable)
UTF_SUIT_END_TESTS_MAC(cpssDxSalBrgPrvEdgeVlan)


