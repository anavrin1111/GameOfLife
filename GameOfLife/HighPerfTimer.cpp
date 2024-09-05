#include "HighPerfTimer.h"
#include "Windows.h"

HighPerfTimer::HighPerfTimer()
{
	previousTime = GetTicks();
	frequency = GetFreq();
}

int64_t HighPerfTimer::GetTicks()
{
	LARGE_INTEGER ticks;

	QueryPerformanceCounter(&ticks);

	return ticks.QuadPart;
}

int64_t HighPerfTimer::GetFreq()
{
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);

	return freq.QuadPart;
}

void HighPerfTimer::resetTimer()
{
	previousTime = currentTime;
}

bool HighPerfTimer::timeElapsed()
{
	currentTime = GetTicks();

	delta = currentTime - previousTime;

	float fps = static_cast<float>(frequency) / FRAMES;

	bool timeHasElapsed = false;

	if (delta >= fps)
	{
		timeHasElapsed = true;
		resetTimer();
	}

	return timeHasElapsed;
}