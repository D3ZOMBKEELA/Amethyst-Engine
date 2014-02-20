#include "fpsclass.h"

FpsClass::FpsClass()
{
}

FpsClass::FpsClass(const FpsClass& other)
{
}

FpsClass::~FpsClass()
{
}

void FpsClass::Initialize()
{
	h_fps = 0;
	h_count = 0;
	h_startTime = timeGetTime();
	return;
}

void FpsClass::Frame()
{
	h_count++;
	if(timeGetTime() >= (h_startTime + 1000))
	{
		h_fps = h_count;
		h_count = 0;

		h_startTime = timeGetTime();
	}
}

int FpsClass::GetFps()
{
	return h_fps;
}