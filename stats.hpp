#ifndef STATS_HPP
#define STATS_HPP
#include <cmath>
#include <stdlib.h>
#include <iostream> // temporary, for testign
class Stats
{
	public:
		static float GetRandomInterval(float average);
		static int Fact(int num);
		static float percentIdleTime(int serviceChannels, float lambda, float mu);
		static float averagePeople(int serviceChannels, float lambda, float mu);
		static float averageWaitTime(int M, float L, float mu);
		static float averageQueue(int M, float L, float mu);
		static float averageQueueWait(int M, float L, float mu);
		static float Rho(int M, float L, float mu);
	private:
};
#endif
