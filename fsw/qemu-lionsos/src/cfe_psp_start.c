#include <sel4/sel4.h>
#include <microkit.h>

#include "target_config.h"
#include "osapi-common.h"
#include "osapi-error.h"

#define CFE_PSP_MAIN_FUNCTION       (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)
#define CFE_PSP_1HZ_FUNCTION        (*GLOBAL_CONFIGDATA.CfeConfig->System1HzISR)
#define CFE_PSP_NONVOL_STARTUP_FILE (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)
#define CFE_PSP_CPU_ID              (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_CPU_NAME            (GLOBAL_CONFIGDATA.Default_CpuName)
#define CFE_PSP_SPACECRAFT_ID       (GLOBAL_CONFIGDATA.Default_SpacecraftId)

void OS_Application_Startup(void)
{
    uint32 reset_type;
    uint32 reset_subtype;
    int32 status;

    reset_type = 0;
    reset_subtype = 0;

    status = OS_API_Init();

    if (status != OS_SUCCESS)
    {
        /* Irrecoverable error if OS_API_Init() fails */
        /* Use microkit primitives here as OS_printf may not work */
        microkit_dbg_puts("OS_Application_Startup():OS_API_Init failure, status code ");
        microkit_dbg_put32(status);
        microkit_dbg_putc('\n');
        seL4_DebugHalt();
    }

    CFE_PSP_MAIN_FUNCTION(reset_type, reset_subtype, 1, CFE_PSP_NONVOL_STARTUP_FILE);
}
