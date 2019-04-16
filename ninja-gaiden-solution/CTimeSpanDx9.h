#ifndef CTIMESPANDX9_H
#define CTIMESPANDX9_H

#include <Windows.h>

class CTimeSpanDx9
{
private:
	UINT64	m_Ticks;
public:

	static const UINT64 TicksPerSecond = 10000000;

	static const UINT64 TicksPerMillisecond = 10000;


	CTimeSpanDx9();

	CTimeSpanDx9(UINT64 Ticks);

	int	getMilliseconds();

	UINT64	getTicks();

	CTimeSpanDx9& operator=(const CTimeSpanDx9& Timesp);

	~CTimeSpanDx9();
};
#endif