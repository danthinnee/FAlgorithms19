#ifndef BANKTELLER
#define BANKTELLER

#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include "iostream"
#include "string"
#include "ArrayQueue.cc"
#include "PQueue.cc"
#include "Event.cc"
#include "BankCustomer.cc"
using namespace std;

// constants defined in the program
const int waitingQCapacity = 20;
const int eventsQCapacity = 20;

class BankTellerService{
	private:
		bool BusyTeller; // indicates if the teller is currently busy or available
		int CustomersNum; // total number of customers in the simulation
		ifstream inf; // text file with the arrival and transaction times
		ofstream otf; // text file with the trace messages adn teh final statistics
		ArrayQueue WaitingQ = ArrayQueue(waitingQCapacity); // array queue
		PQueue EventsQ = PQueue(eventsQCapacity); // priority queue
		BankCustomer* Customers; // array of the customer objects in the simulation
		int waitingQMax = 0; // the maximum length of the waiting queue

	public:
		BankTellerService(string infS, string otfS){ // bank teller service constructor
			inf.open(infS.c_str()); // open input file
			if(inf.fail()){
				cerr << "Error: Could not open input file\n";
				exit(1);
			}
			otf.open(otfS.c_str()); // open output file
			if(otf.fail()){
				cerr << "Error: Could not open output file\n";
				exit(1);
			}
			CustomersNum=0; // initialize Customers to eventsQCapacity, contains 0 elements
			Customers = new BankCustomer[eventsQCapacity];
		}
		~BankTellerService(){ inf.close(); otf.close(); } // destructor

		void readCustomersInfo(){
			// read customer arrival and transaction times from input file
			int arrtime;
			int transtime;
			int index=0;
			BankCustomer b;
			int starttime=0;
			int x,y;
			while(inf >> x && inf >> y){ // while there are still elements in the input stream
				arrtime=x;
cout << arrtime << '\t';
				b.ID=index; b.ArrivalTime=arrtime; // add attributes to bank customer
cout << transtime << endl;		
				transtime=y;	
				b.TransactionLength = transtime;
				Customers[index] = b; // add BankCustomer to Customers
			// add one customer object in Customers array
				Event ev;
				ev.EventType='A'; ev.CustID=index; ev.ADTime=arrtime; // create arrival event for BankCustomer
				EventsQ.enqueue(ev);
			// insert arrival event in the EventsQ
			 	index++;
				CustomersNum++; // increase number of customers
			}
		}
		void serveCustomers(){
			// loop continues as long as there are events in the EventsQ
			BusyTeller=false; // teller is available in beginning
			while(!EventsQ.isEmpty()){
				if(EventsQ.peekFront().EventType == 'A'){ // if the event type is an arrival
					cout << "Processing an arrival event at time <-- " << EventsQ.peekFront().ADTime << endl; 
					otf << "Processing an arrival event at time <-- " << EventsQ.peekFront().ADTime << endl;

					if(BusyTeller){ // and if the teller is busy, add event to queue and update waitingQMax
						WaitingQ.enqueue(EventsQ.peekFront().CustID);
						if(waitingQMax < WaitingQ.queueLength()){ waitingQMax = WaitingQ.queueLength(); }
					}
					else{ // if teller is not busy, make event departure
						Event ev;
						Customers[EventsQ.peekFront().CustID].ServiceStartTime = Customers[EventsQ.peekFront().CustID].ArrivalTime;
						ev.EventType='D'; ev.CustID=EventsQ.peekFront().CustID; ev.ADTime=Customers[EventsQ.peekFront().CustID].ServiceStartTime + Customers[EventsQ.peekFront().CustID].TransactionLength;
						
//cout << "Enqueueing a departure event with ADTime == " << ev.ADTime << endl;
						EventsQ.enqueue(ev);
						BusyTeller=true; // make teller busy with current event
					}
					EventsQ.dequeue(); // dequeue arrival
				}
				else{ // if event is a departure event
					cout << "Processing a departure event at time --> " << EventsQ.peekFront().ADTime << endl;
					otf << "Processing a departure event at time --> " << EventsQ.peekFront().ADTime << endl;
					if(!WaitingQ.isEmpty()){ // if there are still customers in the queue, bring next customer to teller
						Event ev;
						Customers[WaitingQ.peekFront()].ServiceStartTime = EventsQ.peekFront().ADTime;
						ev.EventType='D'; ev.CustID=WaitingQ.peekFront(); ev.ADTime=EventsQ.peekFront().ADTime + Customers[WaitingQ.peekFront()].TransactionLength;
						EventsQ.enqueue(ev);
						WaitingQ.dequeue();
						BusyTeller=true;	
					}
					else { BusyTeller=false; } // if there are no customers in the queue make the teller available
					EventsQ.dequeue(); // dequeue departure event
			}
		}}
		void getStatistics(){ // print statistics to output file and console
			cout << "Final Statistics:" << endl;
			otf << "Final Statistics: " << endl;
			cout << "Total number of customers processed: " << CustomersNum << endl; // print final count
			otf << "Total number of customers processed: " << CustomersNum << endl;
			float avgWaitTime = 0;
			int maxWaitTime = 0;
			for(int i=0; i<CustomersNum; i++){ // determine average wait time by calculating
				avgWaitTime = avgWaitTime + (Customers[i].ServiceStartTime - Customers[i].ArrivalTime);
				if(Customers[i].ServiceStartTime-Customers[i].ArrivalTime > maxWaitTime){
					maxWaitTime = Customers[i].ServiceStartTime - Customers[i].ArrivalTime;
				}
			}
			avgWaitTime = avgWaitTime / CustomersNum; // and then dividing
			cout << "Average waiting time = " << avgWaitTime << endl;
			otf << "Average waiting time = " << avgWaitTime << endl;
			cout << "Maximum waiting time = " << maxWaitTime << endl;
			otf << "Maximum waiting time = " << maxWaitTime << endl;
			cout << "Maximum waiting queue length = " << waitingQMax << endl;
			otf << "Maximum waiting queue length = " << waitingQMax << endl;
		}

};
#endif
