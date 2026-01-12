#include <string.h>

#include "cfe_psp_memory.h"
#include "cfe_psp_error.h"
#include "cfe_psp_memrange_api.h"

char Reset_Storage[0x1f988 /* sizeof(CFE_ES_ResetData_t) */];

CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap = {
    .ResetMemory = {.BlockPtr = Reset_Storage, .BlockSize = 0x1f988}
};

int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    int32 return_code;

    if (SizeOfCDS == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *SizeOfCDS = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize;
        return_code = OS_SUCCESS;
    }

    return return_code;
}

int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
    uint8 *CopyPtr;
    int32  return_code;

    if (PtrToDataToWrite == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize) &&
            ((CDSOffset + NumBytes) <= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize))
        {
            CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
            CopyPtr += CDSOffset;
            memcpy((char*) CopyPtr, (char*) PtrToDataToWrite, NumBytes);

            return_code = OS_SUCCESS;
        }
        else
        {
            return_code = OS_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return return_code;
}

int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes)
{
    uint8 *CopyPtr;
    int32  return_code;

    if (PtrToDataToRead == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize) &&
            ((CDSOffset + NumBytes) <= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize))
        {
            CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
            CopyPtr += CDSOffset;
            memcpy((char*) PtrToDataToRead, (char*) CopyPtr, NumBytes);

            return_code = OS_SUCCESS;
        }
        else
        {
            return_code = OS_ERROR;
        }

    } /* end if PtrToDataToRead == NULL */

    return return_code;
}

int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    int32 return_code;

    if (SizeOfResetArea == NULL || PtrToResetArea == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *PtrToResetArea = (cpuaddr) CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr;
        *SizeOfResetArea = CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
        return_code = OS_SUCCESS;
    }

    return return_code;
}

int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    int32 return_code;

    if (SizeOfVolDisk == NULL || PtrToVolDisk == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *PtrToVolDisk = (cpuaddr) CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr;
        *SizeOfVolDisk = CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;
        return_code = OS_SUCCESS;
    }

    return return_code;
}

int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
    return CFE_PSP_ERROR_NOT_IMPLEMENTED;
}
