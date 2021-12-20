#include "pch.h"


TimeController::TimeController()
:m_ElaspedTime(0), m_FPS(60), m_Frequency(0), m_TargetElaspedTime(0)
{

}

TimeController::~TimeController()
{

}

void TimeController::Initialize()
{
	//빈도를 얻어온다.
	LARGE_INTEGER _Frequency;
	QueryPerformanceFrequency(&_Frequency);

	m_Frequency = _Frequency.QuadPart;

	//FPS와 1프레임에 해당하는 시간
	m_TargetElaspedTime = 1.0f / m_FPS;
}

void TimeController::SetFPS(float fps)
{
	m_FPS = fps;
	m_TargetElaspedTime = 1.0f / m_FPS;
}

void TimeController::CheckTime()
{
	m_ElaspedTime = m_EndTimeStamp.QuadPart - m_StartTimeStamp.QuadPart;

}

void TimeController::StartTimeStamp()
{
	QueryPerformanceCounter(&m_StartTimeStamp);
}

void TimeController::EndTimeStamp()
{
	QueryPerformanceCounter(&m_EndTimeStamp);
}

float TimeController::GetElaspedTimeSec() const
{
	return (float)((float)m_ElaspedTime / (float)m_Frequency) * 1000.f;
}

bool TimeController::FPSCheck()
{
	//시간 기록을 끝낸다.
	EndTimeStamp();

	//지금까지 걸린 시간을 잰다.
	CheckTime();

	if ((m_TargetElaspedTime * 1000.0f) < GetElaspedTimeSec())
	{
		//다음 프레임으로 갈 수 있다.
		StartTimeStamp();
		return true;
	}

	return false;
}


