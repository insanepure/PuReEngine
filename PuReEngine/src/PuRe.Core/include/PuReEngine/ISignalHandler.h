#ifndef _ISIGNALHANDLER_H_
#define _ISIGNALHANDLER_H_


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base Interface for a Signal Handler
        ///
        struct ISignalHandler
        {
            /// @brief Destructor
            ///
            virtual ~ISignalHandler() {};
        };
    }
}
#endif /* _ISIGNALHANDLER_H_*/
