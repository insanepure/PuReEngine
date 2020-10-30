#include "include/PuReEngine/StackTraceWin.h"
#ifdef _WIN32
namespace PuReEngine
{
    namespace Core
    {
        CStackTraceWin::CStackTraceWin()
        {
            CDbgHelpDLL::LoadDLL();
        }
        CStackTraceWin::~CStackTraceWin()
        {
        }

        void CStackTraceWin::Run()
        {
            if (!CDbgHelpDLL::RefreshModuleList(GetCurrentProcess()))
                CDbgHelpDLL::Initialize(GetCurrentProcess(), NULL, TRUE);
            //Initialize Variables
            STACKFRAME64 stackFrame;
            CONTEXT context;
            IMAGEHLP_SYMBOL64* pSymbol;
            IMAGEHLP_MODULE64 Module;
            IMAGEHLP_LINE64 Line;
            DWORD imageType;

            HANDLE Process = GetCurrentProcess();

            //Get our context
            RtlSecureZeroMemory(&context, sizeof(context));
            RtlCaptureContext(&context);

            memset(&stackFrame, 0, sizeof(stackFrame));

            //needed for our different machine types
        #ifdef _M_IX86
            imageType = IMAGE_FILE_MACHINE_I386;
            stackFrame.AddrPC.Offset = context.Eip;
            stackFrame.AddrPC.Mode = AddrModeFlat;
            stackFrame.AddrFrame.Offset = context.Ebp;
            stackFrame.AddrFrame.Mode = AddrModeFlat;
            stackFrame.AddrStack.Offset = context.Esp;
            stackFrame.AddrStack.Mode = AddrModeFlat;
        #elif _M_X64
            imageType = IMAGE_FILE_MACHINE_AMD64;
            stackFrame.AddrPC.Offset = context.Rip;
            stackFrame.AddrPC.Mode = AddrModeFlat;
            stackFrame.AddrFrame.Offset = context.Rsp;
            stackFrame.AddrFrame.Mode = AddrModeFlat;
            stackFrame.AddrStack.Offset = context.Rsp;
            stackFrame.AddrStack.Mode = AddrModeFlat;
        #elif _M_IA64
            imageType = IMAGE_FILE_MACHINE_IA64;
            stackFrame.AddrPC.Offset = context.StIIP;
            stackFrame.AddrPC.Mode = AddrModeFlat;
            stackFrame.AddrFrame.Offset = context.IntSp;
            stackFrame.AddrFrame.Mode = AddrModeFlat;
            stackFrame.AddrBStore.Offset = context.RsBSP;
            stackFrame.AddrBStore.Mode = AddrModeFlat;
            stackFrame.AddrStack.Offset = context.IntSp;
            stackFrame.AddrStack.Mode = AddrModeFlat;
        #else
        #error "Platform not supported!"
        #endif


            pSymbol = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64) + MAX_NAMELEN);
            RtlSecureZeroMemory(pSymbol, sizeof(IMAGEHLP_SYMBOL64) + MAX_NAMELEN);

            pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
            pSymbol->MaxNameLength = MAX_NAMELEN;

            RtlSecureZeroMemory(&Line, sizeof(Line));
            Line.SizeOfStruct = sizeof(Line);

            RtlSecureZeroMemory(&Module, sizeof(Module));
            Module.SizeOfStruct = sizeof(Module);

            //create and open file
            FILE* pFile;
            fopen_s(&pFile, "Stacktrace.txt", "w");

            while (CDbgHelpDLL::BackTrace(imageType, Process, GetCurrentThread(), &stackFrame, &context))
            {
                if (stackFrame.AddrPC.Offset == stackFrame.AddrReturn.Offset)
                    break;
                if (stackFrame.AddrPC.Offset != 0)
                {
                    DWORD64 symbolOffset = 0;
                    DWORD lineOffset = 0;
                    //get backtraced data
                    CDbgHelpDLL::GetSymbolFromAddress(Process, stackFrame.AddrPC.Offset, &symbolOffset, pSymbol);
                    CDbgHelpDLL::GetLineFromAddress(Process, stackFrame.AddrPC.Offset, &lineOffset, &Line);
                    CDbgHelpDLL::GetModuleFromAddress(Process, stackFrame.AddrPC.Offset, &Module);
                    //create string
                    char OutputString[1024];
                    char LineNumber[10];
                    sprintf_s(LineNumber, "%d", Line.LineNumber);
                    //copy our data into our string
                    strcpy_s(OutputString, Line.FileName);
                    strcat_s(OutputString, " (");
                    strcat_s(OutputString, LineNumber);
                    strcat_s(OutputString, "): ");
                    strcat_s(OutputString, pSymbol->Name);
                    strcat_s(OutputString, "\n");
                    //write string to file
                    fwrite(OutputString, sizeof(char), strlen(OutputString), pFile);
                }
            }
            //close file
            fclose(pFile);

            free(pSymbol);


        }
    }
}

#endif