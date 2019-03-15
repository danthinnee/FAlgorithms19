#ifndef BANKCUSTOMER
#define BANKCUSTOMER

#include "iostream"
#include "string"

using namespace std; 

class BankCustomer{ // representing each customer who arrives to the bank
	public:
		int ID; 
		int ArrivalTime;
		int ServiceStartTime;
		int TransactionLength;
};

#endif
