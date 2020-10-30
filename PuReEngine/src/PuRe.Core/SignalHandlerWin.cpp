#include "include/PuReEngine/SignalHandlerWin.h"
#ifdef _WIN32
namespace PuReEngine
{
    namespace Core
    {
        CStackTraceWin* CSignalHandlerWin::m_pStackTrace;

        void CSignalHandlerWin::SignalHandle(const int a_Signal)
        {
            if (a_Signal == SIGSEGV || a_Signal == SIGABRT)
                m_pStackTrace->Run();

        }

        CSignalHandlerWin::CSignalHandlerWin()
        {
            this->m_pStackTrace = new CStackTraceWin();
            signal(SIGSEGV, CSignalHandlerWin::SignalHandle);
            signal(SIGABRT, CSignalHandlerWin::SignalHandle);
        }

        CSignalHandlerWin::~CSignalHandlerWin()
        {
            delete this->m_pStackTrace;
        }

    }
}
#endif