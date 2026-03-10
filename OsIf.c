/** *****************************************************************************************************
 * SEMIDRIVE Copyright Statement                                                                        *
 * Copyright (c) SEMIDRIVE. All rights reserved                                                         *
 *                                                                                                      *
 * This software and all rights therein are owned by SEMIDRIVE, and are                                 *
 * protected by copyright law and other relevant laws, regulations and                                  *
 * protection. Without SEMIDRIVE's prior written consent and/or related rights,                         *
 * please do not use this software or any potion thereof in any form or by any                          *
 * means. You may not reproduce, modify or distribute this software except in                           *
 * compliance with the License. Unless required by applicable law or agreed to                          *
 * in writing, software distributed under the License is distributed on                                 *
 * an 'AS IS' basis, WITHOUT WARRANTIES OF ANY KIND, either express or implied.                         *
 *                                                                                                      *
 *******************************************************************************************************/
/** *****************************************************************************************************
 * \file     OsIf.c                                                                                     *
 * \brief    Semidrive os abstract layer                                                                *
 *                                                                                                      *
 * <table>                                                                                              *
 * <tr><th>Date           <th>Version                                                                   *
 * <tr><td>2023/08/26     <td>1.0.0                                                                     *
 * </table>                                                                                             *
 *******************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "OsIf.h"

#ifdef AUTOSAR_OS_NOT_USED
/* In order to avoid data abort caused by the probability of bus error due to
    the misalignment of byte loading when XIP is not open when the cache is not
    open. */
#ifndef SEMIDRIVE_E3LL_SERIES
static const uint32 Cpu_IndexMap[CPU_MAX_CORE_NUMBER] = {CPU_INDEX_0,
                                                         CPU_INDEX_3,
                                                         CPU_INDEX_4,
                                                         CPU_INDEX_1,
                                                         CPU_INDEX_2
                                                        };
#endif
/*================================================================================================*/
/**
* @brief OsIf_GetCoreID
* @details Function used to get the ID of the currently executing thread
*/
/*================================================================================================*/

uint8 OsIf_GetCoreID(void)
{
    uint8 coreId = CPU_MAX_CORE_NUMBER;
    uint8 cpuId = OsIf_GetCpuId();
#ifndef SEMIDRIVE_E3LL_SERIES
    coreId = (uint8)Cpu_IndexMap[cpuId];
#else
    coreId = cpuId;
#endif
    return coreId;
}

#endif /* AUTOSAR_OS_NOT_USED */

uint32 Mcal_AddressConvert(uint32 cpuAddr)
{
    uint32 tcmBaseAddr;
    uint32 tcmAddrsize;
    uint32 convertAddr = cpuAddr;
    uint8 coreId = Mcal_GetCpuIndex();

    if (CPU_INDEX_0 == coreId)
    {
        tcmBaseAddr = CORE_SF_TCM_BASE;
        tcmAddrsize = CORE_SF_TCM_SIZE;
    }
    else if (CPU_INDEX_1 == coreId)
    {
        tcmBaseAddr = CORE_SX0_TCM_BASE;
        tcmAddrsize = CORE_SX0_TCM_SIZE;
    }
    else if (CPU_INDEX_2 == coreId)
    {
        tcmBaseAddr = CORE_SX1_TCM_BASE;
        tcmAddrsize = CORE_SX1_TCM_SIZE;
    }
    else if (CPU_INDEX_3 == coreId)
    {
        tcmBaseAddr = CORE_SP0_TCM_BASE;
        tcmAddrsize = CORE_SP0_TCM_SIZE;
    }
    else if (CPU_INDEX_4 == coreId)
    {
        tcmBaseAddr = CORE_SP1_TCM_BASE;
        tcmAddrsize = CORE_SP1_TCM_SIZE;
    }
    else
    {
        tcmAddrsize = 0;
        tcmBaseAddr = 0;
    }

    if (cpuAddr < tcmAddrsize)
    {
        convertAddr = cpuAddr + tcmBaseAddr;
    }

    return convertAddr;
}



#ifdef __cplusplus
}
#endif

/* End of file */
