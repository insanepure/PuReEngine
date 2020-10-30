#ifdef _WIN32
#ifndef _STACKTRACEWIN_H_
#define _STACKTRACEWIN_H_

#include "DbgHelpDLL.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        enum { MAX_NAMELEN = 1024 };

        /// @brief StackTrace Structure
        ///
        struct SStackTrace
        {
            char FileName[MAX_NAMELEN];
            int Line;
            char Function[MAX_NAMELEN];
        };
        /// @brief StackTrace Class
        ///
        class CStackTraceWin
        {
        public:
            /// @brief Initializes StackTrace
            ///
            CStackTraceWin();
            /// @brief Destroyes StackTrace
            ///
            ~CStackTraceWin();
        public:
            /// @brief Calls DBGHELP Functions to get our Stacktrace
            ///
            /// @remarks writes everything into StackTrace.txt
            ///
            void Run();
        };
    }
}



#endif /* _STACKTRACEWIN_H_ */
#endif