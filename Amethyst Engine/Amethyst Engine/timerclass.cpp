#include "timerclass.h"

TimerClass::TimerClass()
{
}

TimerClass::TimerClass(const TimerClass& other)
{
}

TimerClass::~TimerClass()
{
}

bool TimerClass::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&h_frequency);
	if(h_frequency == 0)
	{
		return false;
	}

	h_ticksPerMs = (float)(h_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&h_startTime);

	return true;
}

void TimerClass::Frame()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - h_startTime);

	h_frameTime = timeDifference / h_ticksPerMs;

	h_startTime = currentTime;

	return;
}

float TimerClass::GetTime()
{
	return h_frameTime;
}