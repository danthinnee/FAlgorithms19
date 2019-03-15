#ifndef ARRAYQUEUE
#define ARRAYQUEUE

#include "string"
#include "iostream"
#include "PQueue.cc"
#include "Event.cc"
#include "BankCustomer.cc"

using namespace std;

class ArrayQueue {
	private:
		int QCapacity;
		int* IDs; // Array of queue items (the customer's IDs in this case)
		int front; // index to front of queue
		int back; // index to back of queue
		int count; // number of items current in the queue

	public:
		ArrayQueue(int c){
			QCapacity = c;
			IDs = new int [c];
			count = 0;
			front = 0;
			back = 0;
		}
		~ArrayQueue(){
			delete[] IDs;
		}
		bool isEmpty(){if(count==0) return true; else return false;}
		bool enqueue(const int newID){
			if(count < QCapacity){
				IDs[count]=newID;
				count++;
			}
		}
		bool dequeue(){
			count--;
			for(int i=0; i<count; i++){
				IDs[i] = IDs[i+1];
			}
		}
		int peekFront(){
			return IDs[0];
		}
		int queueLength(){ return count; } // returns the current number of items in teh queue

};

#endif
