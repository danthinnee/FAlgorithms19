#include "BankTellerService.cc"
#include "ArrayQueue.cc"
#include "PQueue.cc"
#include "Event.cc"
#include "BankCustomer.cc"

using namespace std;

int main() {
	BankTellerService myBank("input.txt", "output.txt"); // create object
	myBank.readCustomersInfo(); // read from text file
	myBank.serveCustomers(); // carry out simulation
	myBank.getStatistics(); // display statistics
	return 0;
}
