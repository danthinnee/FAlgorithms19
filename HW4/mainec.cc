#include "BankTellerServiceec.cc"
#include "ArrayQueue.cc"
#include "PQueue.cc"
#include "Event.cc"
#include "BankCustomer.cc"

using namespace std;

int main() {
cout <<"1 TELLER" << endl; // test dataset with  1 teller 
	BankTellerService myBank1T("input1.txt", "output1.txt",1);
	myBank1T.readCustomersInfo();
	myBank1T.serveCustomers(); // run simulation
	myBank1T.getStatistics(); // display restuls

cout << "2 TELLER" << endl; // test dataset with 2 tellers
	BankTellerService myBank2T("input1.txt", "output1.txt",2);
	myBank2T.readCustomersInfo();
	myBank2T.serveCustomers(); // run simulation
	myBank2T.getStatistics(); // display results

cout << "3 TELLER" << endl; // test dataset with 3 tellers
	BankTellerService myBank3T("input1.txt", "output1.txt",3);
	myBank3T.readCustomersInfo();
	myBank3T.serveCustomers(); // run simulation
	myBank3T.getStatistics(); // display rseults

cout << "4 TELLER" << endl; // test dataset with 4 tellers
	BankTellerService myBank4T("input1.txt", "output1.txt",4);
	myBank4T.readCustomersInfo();
	myBank4T.serveCustomers(); // run simulation
	myBank4T.getStatistics(); // displayresults

	return 0;
}
