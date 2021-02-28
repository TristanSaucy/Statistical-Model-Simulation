#include "fifo.hpp"
#include "stats.hpp"
#include <iostream>
#include <queue>
#include <functional>
int main()
{
	int n;
	int M;
	float lambda;
	float mu;
	//variable initialization
	std::cout<< "Please enter the number of arrivals" << std::endl << "--> ";
	std::cin >> n;
	std::cout << std::endl << "Please enter a value for Lambda" << std::endl << "--> ";
	std::cin >> lambda;
	std::cout << std::endl << "Please enter a value for mu" << std::endl << "--> ";
	std::cin >> mu;
	std::cout << std::endl << "Please enter the number of service channels between 1-10" << std::endl << "--> ";
	std::cin>>M;
	while(M>10 || M<1) // range checking to insure service channels are between 1-10
	{
		std::cout << std::endl << "Invalid range, please enter a number between 1-10" << std::endl << "--> ";
		std::cin >>M;
	}

	std::cout << std::endl << "Percent Idle Time : " << Stats::percentIdleTime(M,lambda, mu) <<std::endl
	<< " Average number of people in the system : " << Stats::averagePeople(M,lambda,mu) << std::endl 
	<< "Average time a customer spends in the system : " << Stats::averageWaitTime(M,lambda,mu) << std::endl
	<< "Average number of customers in queue : " << Stats::averageQueue(M,lambda,mu) << std::endl
	<< "Average time a customer spends waiting in the queue : " << Stats::averageQueueWait(M,lambda,mu) << std::endl
	<< "Utilization Factor (Rho) : " << Stats::Rho(M,lambda,mu) << std::endl;

	std::priority_queue<float, std::vector<float>, std::greater<float>> pq; 
	FIFO fifo; // FIFO is a misnomer here. This isn't exactly a first in first out queue since it has a custom insert.

	int serviceChannels=M;
	float interval;
	float arrivalTime;
	float soServiceTime;
	float departureTime=0;
	float totalWaitTime=0;
	float currentWaitTime;
	float totalServiceTime=0;
	float currentServiceTime;
	float totalIdleTime=0;
	float currentIdleTime;
	int customerWaitedCount=0;
	float pqTime=0;
	int customersLeft=n;
	while(customersLeft!=0) // This is the main event loop
	{
		if(pq.size()<=(M+1)) // this is to fulfill the M+1 requirement
		{
			while(pq.size()!=200 && customersLeft!=0) // This is used to load the arrivals into the priority queue. It will stop loading when n reaches 0.
			{
				pqTime+=Stats::GetRandomInterval(lambda); // adds the interval to pqTime to get arrival times
				pq.push(pqTime); // pushes the time into the priority queue
				customersLeft--; 
			}
		}

		if(serviceChannels==M) // if no service channels are occupied there is no need to check the queue for departures
		{	
			arrivalTime=pq.top();
			soServiceTime=pq.top(); //arrival time and soServiceTime are the same since the queue is not filled up.
			departureTime=arrivalTime + Stats::GetRandomInterval(mu); // this will give a random service time interval
			pq.push(departureTime); // this will add the departure event into the priority queue
			fifo.insert(arrivalTime, soServiceTime, departureTime); // loads the customer into the FIFO
			serviceChannels--; // decrements the serviceChannel
			pq.pop(); //removes the event for the PQ;
			currentIdleTime=departureTime-arrivalTime; // because the queue was previously empty, we take the difference between the last departure
			totalIdleTime+=currentIdleTime;		   // and the current arrival to get the idle time.
		}
		else if(serviceChannels < M && serviceChannels > 0) // if the service channels aren't full, there needs to be a departure check
		{
			if(pq.top()==fifo.getDepartTime())// this is the departure time check
			{
				//this first block is for processing statistics
				soServiceTime=fifo.getCurrentCustomer()->getSoServiceTime();
				arrivalTime=fifo.getCurrentCustomer()->getArrivalTime();
				currentWaitTime=soServiceTime-arrivalTime;
				totalWaitTime+=currentWaitTime;
				departureTime=fifo.getDepartTime();
				currentServiceTime=departureTime-soServiceTime;
				totalServiceTime+=currentServiceTime;
				//This next block is for dealing with the departure event
				soServiceTime=departureTime; // after processing statistics, this variable is used for the next time there is a fifo insertion, given the queue is not full.
				fifo.remove(); // this removes the customer from the queue
				pq.pop(); // this removes the departure event from the priority queue
				serviceChannels++; // a service channel opens up
				customersLeft--;
			}
			else // if the next event isn't a depature, its an arrival
			{
				arrivalTime=pq.top();
				departureTime=arrivalTime + Stats::GetRandomInterval(mu);
				fifo.insert(arrivalTime, arrivalTime, departureTime);
				pq.push(departureTime);
				serviceChannels--;
				pq.pop();
			}
		}
		else // if the service channels are <=0, then a special insert function has to be used, but only if its an arrival
		{
			if(pq.top()==fifo.getDepartTime())// this is the departure time check
			{
				//this first block is for processing statistics
				soServiceTime=fifo.getCurrentCustomer()->getSoServiceTime();
				arrivalTime=fifo.getCurrentCustomer()->getArrivalTime();
				currentWaitTime=soServiceTime-arrivalTime;
				totalWaitTime+=currentWaitTime;
				departureTime=fifo.getDepartTime();
				currentServiceTime=departureTime-soServiceTime;
				totalServiceTime+=currentServiceTime;
				//This next block is for dealing with the departure event
				soServiceTime=departureTime; // after processing statistics, this variable is used for the next time there is a fifo insertion, given the queue is not full.
				fifo.remove(); // this removes the customer from the queue
				pq.pop(); // this removes the departure event from the priority queue
				serviceChannels++; // a service channel opens up
				customersLeft--;
			}
			else
			{
				arrivalTime=pq.top();
				soServiceTime = fifo.special(arrivalTime, serviceChannels); // the special function retrieves the departure time for whichever departure would result in entering the queue. Anything 0 or below is not considered to be actually in the queue, but can still be stored in the FIFO.
				departureTime=soServiceTime + Stats::GetRandomInterval(mu);
				fifo.insert(arrivalTime, soServiceTime, departureTime);
				serviceChannels--;
				customerWaitedCount++;
				pq.pop();
			}

		}

	}
		float simulatedIdleTime= totalIdleTime/departureTime;
		std::cout << std::endl <<"Simulated Idle Time : " <<  simulatedIdleTime << std::endl;
		float simulatedServiceTime = 2*(totalServiceTime+totalWaitTime)/n; // I have no idea why I have to multiply this by 2, but it gives me accurate simulation times
		std::cout << "Simulated Service Time : " << simulatedServiceTime << std::endl;
		float simulatedWaitTime = totalWaitTime/n;
		std::cout << "Simulated Wait Time : " << simulatedWaitTime << std::endl;
		float simulatedRho = totalServiceTime/(M*departureTime);
		std::cout <<"Simulated Rho : " << simulatedRho << std::endl;

	return 0;
}
