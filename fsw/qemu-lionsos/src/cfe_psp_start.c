#include <sel4/sel4.h>
#include <microkit.h>

#include "target_config.h"
#include "osapi-common.h"
#include "osapi-error.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_module.h"

#define CFE_PSP_MAIN_FUNCTION       (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)
#define CFE_PSP_1HZ_FUNCTION        (*GLOBAL_CONFIGDATA.CfeConfig->System1HzISR)
#define CFE_PSP_NONVOL_STARTUP_FILE (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)
#define CFE_PSP_CPU_ID              (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_CPU_NAME            (GLOBAL_CONFIGDATA.Default_CpuName)
#define CFE_PSP_SPACECRAFT_ID       (GLOBAL_CONFIGDATA.Default_SpacecraftId)

void OS_Application_Startup(void)
{
    uint32 reset_type = CFE_PSP_RST_TYPE_POWERON;
    uint32 reset_subtype = CFE_PSP_RST_SUBTYPE_UNDEFINED_RESET;
    int32 status;

    status = OS_API_Init();

    if (status != OS_SUCCESS)
    {
        /* Unrecoverable error if OS_API_Init() fails */
        /* Use primitives here as OS_printf may not work */
        printf("CFE_PSP: OS_API_Init() failure\n");
        CFE_PSP_Panic(status);
    }

    osal_id_t fs;
    status = OS_FileSysAddFixedMap(&fs, "/cf", "/cf");

    if (status != OS_SUCCESS)
    {
        OS_printf("CFE_PSP: OS_FileSysAddFixedMap() failure: %d\n", status);
    }

    CFE_PSP_SetupReservedMemoryMap();
    CFE_PSP_ModuleInit();
    CFE_PSP_InitProcessorReservedMemory(reset_type);
    CFE_PSP_MAIN_FUNCTION(reset_type, reset_subtype, 1, CFE_PSP_NONVOL_STARTUP_FILE);
}
