#include "customer.hpp"


Customer::Customer(float arrivalTime, float soServiceTime, float deportTime)
{
	this->arrivalTime=arrivalTime;
	this->soServiceTime=soServiceTime;
	this->deportTime=deportTime;
	nextCust=nullptr;
}
float Customer::getDeportTime()
{
	return deportTime;
}

float Customer::getSoServiceTime()
{
	return soServiceTime;
}

float Customer::getArrivalTime()
{
	return arrivalTime;
}

Customer* Customer::getNext()
{
	return nextCust;
}

void Customer::setDeportTime( float deportTime)
{
this->deportTime=deportTime;
}

void Customer::setSoServiceTime(float soServiceTime)
{
this->soServiceTime=soServiceTime;
}

void Customer::setArrivalTime(float arrivalTime)
{
	this->arrivalTime=arrivalTime;
}

void Customer::setNext(Customer* nextCustomer)
{
	this->nextCust=nextCustomer;
}
