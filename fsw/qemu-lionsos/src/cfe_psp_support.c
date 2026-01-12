#include <microkit.h>
#include <sel4/sel4.h>

#include "common_types.h"
#include "osapi-printf.h"
#include "target_config.h"

#define CFE_PSP_CPU_ID        (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_CPU_NAME      (GLOBAL_CONFIGDATA.Default_CpuName)
#define CFE_PSP_SPACECRAFT_ID (GLOBAL_CONFIGDATA.Default_SpacecraftId)

void CFE_PSP_Restart(uint32 resetType)
{
    OS_printf("%s():reset type %d\n", __func__, resetType);
    OS_printf("Restart functionality not implemented, cFS will now halt\n");
    seL4_DebugHalt();
}

void CFE_PSP_Panic(int32 ErrorCode)
{
    OS_printf("%s():error code %d\n", __func__, ErrorCode);
    OS_printf("cFS will now halt\n");
    seL4_DebugHalt();
}

uint32 CFE_PSP_GetProcessorId(void)
{
    return CFE_PSP_CPU_ID;
}

uint32 CFE_PSP_GetSpacecraftId(void)
{
    return CFE_PSP_SPACECRAFT_ID;
}

const char *CFE_PSP_GetProcessorName(void)
{
    return CFE_PSP_CPU_NAME;
}
