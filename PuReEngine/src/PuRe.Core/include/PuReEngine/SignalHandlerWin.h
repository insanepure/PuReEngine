#ifdef _WIN32
#ifndef _SIGNALHANDLERWIN_H_
#define _SIGNALHANDLERWIN_H_

#include "StackTraceWin.h"
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
        class CSignalHandlerWin : public ISignalHandler
        {
        private:
            /// @brief Pointer to our StackTrace Object
            ///
            static CStackTraceWin* m_pStackTrace;
        public:
            /// @brief Initializes StackTrace and signal
            ///
            CSignalHandlerWin();
            /// @brief Destroyes StackTrace
            ///
            ~CSignalHandlerWin();
        private:
            /// @brief Handles Signals
            ///
            /// @param Signal we got as int
            ///
            static void SignalHandle(const int a_Signal);
        };
    }
}

#endif /*_SIGNALHANDLERWIN_H_ */
#endif