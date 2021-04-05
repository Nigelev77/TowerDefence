#pragma once
#include <chrono>

/*
Basic Time Keeper for getting delta times.

*/


class TimeKeeper
{
public:
	//Returns miliseconds
	float GetDeltaTime(); //Returns the dt from last delta time call.
	float EndTimer();
	void StartTimer();
	void DeltaTimeBase(); //Set the start to delta time as this will be called regularly
	TimeKeeper();


private:
	std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
	std::chrono::time_point<std::chrono::steady_clock> m_TimerTime;
};