#include "cfe_psp_error.h"
#include "cfe_psp_exception_api.h"
#include "cfe_psp_exceptionstorage_api.h"

void CFE_PSP_AttachExceptions(void)
{
    CFE_PSP_Exception_Reset();
}

int32 CFE_PSP_ExceptionGetSummary_Impl(const struct CFE_PSP_Exception_LogData *Buffer, char *ReasonBuf, uint32 ReasonSize)
{
    return CFE_PSP_ERROR_NOT_IMPLEMENTED;
}

void CFE_PSP_SetDefaultExceptionEnvironment(void) {}
