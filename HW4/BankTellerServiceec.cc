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
const int waitingQCapacity = 50;
const int eventsQCapacity = 50;

class BankTellerService{
	private:
		int BusyTeller; // indicates how many tellers are currently busy or available
		int CustomersNum; // total number of customers in the simulation
		ifstream inf; // text file with the arrival and transaction times
		ofstream otf; // text file with the trace messages adn teh final statistics
		ArrayQueue WaitingQ = ArrayQueue(waitingQCapacity); // array queue
		PQueue EventsQ = PQueue(eventsQCapacity); // priority queue
		BankCustomer* Customers; // array of the customer objects in the simulation
		int waitingQMax = 0; // the maximum length of the waiting queue

	public:
		BankTellerService(string infS, string otfS, int numT){
			inf.open(infS.c_str());
			if(inf.fail()){
				cerr << "Error: Could not open input file\n";
				exit(1);
			}
			otf.open(otfS.c_str());
			if(otf.fail()){
				cerr << "Error: Could not open output file\n";
				exit(1);
			}
			CustomersNum=0;
			Customers = new BankCustomer[eventsQCapacity];
			BusyTeller=numT;
		}
		~BankTellerService(){ inf.close(); otf.close(); }

		void readCustomersInfo(){
			// read customer arrival and transaction times from input file
			int arrtime;
			int transtime;
			int index=0;
			BankCustomer b;
			int starttime=0;
			int x,y;
			while(inf >> x && inf >> y){
				arrtime=x;
cout << arrtime << '\t';
				b.ID=index; b.ArrivalTime=arrtime;
cout << transtime << endl;		
				transtime=y;	
				b.TransactionLength = transtime;
				Customers[index] = b;
			// add one customer object in Customers array
				Event ev;
				ev.EventType='A'; ev.CustID=index; ev.ADTime=arrtime; 
				EventsQ.enqueue(ev);
			// insert arrival event in the EventsQ
			 	index++;
				CustomersNum++;
			}
		}
		void serveCustomers(){
			// loop continues as long as there are events in teh EventsQ

			while(!EventsQ.isEmpty()){
				if(EventsQ.peekFront().EventType == 'A'){
					cout << "Processing an arrival event at time <-- " << EventsQ.peekFront().ADTime << endl; 
					otf << "Processing an arrival event at time <-- " << EventsQ.peekFront().ADTime << endl;
cout << BusyTeller << endl;
					if(BusyTeller==0){ // if event is an arrival event and there are no tellers available, add person to queue
						WaitingQ.enqueue(EventsQ.peekFront().CustID);
						if(waitingQMax < WaitingQ.queueLength()){ waitingQMax = WaitingQ.queueLength(); }
					}
					else{ // if some tellers are available
						Event ev;
						Customers[EventsQ.peekFront().CustID].ServiceStartTime = Customers[EventsQ.peekFront().CustID].ArrivalTime;
						ev.EventType='D'; ev.CustID=EventsQ.peekFront().CustID; ev.ADTime=Customers[EventsQ.peekFront().CustID].ServiceStartTime + Customers[EventsQ.peekFront().CustID].TransactionLength;
						
//cout << "Enqueueing a departure event with ADTime == " << ev.ADTime << endl;
						EventsQ.enqueue(ev);
						BusyTeller--; // there is one less teller available
					}
					EventsQ.dequeue();
				}
				else{ // if event is a departure event
					cout << "Processing a departure event at time --> " << EventsQ.peekFront().ADTime << endl;
					otf << "Processing a departure event at time --> " << EventsQ.peekFront().ADTime << endl;
					if(!WaitingQ.isEmpty()){
						Event ev;
						Customers[WaitingQ.peekFront()].ServiceStartTime = EventsQ.peekFront().ADTime;
						ev.EventType='D'; ev.CustID=WaitingQ.peekFront(); ev.ADTime=EventsQ.peekFront().ADTime + Customers[WaitingQ.peekFront()].TransactionLength;
						EventsQ.enqueue(ev);
						WaitingQ.dequeue();
						// by picking up a new customer, the number of available tellers stays the same	
					}
					else { BusyTeller++; }
					EventsQ.dequeue();
			}
		}}
		void getStatistics(){
			cout << "Final Statistics:" << endl;
			otf << "Final Statistics: " << endl;
			cout << "Total number of customers processed: " << CustomersNum << endl;
			otf << "Total number of customers processed: " << CustomersNum << endl;
			float avgWaitTime = 0;
			int maxWaitTime = 0;
			for(int i=0; i<CustomersNum; i++){
				avgWaitTime = avgWaitTime + (Customers[i].ServiceStartTime - Customers[i].ArrivalTime);
				if(Customers[i].ServiceStartTime-Customers[i].ArrivalTime > maxWaitTime){
					maxWaitTime = Customers[i].ServiceStartTime - Customers[i].ArrivalTime;
				}
			}
			avgWaitTime = avgWaitTime / CustomersNum;
			cout << "Average waiting time = " << avgWaitTime << endl;
			otf << "Average waiting time = " << avgWaitTime << endl;
			cout << "Maximum waiting time = " << maxWaitTime << endl;
			otf << "Maximum waiting time = " << maxWaitTime << endl;
			cout << "Maximum waiting queue length = " << waitingQMax << endl;
			otf << "Maximum waiting queue length = " << waitingQMax << endl;
		}

};
#endif
