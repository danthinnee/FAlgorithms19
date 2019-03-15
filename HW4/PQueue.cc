#ifndef PQUEUE
#define PQUEUE

#include "iostream"
#include "string"
#include "BankCustomer.cc"
#include "Event.cc"

using namespace std;

class PQueue {
	private:
		int QCapacity; // Max size of the queue
		Event* events; // Pointer to the array that holds arrival and departure events
		int count; // Number of events currently in the queue
		bool listInsert(Event ev){ // insert a new event to a sorted list
			int index=0;
			if(count>0){
				while(index < count && ev.ADTime < events[index].ADTime){
					index++;
				}
				for(int i=count; i>index; i--){
					events[i] = events[i-1];
				}
			}
			events[index] = ev;
			count++;
		}
		bool listDelete(){ // Delete the event at the end of the list
			count--;
		}
		Event listPeek(){ // Get the event at the end of the list
			return events[count-1];
		}

	public:
		PQueue(int c){ // c for the Qcapacity
			QCapacity = c; // initialize variables
			events = new Event [c];
			count = 0;
		}
		~PQueue(){
			delete[] events;
		}
		bool isEmpty(){
			if(count==0) return true;
			else return false;
		}
		bool enqueue(Event ev){ // calls listInsert to insert a new event
			listInsert(ev);
		}
		bool dequeue(){ // calls  listDelete to remove the queue's front event
			listDelete();
		}
		Event peekFront(){ // calls listPeek to return the queue's front event
			return listPeek();
		}

};

#endif
