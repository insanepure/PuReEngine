#include "include/PuReEngine/SignalHandlerLinux.h"
#ifdef __linux__
namespace PuReEngine
{
    namespace Core
    {
        CStackTraceLinux* CSignalHandlerLinux::m_pStackTrace;

        void CSignalHandlerLinux::SignalHandle(const int a_Signal)
        {
            if (a_Signal == SIGSEGV || a_Signal == SIGABRT)
                m_pStackTrace->Run();

        }

        CSignalHandlerLinux::CSignalHandlerLinux()
        {
            this->m_pStackTrace = new CStackTraceLinux();
            signal(SIGSEGV, CSignalHandlerLinux::SignalHandle);
            signal(SIGABRT, CSignalHandlerLinux::SignalHandle);
        }

        CSignalHandlerLinux::~CSignalHandlerLinux()
        {
            delete this->m_pStackTrace;
        }

    }
}
#endif