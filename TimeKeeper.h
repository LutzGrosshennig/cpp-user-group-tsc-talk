#pragma once

#include <intrin.h>

/*
This is the simple class to demonstrate the usage of the timestampcounter. It was part of my talk at the CPP user group talk about
the "Joy and perils of the Intel timestamp counters. Where I explained all the twists and changes in technology that had an big impact
on the reliabilty of the TSC and gave them a very bad repuation (and rightfully so).

So this code assumes you are using a decent PC (at least a first gen Core i3/i5/i7). The code uses the newer rdtscp instruction which
does all the serialization and also reports the core the reading comes from (at least if the OS supports this). The code also assumes that 
that your CPU features an "invariant TSC" which means that the TSC is not affected by either SpeedStep, Turboboost or C/P states.
*/
class TimeKeeper final
{
public:

	TimeKeeper();
	~TimeKeeper();

private:

	void LogDuration(unsigned __int64 duration);
	void LogCoreMismatch(unsigned int startAuxTSC, unsigned int stopAuxTSC);

	unsigned __int64 startTSC;
	unsigned int startAuxTSC;

};

inline TimeKeeper::TimeKeeper()
{
	startTSC = __rdtscp(&startAuxTSC);
}

inline TimeKeeper::~TimeKeeper()
{
	unsigned int stopAuxTSC;
	unsigned __int64 stopTSC = __rdtscp(&stopAuxTSC);

	if (stopAuxTSC == startAuxTSC)
	{
		LogDuration(stopTSC - startTSC);
	}
	else
	{
		LogCoreMismatch(startAuxTSC, stopAuxTSC);
	}
}

inline void TimeKeeper::LogDuration(unsigned __int64 duration)
{
	std::cout << "Code took " << duration << " ticks to complete on core " << startAuxTSC << std::endl;
}

inline void TimeKeeper::LogCoreMismatch(unsigned int startAuxTSC, unsigned int stopAuxTSC)
{
	std::cout << "Measurement startet on core " << startAuxTSC << " and stopped on core " << stopAuxTSC << std::endl;
}
