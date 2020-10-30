#ifdef _WIN32
#ifndef _DBGHELPDLL_H_
#define _DBGHELPDLL_H_


#include <Windows.h>
#include <stdio.h>      /* printf, scanf, NULL */

#pragma warning (push)
#pragma warning (disable:4091) // a microsoft header has warnings. Very nice.
#include <dbghelp.h>
#pragma warning (pop)
// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief DBGHELP Wrapper
        ///
        class CDbgHelpDLL
        {
        public: //typedefs

            /// @brief Typedef of the Initialize Function from DBGHELP
            ///
            typedef BOOL(__stdcall *SymInit)(IN HANDLE hProcess, IN PSTR UserSearchPath, IN BOOL fInvadeProcess);

            /// @brief Typedef of the Refresh Function from DBGHELP
            ///
            typedef DWORD(__stdcall *SymRefresh)(IN HANDLE hProcess);

            /// @brief Typedef of the GetSymbol Function from DBGHELP
            ///
            typedef BOOL(__stdcall *SymGetSym)(IN HANDLE hProcess, IN DWORD64 dwAddr, OUT PDWORD64 pdwDisplacement, OUT PIMAGEHLP_SYMBOL64 Symbol);

            /// @brief Typedef of the FunctTableCallback Function from DBGHELP
            ///
            typedef PVOID(__stdcall *SymFuncTablAcc)(HANDLE hProcess, DWORD64 AddrBase);

            /// @brief Typedef of the GetLine Function from DBGHELP
            ///
            typedef BOOL(__stdcall *SymGetLine)(IN HANDLE hProcess, IN DWORD64 dwAddr, OUT PDWORD pdwDisplacement, OUT PIMAGEHLP_LINE64 Line);

            /// @brief Typedef of the GetModule Function from DBGHELP
            ///
            typedef DWORD64(__stdcall *SymGetModule)(IN HANDLE hProcess, IN DWORD64 dwAddr, OUT PIMAGEHLP_MODULE64 ModuleInfo);

            /// @brief Typedef of the GetModuleCallback Function from DBGHELP
            ///
            typedef DWORD64(__stdcall *SymGetModuleBase)(IN HANDLE hProcess, IN DWORD64 dwAddr);

            /// @brief Typedef of the Stackwalk Function from DBGHELP
            ///
            typedef BOOL(__stdcall *StckWlk)(
                DWORD MachineType,
                HANDLE hProcess,
                HANDLE hThread,
                LPSTACKFRAME64 StackFrame,
                PVOID ContextRecord,
                PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
                PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
                PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine,
                PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress);
        public: //functions

            /// @brief Loads all functions from the DLL
            ///
            /// @returns Boolean if an error occured or not
            ///
            static bool LoadDLL();
            /// @brief Backtraces the Stack and writes everything into the file
            /// 
            /// @remarks Writes everythign into Stacktrace.txt
            ///
            /// @param MachineType, standart is IMAGE_FILE_MACHINE_I386
            /// @param Process where it happend
            /// @param Thread where it happend
            /// @param Stackframe Struct needed for the function
            /// @param Context Struct needed for the function
            ///
            /// @returns Boolean if an error occured or not
            ///
            static bool BackTrace(DWORD a_MachineType, HANDLE a_hProcess, HANDLE a_hThread, LPSTACKFRAME64 a_StackFrame, PVOID a_ContextRecord);
            /// @brief Initialize Function we load from the DLL
            /// 
            static SymInit Initialize;
            /// @brief Refresh Function we load from the DLL
            /// 
            static SymRefresh RefreshModuleList;
            /// @brief GetSymbol Function we load from the DLL
            /// 
            static SymGetSym GetSymbolFromAddress;
            /// @brief FunctionTableCallback Function we load from the DLL
            /// 
            static SymFuncTablAcc FunctionTableAccess;
            /// @brief GetLine Function we load from the DLL
            /// 
            static SymGetLine GetLineFromAddress;
            /// @brief GetModule Function we load from the DLL
            /// 
            static SymGetModule GetModuleFromAddress;
            /// @brief GetModuleCallback Function we load from the DLL
            /// 
            static SymGetModuleBase GetModuleBase;
        private:
            /// @brief StackWalk64 Function from DBGHELP we load from the DLL
            /// 
            static StckWlk StackWalk;
        };
    }
}

#endif _DBGHELPDLL_H_
#endif