#ifndef EVENT
#define EVENT

#include "iostream"
#include "string"

using namespace std;

class Event{
	public:
		char EventType; // 'A' for arrival and 'D' for departure
		int CustID; // ID of the customer who created the event
		int ADTime; // Arrival or departure time
};

#endif
