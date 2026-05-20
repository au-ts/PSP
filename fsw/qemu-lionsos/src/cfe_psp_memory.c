#include <string.h>

#include "cfe_psp_memory.h"
#include "cfe_psp_config.h"
#include "cfe_psp_error.h"
#include "target_config.h"

#define CFE_PSP_CDS_SIZE (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)
#define CFE_PSP_RAMDISK_SIZE (GLOBAL_CONFIGDATA.CfeConfig->RamDiskTotalSectors * GLOBAL_CONFIGDATA.CfeConfig->RamDiskSectorSize)

struct {
    CFE_PSP_ReservedMemoryBootRecord_t BootRecord;
    CFE_PSP_ExceptionStorage_t ExceptionStorage;
    char ResetMemory[0x1f998 /* sizeof(CFE_ES_ResetData_t) */];
    char CDSMemory[0x100000 /* 1 MiB */];
    char VolatileDiskMemory[0x100000 /* 1 MiB */];
    char UserReservedMemory[0x100000 /* 1 MiB */];
} CFE_PSP_LionsOSMemoryStorage;

CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap = {
    .BootPtr = &CFE_PSP_LionsOSMemoryStorage.BootRecord,
    .ExceptionStoragePtr = &CFE_PSP_LionsOSMemoryStorage.ExceptionStorage,
    .ResetMemory = {
        .BlockPtr = &CFE_PSP_LionsOSMemoryStorage.ResetMemory,
        .BlockSize = sizeof(CFE_PSP_LionsOSMemoryStorage.ResetMemory)
    },
    .VolatileDiskMemory = {
        .BlockPtr = &CFE_PSP_LionsOSMemoryStorage.VolatileDiskMemory,
        .BlockSize = sizeof(CFE_PSP_LionsOSMemoryStorage.VolatileDiskMemory)
    },
    .CDSMemory = {
        .BlockPtr = &CFE_PSP_LionsOSMemoryStorage.CDSMemory,
        .BlockSize = sizeof(CFE_PSP_LionsOSMemoryStorage.CDSMemory)
    },
    .UserReservedMemory = {
        .BlockPtr = &CFE_PSP_LionsOSMemoryStorage.UserReservedMemory,
        .BlockSize = sizeof(CFE_PSP_LionsOSMemoryStorage.UserReservedMemory)
    }
};

int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    if (SizeOfCDS == NULL) {
        return OS_ERROR;
    }

    *SizeOfCDS = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize;
    return OS_SUCCESS;
}

int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
    if (PtrToDataToWrite == NULL)
    {
        return OS_ERROR;
    }

    if (CDSOffset >= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize || (CDSOffset + NumBytes) > CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize)
    {
        return OS_ERROR;
    }

    memcpy(CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr, PtrToDataToWrite, NumBytes);
    return OS_SUCCESS;
}

int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes)
{
    if (PtrToDataToRead == NULL)
    {
        return OS_ERROR;
    }

    if (CDSOffset >= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize || (CDSOffset + NumBytes) > CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize)
    {
        return OS_ERROR;
    }

    memcpy(PtrToDataToRead, CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr, NumBytes);
    return OS_SUCCESS;
}

int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    if (SizeOfResetArea == NULL || PtrToResetArea == NULL)
    {
        return OS_ERROR;
    }

    *PtrToResetArea = (cpuaddr) CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr;
    *SizeOfResetArea = CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
    return OS_SUCCESS;
}

int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    if (SizeOfVolDisk == NULL || PtrToVolDisk == NULL)
    {
        return OS_ERROR;
    }

    *PtrToVolDisk = (cpuaddr) CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr;
    *SizeOfVolDisk = CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;
    return OS_SUCCESS;
}

int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea)
{
    if (SizeOfUserArea == NULL || PtrToUserArea == NULL)
    {
        return OS_ERROR;
    }

    *PtrToUserArea = (cpuaddr) CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr;
    *SizeOfUserArea = CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize;
    return OS_SUCCESS;
}

void CFE_PSP_SetupReservedMemoryMap(void)
{
    /* The LionsOS libc layer does not support memory-mapped files,
     * so the contents of all reserved memory blocks will be lost on reset */

    if (CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize < CFE_PSP_RESET_AREA_SIZE)
    {
        OS_printf(
            "CFE_PSP: Reset memory too small to boot (have %zu, need %d)\n",
            CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize,
            CFE_PSP_RESET_AREA_SIZE
        );

        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    if (CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr == NULL)
    {
        OS_printf(
            "CFE_PSP: Volatile disk memory too small to boot (have %zu, need %d)\n",
            CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize,
            CFE_PSP_RAMDISK_SIZE
        );

        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    if (CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr == NULL)
    {
        OS_printf(
            "CFE_PSP: CDS memory too small to boot (have %zu, need %d)\n",
            CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize,
            CFE_PSP_CDS_SIZE
        );

        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    if (CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr == NULL)
    {
        OS_printf(
            "CFE_PSP: User reserved memory too small to boot (have %zu, need %d)\n",
            CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize,
            CFE_PSP_USER_RESERVED_SIZE
        );

        CFE_PSP_Panic(CFE_PSP_ERROR);
    }
}

int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
    return CFE_PSP_SUCCESS;
}

int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
    return CFE_PSP_ERROR_NOT_IMPLEMENTED;
}
