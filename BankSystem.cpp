#include <iostream>
#include <limits>
using namespace std;


class Account {
protected:
    double balance = 0;

public:
    virtual void deposit() = 0; 
    virtual void withdraw() = 0; 
    double getBalance() {
        return balance;
    }

    void checkBalance() {
        cout << "Current Balance: " << balance << endl;
    }

    
    double getValidAmount() {
        double amount;
        while (true) {
            cin >> amount;
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a valid number: ";
            } else if (amount < 0) {
                cout << "Amount cannot be negative. Enter a valid amount: ";
            } else {
                break;
            }
        }
        return amount;
    }
};


class SavingsAccount : public Account {
public:
    void deposit() override {
        double amount;
        cout << "Savings Account - Deposit\nEnter Amount: ";
        amount = getValidAmount();

        if (balance == 0 && amount < 1000) {
            cout << "Minimum initial deposit for Savings Account should be 1000.\n";
        } else {
            balance += amount;
            cout << "Deposit successful.\n";
        }
    }

    void withdraw() override {
        double amount;
        cout << "Savings Account - Withdraw\nEnter Amount: ";
        amount = getValidAmount();

        if (balance - amount < 1000) {
            cout << "Insufficient balance. You must maintain a minimum balance of 1000.\n";
        } else {
            balance -= amount;
            cout << "Withdrawal successful.\n";
        }
    }
};


class CurrentAccount : public Account {
public:
    void deposit() override {
        double amount;
        cout << "Current Account - Deposit\nEnter Amount: ";
        amount = getValidAmount();

        balance += amount;
        cout << "Deposit successful.\n";
    }

    void withdraw() override {
        double amount;
        cout << "Current Account - Withdraw\nEnter Amount: ";
        amount = getValidAmount();

        if (balance < amount) {
            cout << "Insufficient balance for withdrawal.\n";
        } else {
            balance -= amount;
            cout << "Withdrawal successful.\n";
        }
    }
};

void displayMainMenu() {
    cout << "==================== Canmore Bank ====================\n";
    cout << "Main Menu:\n1 - Savings Account\n2 - Current Account\n3 - Exit\n";
}

void displaySubMenu() {
    cout << "\nSub Menu:\n1 - Deposit\n2 - Withdraw\n3 - Check Balance\n4 - Back\n";
}

int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        } else {
            break;
        }
    }
    return choice;
}

int main() {
    SavingsAccount savings;
    CurrentAccount current;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMainMenu();
        int mainChoice = getValidChoice(1, 3);

        switch (mainChoice) {
        case 1: { 
            bool backToMain = false;
            while (!backToMain) {
                displaySubMenu();
                int subChoice = getValidChoice(1, 4);

                switch (subChoice) {
                case 1:
                    savings.deposit();
                    break;
                case 2:
                    savings.withdraw();
                    break;
                case 3:
                    savings.checkBalance();
                    break;
                case 4:
                    backToMain = true;
                    break;
                }
            }
            break;
        }
        case 2: { 
            bool backToMain = false;
            while (!backToMain) {
                displaySubMenu();
                int subChoice = getValidChoice(1, 4);

                switch (subChoice) {
                case 1:
                    current.deposit();
                    break;
                case 2:
                    current.withdraw();
                    break;
                case 3:
                    current.checkBalance();
                    break;
                case 4:
                    backToMain = true;
                    break;
                }
            }
            break;
        }
        case 3:
            exitProgram = true;
            cout << "Thank you for using Canmore Bank. Goodbye!\n";
            break;
        }
    }

    return 0;
}
