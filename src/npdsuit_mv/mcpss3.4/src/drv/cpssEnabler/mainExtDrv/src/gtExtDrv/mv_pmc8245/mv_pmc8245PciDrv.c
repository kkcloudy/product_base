/*******************************************************************************
*              Copyright 2001, GALILEO TECHNOLOGY, LTD.
*
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL. NO RIGHTS ARE GRANTED
* HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT OF MARVELL OR ANY THIRD
* PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE DISCRETION TO REQUEST THAT THIS
* CODE BE IMMEDIATELY RETURNED TO MARVELL. THIS CODE IS PROVIDED "AS IS".
* MARVELL MAKES NO WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS
* ACCURACY, COMPLETENESS OR PERFORMANCE. MARVELL COMPRISES MARVELL TECHNOLOGY
* GROUP LTD. (MTGL) AND ITS SUBSIDIARIES, MARVELL INTERNATIONAL LTD. (MIL),
* MARVELL TECHNOLOGY, INC. (MTI), MARVELL SEMICONDUCTOR, INC. (MSI), MARVELL
* ASIA PTE LTD. (MAPL), MARVELL JAPAN K.K. (MJKK), GALILEO TECHNOLOGY LTD. (GTL)
* AND GALILEO TECHNOLOGY, INC. (GTI).
********************************************************************************
* ppc8240PciDrv.c
*
* DESCRIPTION:
*       Includes PCI functions wrappers implementation for the PrPMC600 BSP.
*
* DEPENDENCIES:
*       -   System controller.
*       -   BSP.
*
* FILE REVISION NUMBER:
*       $Revision: 1.1.1.1 $
*
*******************************************************************************/

#include <gtExtDrv/drivers/gtPciDrv.h>
#include "vxWorks.h"
#include "drv/pci/pciConfigLib.h"

/* These header file placed in the BSP */
#include "mpc8245.h"
#include "drv/sysEpic.h"


/*#include <pci.target.h>
  */
/*#include "pci.h"*/


/*******************************************************************************
* internal definitions
*******************************************************************************/
#ifdef PRESTERA_DEBUG
#define PCI_DRV_DEBUG
#endif

#ifdef PCI_DRV_DEBUG
#define DBG_INFO(x)     osPrintf x
#else
#define DBG_INFO(x)
#endif


/*******************************************************************************
* extDrvPciConfigWriteReg
*
* DESCRIPTION:
*       This routine write register to the PCI configuration space.
*
* INPUTS:
*       busNo    - PCI bus number.
*       devSel   - the device devSel.
*       funcNo   - function number.
*       regAddr  - Register offset in the configuration space.
*       data     - data to write.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - othersise.
*
* COMMENTS:
*
*******************************************************************************/
GT_STATUS extDrvPciConfigWriteReg
(
    IN  GT_U32  busNo,
    IN  GT_U32  devSel,
    IN  GT_U32  funcNo,
    IN  GT_U32  regAddr,
    IN  GT_U32  data
)
{
    GT_STATUS ret;
    /* call bsp write function */
    ret = pciConfigOutLong(busNo, devSel, funcNo, regAddr, data);
    /* check whether success */
    if(ret != 0)
    {
        return GT_FAIL;
    }

    DBG_INFO("Pci config write reg");
     return GT_OK;
}



/*******************************************************************************
* extDrvPciConfigReadReg
*
* DESCRIPTION:
*       This routine read register from the PCI configuration space.
*
* INPUTS:
*       busNo    - PCI bus number.
*       devSel   - the device devSel.
*       funcNo   - function number.
*       regAddr  - Register offset in the configuration space.
*
* OUTPUTS:
*       data     - the read data.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - othersise.
*
* COMMENTS:
*
*******************************************************************************/
GT_STATUS extDrvPciConfigReadReg
(
    IN  GT_U32  busNo,
    IN  GT_U32  devSel,
    IN  GT_U32  funcNo,
    IN  GT_U32  regAddr,
    OUT GT_U32  *data
)
{
    GT_STATUS ret;
    /* call bsp read function */
    ret = pciConfigInLong(busNo, devSel, funcNo, regAddr, (int*)data);
    /* check whether success */
    if(ret != 0)
    {
        return GT_FAIL;
    }
    DBG_INFO("Pci config read reg");
    return GT_OK;
}



/*******************************************************************************
* extDrvPciFindDev
*
* DESCRIPTION:
*       This routine returns the next instance of the given device (defined by
*       vendorId & devId).
*
* INPUTS:
*       vendorId - The device vendor Id.
*       devId    - The device Id.
*       instance - The requested device instance.
*
* OUTPUTS:
*       busNo    - PCI bus number.
*       devSel   - the device devSel.
*       funcNo   - function number.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - othersise.
*
* COMMENTS:
*
*******************************************************************************/
GT_STATUS extDrvPciFindDev
(
    IN  GT_U16  vendorId,
    IN  GT_U16  devId,
    IN  GT_U32  instance,
    OUT GT_U32  *busNo,
    OUT GT_U32  *devSel,
    OUT GT_U32  *funcNo
)
{
    STATUS ret;
    /* call bsp read function */
    ret = pciFindDevice(vendorId, devId, instance, (int*)busNo,
                        (int*)devSel, (int*)funcNo);
    /* check whether success */
    if(ret != OK)
    {
        return GT_FAIL;
    }
    return GT_OK;
}


/*******************************************************************************
* extDrvGetPciIntVec
*
* DESCRIPTION:
*       This routine return the PCI interrupt vector.
*
* INPUTS:
*       pciInt - PCI interrupt number.
*
* OUTPUTS:
*       intVec - PCI interrupt vector.
*
* RETURNS:
*       GT_OK      - on success.
*       GT_FAIL    - otherwise.
*
* COMMENTS:
*       None.
*
*******************************************************************************/
GT_STATUS extDrvGetPciIntVec
(
    IN  GT_PCI_INT  pciInt,
    OUT void        **intVec
)
{
    /* check parameters */
    if(intVec == NULL)
    {
        return GT_BAD_PARAM;
    }
    /* get the PCI interrupt vector */
    /* This function located in the BSP directory */
    *intVec  = (void *)getPciInterruptVector();
    return GT_OK;
}

/*******************************************************************************
* extDrvGetIntMask
*
* DESCRIPTION:
*       This routine return the PCI interrupt vector.
*
* INPUTS:
*       pciInt - PCI interrupt number.
*
* OUTPUTS:
*       intMask - PCI interrupt mask.
*
* RETURNS:
*       GT_OK      - on success.
*       GT_FAIL    - otherwise.
*
* COMMENTS:
*       PCI interrupt mask should be used for interrupt disable/enable.
*
*******************************************************************************/
GT_STATUS extDrvGetIntMask
(
    IN  GT_PCI_INT  pciInt,
    OUT GT_U32      *intMask
)
{
    void        *intVec;

    /* check parameters */
    if(intMask == NULL)
    {
        return GT_BAD_PARAM;
    }
    /* get the PCI interrupt vector */
    extDrvGetPciIntVec(pciInt, &intVec);

    *intMask = (GT_U32)intVec;

    return GT_OK;
}

/*******************************************************************************
* extDrvEnableCombinedWrites
*
* DESCRIPTION:
*       This function enables / disables the Pci writes / reads combining
*       feature.
*       Some system controllers support combining memory writes / reads. When a
*       long burst write / read is required and combining is enabled, the master
*       combines consecutive write / read transactions, if possible, and
*       performs one burst on the Pci instead of two. (see comments)
*
* INPUTS:
*       enWrCombine - GT_TRUE enables write requests combining.
*       enRdCombine - GT_TRUE enables read requests combining.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK               - on sucess,
*       GT_NOT_SUPPORTED    - if the controller does not support this feature,
*       GT_FAIL             - otherwise.
*
* COMMENTS:
*       1.  Example for combined write scenario:
*           The controller is required to write a 32-bit data to address 0x8000,
*           while this transaction is still in progress, a request for a write
*           operation to address 0x8004 arrives, in this case the two writes are
*           combined into a single burst of 8-bytes.
*
*******************************************************************************/
GT_STATUS extDrvEnableCombinedPciAccess
(
    IN  GT_BOOL     enWrCombine,
    IN  GT_BOOL     enRdCombine
)
{
    if((enWrCombine == GT_TRUE) || (enRdCombine == GT_TRUE))
    {
        return GT_NOT_SUPPORTED;
    }

    return GT_OK;
}

/*******************************************************************************
* extDrvPciDoubleWrite
*
* DESCRIPTION:
*        This routine will write a 64-bit data  to given address
*
* INPUTS:
*        address - address to write to
*       word1 - the first half of double word to write (MSW)
*       word2 - the second half of double word to write (LSW)
*
* OUTPUTS:
*      none
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
* COMMENTS:
*
*******************************************************************************/
GT_STATUS extDrvPciDoubleWrite
(
    IN  GT_U32 address,
    IN  GT_U32 word1, 
    IN  GT_U32 word2
)
{
	return GT_NOT_SUPPORTED;
}

/*******************************************************************************
* extDrvPciDoubleRead
*
* DESCRIPTION:
*        This routine will read a 64-bit data  from given address
*
* INPUTS:
*        address - address to read from
*
* OUTPUTS:
*       data     -  pointer for the received data.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
* COMMENTS:
*
*******************************************************************************/
GT_STATUS extDrvPciDoubleRead
(
    IN  GT_U32  address,
    OUT GT_U64  *dataPtr
)
{
	return GT_NOT_SUPPORTED;
}
