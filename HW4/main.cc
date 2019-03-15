#include "BankTellerService.cc"
#include "ArrayQueue.cc"
#include "PQueue.cc"
#include "Event.cc"
#include "BankCustomer.cc"

using namespace std;

int main() {
	BankTellerService myBank("input.txt", "output.txt");
	myBank.readCustomersInfo();
	myBank.serveCustomers();
	myBank.getStatistics();
	return 0;
}
