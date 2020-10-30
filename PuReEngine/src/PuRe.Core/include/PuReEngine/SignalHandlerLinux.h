#ifdef __linux__
#ifndef _SIGNALHANDLERLINUX_H_
#define _SIGNALHANDLERLINUX_H_

#include "StackTraceLinux.h"
#include <signal.h>

// Engine specific includes
#include "Defines.h"
#include "ISignalHandler.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Handels Signals
        ///
        class CSignalHandlerLinux  : public ISignalHandler
        {
        private:
            /// @brief Pointer to our StackTrace Object
            ///
            static CStackTraceLinux* m_pStackTrace;
        public:
            /// @brief Initializes StackTrace and signal
            ///
            CSignalHandlerLinux();
            /// @brief Destroyes StackTrace
            ///
            ~CSignalHandlerLinux();
        private:
            /// @brief Handles Signals
            ///
            /// @param Signal we got as int
            ///
            static void SignalHandle(const int a_Signal);
        };
    }
}
#endif /*_SIGNALHANDLERLINUX_H_ */
#endif