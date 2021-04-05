#include "TimeKeeper.h"


void TimeKeeper::StartTimer()
{
	m_TimerTime = std::chrono::steady_clock::now();
}


//Returns milliseconds
float TimeKeeper::EndTimer()
{
	auto dt = std::chrono::steady_clock::now() - m_TimerTime;
	auto dtmSecs = std::chrono::duration_cast<std::chrono::milliseconds>(dt);
	return (float)dtmSecs.count();
}


TimeKeeper::TimeKeeper()
	: m_TimerTime{std::chrono::steady_clock::now()}, m_LastTime{std::chrono::steady_clock::now()}
{}

void TimeKeeper::DeltaTimeBase()
{
	m_LastTime = std::chrono::steady_clock::now();
}

//Returns milliseconds
float TimeKeeper::GetDeltaTime()
{
	auto dt = std::chrono::steady_clock::now() - m_LastTime;
	auto dtmSecs = std::chrono::duration_cast<std::chrono::milliseconds>(dt);
	m_LastTime = std::chrono::steady_clock::now();
	return (float)dtmSecs.count();
}