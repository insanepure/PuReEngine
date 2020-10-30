#ifndef _TIMER_H_
#define _TIMER_H_
// Engine specific includes
#include "Defines.h"
#include <chrono>

#define Time std::chrono::high_resolution_clock::time_point
#define Time_Now std::chrono::high_resolution_clock::now()
#define Convert_Time(x) std::chrono::duration_cast<std::chrono::milliseconds>(x).count()

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Timer for handling Time calculations.
        ///
        class CTimer
        {

        private:
            /// @brief Intervall for our FPS
            ///
            int64 m_FPSIntervall;
            /// @brief Frames Per Second Counter
            ///
            uint32 m_FPSCounter;
            /// @brief Frames Per Second
            ///
            uint32 m_FPS;
            /// @brief Difference between last Updates
            ///
            int32 m_LastUpdateDifference;
        protected:
            /// @brief Time since Start
            ///
            Time m_StartTime;
            /// @brief Time since last Update
            ///
            Time m_LastUpdateTime;

        public:

            /// @brief Creates an instance of Timer.
            ///
            CTimer();

            /// @brief Destroyes an instance of Timer.
            ///
            ~CTimer();

        public:
            /// @brief returns the frames drawn each second
            ///
            /// @return frames drawn each second
            ///
            uint32 GetFPS();
            /// @brief returns the total elapsed Time in milliseconds
            ///
            /// @return total elapsed time as int64 in milliseconds
            ///
            int64 GetTotalElapsedMilliseconds();

            /// @brief returns the total elapsed Time in seconds
            ///
            /// @return total elapsed time as int64 in seconds
            ///
            float32 GetTotalElapsedSeconds();

            /// @brief returns the elapsed Time in milliseconds since the last Update
            ///
            /// @return elapsed time as int64 in milliseconds
            ///
            int64 GetElapsedMilliseconds();

            /// @brief returns the elapsed Time in seconds since the last Update
            ///
            /// @return elapsed time as int64 in seconds
            ///
            float32 GetElapsedSeconds();

            /// @brief Updates last Time, called after Rendering is done
            ///
            void Update();

            /// @brief Calculate the Frames Per Second
            ///
            void CalculateFPS();
        };
    }
}

#endif _TIMER_H_