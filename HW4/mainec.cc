#include "BankTellerServiceec.cc"
#include "ArrayQueue.cc"
#include "PQueue.cc"
#include "Event.cc"
#include "BankCustomer.cc"

using namespace std;

int main() {
cout <<"1 TELLER" << endl;
	BankTellerService myBank1T("input1.txt", "output1.txt",1);
	myBank1T.readCustomersInfo();
	myBank1T.serveCustomers();
	myBank1T.getStatistics();

cout << "2 TELLER" << endl;
	BankTellerService myBank2T("input1.txt", "output1.txt",2);
	myBank2T.readCustomersInfo();
	myBank2T.serveCustomers();
	myBank2T.getStatistics();

cout << "3 TELLER" << endl;
	BankTellerService myBank3T("input1.txt", "output1.txt",3);
	myBank3T.readCustomersInfo();
	myBank3T.serveCustomers();
	myBank3T.getStatistics();

cout << "4 TELLER" << endl;
	BankTellerService myBank4T("input1.txt", "output1.txt",4);
	myBank4T.readCustomersInfo();
	myBank4T.serveCustomers();
	myBank4T.getStatistics();

	return 0;
}
