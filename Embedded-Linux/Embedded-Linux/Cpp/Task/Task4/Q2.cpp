#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifndef _ACCOUNT_H_ 
#define _ACCOUNT_H_ 

/* ************************************************************************** */
/*                         ----- Account Class -----                          */
/* ************************************************************************** */

class Account
{
private:
	static int m_noOfAccounts;
	static int m_totalAmount;
	static int m_totalNbDeposits;
	static int m_totalNbWithdrawals;

	// To use time functions --> #include <ctime> 
	static void m_displayTimestamp(void);
	// Displays the current timestamp (Will be used in displayAccountsInfos() )

	int m_accountIndex;
	int m_amount;
	int m_noOfDeposits;
	int m_noOfWithdrawals;

	Account(void);
public:
	using acc = Account;

	static int getNoOfAccounts(void);       // Returns the number of accounts 
	static int getTotalAmount(void);        // Returns the total amount of all accounts 
	static int getNbDeposits(void);         // Returns the number of deposits 
	static int getNoOfWithdrawals(void);    // Returns the number of withdrawals 
	static void displayAccountsInfos(void); // Displays the number of accounts, the total 
	// amount of deposits, the total amount of withdrawals, and the total amount of all accounts

	Account(int initial_deposit);
	~Account(void);

	void makeDeposit(int deposit);
	bool makeWithdrawal(int withdrawal);
	int checkAmount(void) const;
	void displayStatus(void) const;





};

#endif /* _ACCOUNT_H_ */

int Account::m_noOfAccounts = 0;
int Account::m_totalAmount = 0;
int Account::m_totalNbDeposits = 0;
int Account::m_totalNbWithdrawals = 0;

int Account::getNoOfAccounts(void) {
	return m_noOfAccounts;
}
int Account::getTotalAmount(void) {
	return m_totalAmount;
}
int Account::getNbDeposits(void)
{
	return m_totalNbDeposits;
}
int Account::getNoOfWithdrawals(void) {
	return m_totalNbWithdrawals;
}
void Account::displayAccountsInfos(void) {

	std::cout << "\n-------------------------------------------------------------\n";
	std::cout << "The number of accounts:          " << getNoOfAccounts() << std::endl;
	std::cout << "The total amount of deposits:    " << getNbDeposits() << std::endl;
	std::cout << "The total amount of withdrawals: " << getNoOfWithdrawals() << std::endl;
	std::cout << "The total amount of all accounts: " << getTotalAmount() << std::endl;
	std::cout << "-------------------------------------------------------------\n\n";


}

// Account::getTotalAmount

Account::Account(int initial_deposit): m_accountIndex(m_noOfAccounts), m_amount(initial_deposit), 
m_noOfDeposits(0), m_noOfWithdrawals(0)
{
	++m_noOfAccounts;
	m_totalAmount += initial_deposit;
	std::cout << "Account " << m_accountIndex << " created successfully; " << "initial deposit: " << initial_deposit << std::endl;
}

// Destructor
Account::~Account(void)
{
	std::cout << "Account " << m_accountIndex << "; closed; " << "final amount: " << m_amount << std::endl;
}

void Account::m_displayTimestamp(void)
{
	std::time_t now = std::time(nullptr);
	std::tm tm_buf;
	std::tm* ptm = nullptr;
#ifdef _WIN32
	localtime_s(&tm_buf, &now);
	ptm = &tm_buf;
#else
	ptm = localtime_r(&now, &tm_buf);
#endif
	char buffer[32];
	// Format: YYYY/MM/DD : HH:MM:SS
	std::strftime(buffer, 32, "[%Y/%m/%d : %H:%M:%S]", ptm);
	std::cout << buffer;
	std::cout << std::endl;
}

void Account::makeDeposit(int deposit) {
	std::cout << "\n-------------------------------------------------------------\n";
	m_amount += deposit;
	m_totalAmount += deposit;
	m_totalNbDeposits++;
	m_noOfDeposits++;
	m_displayTimestamp();
	std::cout << " Account " << m_accountIndex
		<< "; deposit: " << deposit
		<< "; new amount: " << m_amount << std::endl;
	std::cout << "-------------------------------------------------------------\n";

}
bool Account::makeWithdrawal(int withdrawal) {
	std::cout << "\n-------------------------------------------------------------\n";
	m_displayTimestamp();
	std::cout << " Account " << m_accountIndex;
	if (withdrawal <= m_amount)
	{
		m_amount -= withdrawal;
		m_noOfWithdrawals++;
		m_totalNbWithdrawals++;
		m_totalAmount -= withdrawal;
		std::cout << "; withdrawal: " << withdrawal
			<< "; new amount: " << m_amount << std::endl;
		return true;
	}
	else
	{
		std::cout << "; withdrawal: refused" << std::endl;
		return false;
	}
	std::cout << "-------------------------------------------------------------\n";
}
int Account::checkAmount(void) const {
	return m_amount;
}
void Account::displayStatus(void) const {
	std::cout << "\n-------------------------------------------------------------\n";
	m_displayTimestamp();
	std::cout << "Account " << m_accountIndex
		<< "\namount: " << m_amount
		<< "\ndeposits: " << m_noOfDeposits
		<< "\nwithdrawals: " << m_noOfWithdrawals << std::endl;
	std::cout << "-------------------------------------------------------------\n";

}

int main()
{
	Account acc1(100);
	Account acc2(200);
	Account acc3(300);

	acc1.makeDeposit(50);
	acc2.makeDeposit(100);
	acc3.makeDeposit(150);

	acc1.makeWithdrawal(30);
	acc2.makeWithdrawal(200);
	acc3.makeWithdrawal(500); // This should be refused

	acc1.displayStatus();
	acc2.displayStatus();
	acc3.displayStatus();

	Account::displayAccountsInfos();

	return 0;
}