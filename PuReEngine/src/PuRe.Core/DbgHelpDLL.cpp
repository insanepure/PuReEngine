#include "include/PuReEngine/DbgHelpDLL.h"
#ifdef _WIN32
namespace PuReEngine
{
    namespace Core
    {
        CDbgHelpDLL::SymInit CDbgHelpDLL::Initialize;
        CDbgHelpDLL::SymRefresh CDbgHelpDLL::RefreshModuleList;
        CDbgHelpDLL::SymGetSym CDbgHelpDLL::GetSymbolFromAddress;
        CDbgHelpDLL::SymFuncTablAcc CDbgHelpDLL::FunctionTableAccess;
        CDbgHelpDLL::SymGetLine CDbgHelpDLL::GetLineFromAddress;
        CDbgHelpDLL::SymGetModule CDbgHelpDLL::GetModuleFromAddress;
        CDbgHelpDLL::SymGetModuleBase CDbgHelpDLL::GetModuleBase;
        CDbgHelpDLL::StckWlk CDbgHelpDLL::StackWalk;

        bool CDbgHelpDLL::BackTrace(DWORD a_MachineType, HANDLE a_hProcess, HANDLE a_hThread, LPSTACKFRAME64 a_StackFrame, PVOID a_ContextRecord)
        {
            return StackWalk(a_MachineType, a_hProcess, a_hThread, a_StackFrame, a_ContextRecord, NULL, FunctionTableAccess, GetModuleBase, NULL) == 1;
        }

        bool CDbgHelpDLL::LoadDLL()
        {
            HMODULE m_DbgHelpDLL = LoadLibrary(TEXT("dbghelp.dll"));
            if (m_DbgHelpDLL == NULL)
                printf("Error while loading dbghelp.dll\n");
            else
            {
                Initialize = (SymInit)GetProcAddress(m_DbgHelpDLL, "SymInitialize");
                RefreshModuleList = (SymRefresh)GetProcAddress(m_DbgHelpDLL, "SymRefreshModuleList");
                GetSymbolFromAddress = (SymGetSym)GetProcAddress(m_DbgHelpDLL, "SymGetSymFromAddr64");
                FunctionTableAccess = (SymFuncTablAcc)GetProcAddress(m_DbgHelpDLL, "SymFunctionTableAccess64");
                GetLineFromAddress = (SymGetLine)GetProcAddress(m_DbgHelpDLL, "SymGetLineFromAddr64");
                GetModuleFromAddress = (SymGetModule)GetProcAddress(m_DbgHelpDLL, "SymGetModuleInfo64");
                GetModuleBase = (SymGetModuleBase)GetProcAddress(m_DbgHelpDLL, "SymGetModuleBase64");
                StackWalk = (StckWlk)GetProcAddress(m_DbgHelpDLL, "StackWalk64");
                if (Initialize == NULL || RefreshModuleList == NULL || GetSymbolFromAddress == NULL || StackWalk == NULL
                    || FunctionTableAccess == NULL || GetLineFromAddress == NULL || GetModuleFromAddress == NULL)
                {
                    printf("Could not load functions from dbghelp.dll\n");
                    FreeLibrary(m_DbgHelpDLL);
                    return false;
                }
                return true;
            }
            return false;
        }
    }
}
#endif