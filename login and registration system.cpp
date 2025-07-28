#include <iostream>
#include <string>
using namespace std;


const int MAX_USERS = 100;


struct User {
    string username;
    string password;
};


bool usernameExists(User users[], int userCount, string uname) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == uname) {
            return true;
        }
    }
    return false;
}


void registerUser(User users[], int &userCount) {
    if (userCount >= MAX_USERS) {
        cout << "?? Maximum user limit reached.\n";
        return;
    }

    string uname, pass;
    cout << "\n--- Registration ---\n";
    cout << "Enter username: ";
    cin >> uname;

    if (usernameExists(users, userCount, uname)) {
        cout << "?? Username already taken. Try a different one.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> pass;
    
    if (uname.length() < 3 || pass.length() < 4) {
        cout << "?? Username must be 3+ chars and password 4+ chars.\n";
        return;
    }

    
    users[userCount].username = uname;
    users[userCount].password = pass;
    userCount++;

    cout << "? Registration successful!\n";
}


void loginUser(User users[], int userCount) {
    string uname, pass;
    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pass;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == uname && users[i].password == pass) {
            cout << "? Login successful! Welcome, " << uname << ".\n";
            return;
        }
    }
    cout << "? Invalid username or password!\n";
}


int main() {
    User users[MAX_USERS];
    int userCount = 0;
    int choice;

    do {
        cout << "\n===== Login & Registration System =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users, userCount);
                break;
            case 2:
                loginUser(users, userCount);
                break;
            case 3:
                cout << "?? Exiting... Thank you!\n";
                break;
            default:
                cout << "?? Invalid option. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}

