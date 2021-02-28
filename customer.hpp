#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
class Customer
{
	public:
		Customer(float arrivalTime, float soServiceTime, float deportTime);
		float getDeportTime();
		float getSoServiceTime();
		float getArrivalTime();
		void setDeportTime(float deport);
		void setSoServiceTime(float service);
		void setArrivalTime(float arrival);
		Customer* getNext();
		void setNext(Customer* nextCustomer);
	private:
		float arrivalTime;
		float soServiceTime;
		float deportTime;
		Customer * nextCust;
};
#endif
