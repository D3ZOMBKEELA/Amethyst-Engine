#ifndef _CPUCLASS_H_
#define _CPUCLASS_H_

#pragma comment(lib, "pdh.lib")

#include <pdh.h>

class CpuClass
{
public:
	CpuClass();
	CpuClass(const CpuClass&);
	~CpuClass();

	void Initialize();
	void Shutdown();
	void Frame();
	int GetCpuPercentage();

private:
	bool h_canReadCpu;
	HQUERY h_queryHandle;
	HCOUNTER h_counterHandle;
	unsigned long h_lastSampleTime;
	long h_cpuUsage;
};

#endif