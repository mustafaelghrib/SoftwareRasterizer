#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

typedef unsigned long long uint64;

class Timer
{
private:
	uint64 mStart;

public:

	uint64 QueryFrequency();

	uint64 QueryCounter();

	uint64 StartTimer();

	uint64 GetTickS(); // seconds

	uint64 GetTickMs(); // milliseconds

	uint64 GetTickUs(); // microseconds

	uint64 DeltaTimeS();

	uint64 DeltaTimeMs();

	uint64 DeltaTimeUs();
};