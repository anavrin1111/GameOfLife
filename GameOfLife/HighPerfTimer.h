#pragma once

#include <stdint.h>

constexpr auto FRAMES = 15.0f;

class HighPerfTimer
{
private:
	int64_t previousTime;
	int64_t currentTime;
	int64_t delta;
	int64_t frequency;

	int64_t GetTicks();
	int64_t GetFreq();

public:
	HighPerfTimer();
	bool timeElapsed();
	void resetTimer();
};