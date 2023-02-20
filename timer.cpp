#include "timer.h"

typedef unsigned long long uint64;

uint64 Timer::QueryFrequency() {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return freq.QuadPart;
}

uint64 Timer::QueryCounter() {
	LARGE_INTEGER time;
	::QueryPerformanceCounter(&time);
	return time.QuadPart;
}

uint64 Timer::StartTimer() {
	mStart = QueryCounter();
	return mStart;
}

uint64 Timer::GetTickS() {
	return QueryCounter() / QueryFrequency();
}

uint64 Timer::GetTickMs() {
	return (QueryCounter() / QueryFrequency()) * 1000;
}

uint64 Timer::GetTickUs() {
	return (QueryCounter() / QueryFrequency()) * 1000000;
}

uint64 Timer::DeltaTimeS() {
	return (QueryCounter() - mStart) / QueryFrequency();
}

uint64 Timer::DeltaTimeMs() {
	return DeltaTimeS() * 1000;
}

uint64 Timer::DeltaTimeUs() {
	return DeltaTimeS() * 1000000;
}