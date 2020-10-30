#include "include/PuReEngine/Timer.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************
        CTimer::CTimer()
        {
            this->m_StartTime = Time_Now;
            this->m_LastUpdateTime = Time_Now;
            this->m_FPS = 0;
            this->m_FPSCounter = 0;
            this->m_FPSIntervall = 0;
        }

        // **************************************************************************
        // **************************************************************************
        CTimer::~CTimer()
        {
        }

        // **************************************************************************
        // **************************************************************************
        int64 CTimer::GetTotalElapsedMilliseconds()
        {
            auto now = Time_Now;
            auto dif = now - this->m_StartTime;
            int64 ms = Convert_Time(dif);
            return ms;
        }

        // **************************************************************************
        // **************************************************************************
        int64 CTimer::GetElapsedMilliseconds()
        {
            return this->m_LastUpdateDifference;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CTimer::GetTotalElapsedSeconds()
        {
            return this->GetTotalElapsedMilliseconds() / 1000.0f;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CTimer::GetElapsedSeconds()
        {
            return this->GetElapsedMilliseconds() / 1000.0f;
        }

        uint32 CTimer::GetFPS()
        {
            return this->m_FPS;
        }

        // **************************************************************************
        // **************************************************************************
        void CTimer::CalculateFPS()
        {

            //Calculate FPS
            this->m_FPSCounter++;
            //If 1000 milliseconds (one second) passed
            if (GetTotalElapsedMilliseconds() - this->m_FPSIntervall > 1000)
            {
                this->m_FPS = this->m_FPSCounter;
                this->m_FPSCounter = 0;
                //Set our Intervall to actuall time
                this->m_FPSIntervall = GetTotalElapsedMilliseconds();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CTimer::Update()
        {
            this->m_LastUpdateDifference = (int32)Convert_Time(Time_Now - this->m_LastUpdateTime);
            this->m_LastUpdateTime = Time_Now;
        }

    }
}