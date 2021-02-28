#ifndef FIFO_HPP
#define FIFO_HPP
#include "customer.hpp"
class FIFO
{
	public:
		FIFO();
		void insert(float arrivalTime, float soServiceTime, float deportTime); // this is a custom insert to place the departure in the proper place
		Customer* getCurrentCustomer();
		void remove();
		float getDepartTime();
		float special(float arrivalTime, int serviceChannels);
	private:
		Customer * currentCustomer;
};
#endif
