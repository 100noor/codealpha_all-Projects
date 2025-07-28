#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_CUSTOMERS = 10;
const int MAX_TRANSACTIONS = 100;

struct Transaction {
    char type[20];        
    double amount;
    char description[50]; 
};

struct Account {
    int accountId;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
};

struct Customer {
    int id;
    char name[30];
    Account account;
};

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

void addCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        cout << "Maximum number of customers reached!" << endl;
        return;
    }

    Customer c;
    c.id = customerCount + 1;
    cout << "Enter name for Customer " << c.id << ": ";
    cin.ignore();
    cin.getline(c.name, 30);
    c.account.accountId = c.id;
    c.account.balance = 0;
    c.account.transactionCount = 0;

    customers[customerCount++] = c;
    cout << "Customer added successfully!\n\n";
}

int findCustomerIndex(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id)
            return i;
    }
    return -1;
}

void deposit() {
    int id;
    double amount;
    cout << "Enter customer ID to deposit: ";
    cin >> id;

    int index = findCustomerIndex(id);
    if (index == -1) {
        cout << "Customer not found!\n";
        return;
    }

    cout << "Enter amount to deposit: ";
    cin >> amount;

    customers[index].account.balance += amount;

    Transaction t;
    strcpy(t.type, "Deposit");
    t.amount = amount;
    strcpy(t.description, "Cash deposit");
    customers[index].account.transactions[customers[index].account.transactionCount++] = t;

    cout << "Amount deposited successfully!\n";
}

void withdraw() {
    int id;
    double amount;
    cout << "Enter customer ID to withdraw: ";
    cin >> id;

    int index = findCustomerIndex(id);
    if (index == -1) {
        cout << "Customer not found!\n";
        return;
    }

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount > customers[index].account.balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    customers[index].account.balance -= amount;

    Transaction t;
    strcpy(t.type, "Withdraw");
    t.amount = amount;
    strcpy(t.description, "Cash withdrawal");
    customers[index].account.transactions[customers[index].account.transactionCount++] = t;

    cout << "Amount withdrawn successfully!\n";
}

void transfer() {
    int fromId, toId;
    double amount;
    cout << "Enter your Customer ID (from): ";
    cin >> fromId;
    cout << "Enter Receiver Customer ID (to): ";
    cin >> toId;
    cout << "Enter amount to transfer: ";
    cin >> amount;

    int fromIndex = findCustomerIndex(fromId);
    int toIndex = findCustomerIndex(toId);

    if (fromIndex == -1 || toIndex == -1) {
        cout << "One or both customers not found!\n";
        return;
    }

    if (customers[fromIndex].account.balance < amount) {
        cout << "Insufficient balance for transfer!\n";
        return;
    }

    customers[fromIndex].account.balance -= amount;
    customers[toIndex].account.balance += amount;

    
    Transaction t1;
    strcpy(t1.type, "Transfer");
    t1.amount = amount;
    char desc1[50];
    sprintf(desc1, "To ID %d", toId);
    strcpy(t1.description, desc1);
    customers[fromIndex].account.transactions[customers[fromIndex].account.transactionCount++] = t1;

    
    Transaction t2;
    strcpy(t2.type, "Receive");
    t2.amount = amount;
    char desc2[50];
    sprintf(desc2, "From ID %d", fromId);
    strcpy(t2.description, desc2);
    customers[toIndex].account.transactions[customers[toIndex].account.transactionCount++] = t2;

    cout << "Transfer completed successfully!\n";
}

void viewAccountDetails() {
    int id;
    cout << "Enter customer ID to view account: ";
    cin >> id;

    int index = findCustomerIndex(id);
    if (index == -1) {
        cout << "Customer not found!\n";
        return;
    }

    Customer c = customers[index];
    cout << "\n--- Account Details ---\n";
    cout << "Customer ID: " << c.id << endl;
    cout << "Name: " << c.name << endl;
    cout << "Account ID: " << c.account.accountId << endl;
    cout << fixed << setprecision(2) << "Balance: pkr" << c.account.balance << endl;

    cout << "\n--- Transaction History ---\n";
    for (int i = 0; i < c.account.transactionCount; i++) {
        Transaction t = c.account.transactions[i];
        cout << t.type << " of pkr" << fixed << setprecision(2) << t.amount << " | " << t.description << endl;
    }
    cout << endl;
}

void menu() {
    int choice;
    do {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Add Customer\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. View Account Details\n";
        cout << "6. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: transfer(); break;
            case 5: viewAccountDetails(); break;
            case 6: cout << "Thank you for using the Banking System!\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}

