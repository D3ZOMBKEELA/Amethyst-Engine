#include "cpuclass.h"

CpuClass::CpuClass()
{
}

CpuClass::CpuClass(const CpuClass& other)
{
}

CpuClass::~CpuClass()
{
}

void CpuClass::Initialize()
{
	PDH_STATUS status;
	h_canReadCpu = true;

	status = PdhOpenQuery(NULL, 0, &h_queryHandle);
	if(status != ERROR_SUCCESS)
	{
		h_canReadCpu = false;
	}

	status = PdhAddCounter(h_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &h_counterHandle);
	if(status != ERROR_SUCCESS)
	{
		h_canReadCpu = false;
	}

	h_lastSampleTime = GetTickCount();

	h_cpuUsage = 0;

	return;
}

void CpuClass::Shutdown()
{
	if(h_canReadCpu)
	{
		PdhCloseQuery(h_queryHandle);
	}

	return;
}

void CpuClass::Frame()
{
	PDH_FMT_COUNTERVALUE value;

	if(h_canReadCpu)
	{
		if((h_lastSampleTime + 1000) < GetTickCount())
		{
			h_lastSampleTime = GetTickCount();

			PdhCollectQueryData(h_queryHandle);

			PdhGetFormattedCounterValue(h_counterHandle, PDH_FMT_LONG, NULL, &value);

			h_cpuUsage = value.longValue;
		}
	}

	return;
}

int CpuClass::GetCpuPercentage()
{
	int usage;

	if(h_canReadCpu)
	{
		usage = (int)h_cpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}