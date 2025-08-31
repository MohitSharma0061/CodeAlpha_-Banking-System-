#include <iostream>
#include <vector>
#include <iomanip>  // for fixed and setprecision
using namespace std;

// Account class
class Account {
private:
    int accountNumber;
    string ownerName;
    double balance;
    vector<string> transactions;

public:
    Account(int accNo, string owner, double initialBalance = 0.0) {
        accountNumber = accNo;
        ownerName = owner;
        balance = initialBalance;
        transactions.push_back("Account created with balance: " + to_string(initialBalance));
    }

    int getAccountNumber() { return accountNumber; }
    string getOwnerName() { return ownerName; }
    double getBalance() { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back("Deposited: " + to_string(amount));
            cout << " Deposit successful.\n";
        } else {
            cout << " Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back("Withdrew: " + to_string(amount));
            cout << " Withdrawal successful.\n";
        } else {
            cout << " Invalid or insufficient balance.\n";
        }
    }

    void displayTransactions() {
        cout << "\n Transaction History for Account " << accountNumber << ":\n";
        for (string t : transactions) {
            cout << " - " << t << endl;
        }
    }

    void displayDetails() {
        cout << fixed << setprecision(2);  // Show only 2 decimal places
        cout << "\n Account Details\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner: " << ownerName << endl;
        cout << "Balance: " << balance << endl;
    }
};

// Bank system class
class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount(int accNo, string owner, double initialBalance = 0.0) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo) {
                cout << " Error: Account number already exists.\n";
                return;
            }
        }
        accounts.push_back(Account(accNo, owner, initialBalance));
        cout << "Account created successfully!\n";
    }

    Account* findAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo) {
                return &acc;
            }
        }
        cout << " Account not found.\n";
        return nullptr;
    }
};

// Main program
int main() {
    Bank bank;
    int choice, accNo;
    string owner;
    double amount;

    while (true) {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. View Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Owner Name: ";
                cin >> owner;
                cout << "Enter Initial Balance: ";
                cin >> amount;
                bank.createAccount(accNo, owner, amount);
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                if (Account* acc = bank.findAccount(accNo)) {
                    acc->deposit(amount);
                }
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                if (Account* acc = bank.findAccount(accNo)) {
                    acc->withdraw(amount);
                }
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNo;
                if (Account* acc = bank.findAccount(accNo)) {
                    acc->displayDetails();
                }
                break;

            case 5:
                cout << "Enter Account Number: ";
                cin >> accNo;
                if (Account* acc = bank.findAccount(accNo)) {
                    acc->displayTransactions();
                }
                break;

            case 6:
                cout << " Exiting system. Goodbye!\n";
                return 0;

            default:
                cout << " Invalid choice. Try again.\n";
        }
    }
}

