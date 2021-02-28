#include "stats.hpp"

float Stats::GetRandomInterval(float average)
{
	float randomNumber = (rand()%1000000)/1000000.0;
	return -1*(1.0/average) * log(randomNumber);
}

float Stats::percentIdleTime(int serviceChannels, float lambda, float mu) // This function will calculate the percentage of time that no one is in the system.
{
	float sum = 0;
	for(int i = 0; i<serviceChannels; ++i)
	{
		sum+=(1.0/Fact(i))*(pow(lambda/mu, i));
	}
	return (1.0/(sum+(1.0/Fact(serviceChannels)) * pow((lambda/mu),serviceChannels) * ((serviceChannels*mu)/((serviceChannels*mu)-lambda))));
}

float Stats::averagePeople(int serviceChannels, float lambda, float mu) // This will give you the average amount of people in the system (which includes both the priority queue and the FIFO queue
{
	return (((lambda*mu*pow(lambda/mu, serviceChannels))/(Fact(serviceChannels-1)*pow(serviceChannels*mu-lambda, 2)))*percentIdleTime(serviceChannels, lambda, mu) + (lambda/mu));
}

float Stats::averageWaitTime(int M, float L, float mu) // I realized my mistake in how I named the previous functions but its too late to go back now
{
	return averagePeople(M, L, mu)/L;
}

float Stats::averageQueue(int M, float L, float mu)
{
	return (averagePeople(M, L, mu)-L/mu);
}

float Stats::averageQueueWait(int M, float L, float mu)
{
	return averageQueue(M, L, mu)/L;
}

float Stats::Rho(int M, float L, float mu)
{
	return L/(M*mu);
}
int Stats::Fact(int num)
{
	if(num == 0)
		return 1;
	else
	return num*Fact(num-1);
}
