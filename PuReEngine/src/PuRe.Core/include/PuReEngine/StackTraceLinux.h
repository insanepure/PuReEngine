#ifdef __linux__
#ifndef _STACKTRACELINUX_H_
#define _STACKTRACELINUX_H_


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
        class CStackTraceLinux
        {
        public:
            /// @brief Initializes StackTrace
            ///
            CStackTraceLinux();
            /// @brief Destroyes StackTrace
            ///
            ~CStackTraceLinux();
        public:
            /// @brief Calls DBGHELP Functions to get our Stacktrace
            ///
            /// @remarks writes everything into StackTrace.txt
            ///
            void Run();
        };
    }
}



#endif /* _STACKTRACELINUX_H_ */
#endif