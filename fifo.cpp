#include "fifo.hpp"

FIFO::FIFO()
{
	currentCustomer = nullptr;
}

void FIFO::insert(float arrivalTime, float soServiceTime, float deportTime)
{
	if(currentCustomer==nullptr) // The queue is empty
	{
		currentCustomer=new Customer(arrivalTime, soServiceTime, deportTime);
	}
	else
	{	
	
		Customer* tempCustomer;
		Customer* prevCustomer;
		Customer* nextCustomer;
		tempCustomer=currentCustomer;
		prevCustomer=nullptr;
		
		while(1)
		{
			if(tempCustomer->getDeportTime() < deportTime) // checking to see where the new customer fits into the queue
			{
				prevCustomer=tempCustomer;
				tempCustomer=tempCustomer->getNext();
				if(tempCustomer==nullptr) // if tempCustomer becomes nullptr, that means it has reached the end of the list
				{
					tempCustomer=new Customer(arrivalTime, soServiceTime, deportTime);
					prevCustomer->setNext(tempCustomer);
					break;
				}
			}
			else
			{
				if(prevCustomer==nullptr) // if the new customer departure time is smaller than any other departure
				{
					currentCustomer=new Customer(arrivalTime, soServiceTime, deportTime);
					currentCustomer->setNext(tempCustomer);
					break;
				}
				else // if the prevCustomer is not nullptr, then its at least not the first position
				{
					nextCustomer=tempCustomer;
					tempCustomer=new Customer(arrivalTime, soServiceTime, deportTime);
					prevCustomer->setNext(tempCustomer);
					tempCustomer->setNext(nextCustomer);
					break;
				}
			}
		}
	}

}

void FIFO::remove()
{
	Customer* tempCustomer = currentCustomer->getNext();
	delete currentCustomer;
	currentCustomer=tempCustomer;
}

Customer* FIFO::getCurrentCustomer()
{
	return currentCustomer;
}

float FIFO::getDepartTime()
{
	return currentCustomer->getDeportTime();
}

float FIFO::special(float arrivalTime, int ServiceChannels)
{
	Customer* tempCustomer;
	tempCustomer=currentCustomer;
	for(int i =0; i<-ServiceChannels; i++)
	{
		tempCustomer=tempCustomer->getNext(); // this is to go through the FIFO queue to determine what the soServiceTime should be for the new entry
	}
	return tempCustomer->getDeportTime();













}
