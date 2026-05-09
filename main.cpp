#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include<cstring>
using namespace std;

// ─────────────────────────────────────────────
//  Account Structure
// ─────────────────────────────────────────────
struct Account {
    int    accNumber;
    char   name[50];
    char   type[20];       // Savings / Current
    double balance;
    long long phone;
};

const string FILE_NAME = "accounts.dat";

// ─────────────────────────────────────────────
//  Utility helpers
// ─────────────────────────────────────────────
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printHeader(const string& title) {
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║   " << left << setw(41) << title << "║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
}

void printTableHeader() {
    cout << "  " << string(75, '-') << "\n";
    cout << "  " << left
         << setw(10) << "Acc No."
         << setw(22) << "Name"
         << setw(12) << "Type"
         << setw(16) << "Balance (INR)"
         << setw(14) << "Phone"
         << "\n";
    cout << "  " << string(75, '-') << "\n";
}

void printAccount(const Account& a) {
    cout << "  " << left
         << setw(10) << a.accNumber
         << setw(22) << a.name
         << setw(12) << a.type
         << setw(16) << fixed << setprecision(2) << a.balance
         << setw(14) << a.phone
         << "\n";
}

bool accExists(int accNo) {
    ifstream fin(FILE_NAME, ios::binary);
    Account a;
    while (fin.read(reinterpret_cast<char*>(&a), sizeof(a)))
        if (a.accNumber == accNo) { fin.close(); return true; }
    fin.close();
    return false;
}

// ─────────────────────────────────────────────
//  1. CREATE ACCOUNT
// ─────────────────────────────────────────────
void createAccount() {
    clearScreen();
    printHeader("CREATE NEW ACCOUNT");

    Account a;

    cout << "  Enter Account Number : ";
    cin  >> a.accNumber;

    if (accExists(a.accNumber)) {
        cout << "\n  ✖  Account " << a.accNumber << " already exists!\n";
        pause(); return;
    }

    cin.ignore();
    cout << "  Enter Account Holder Name : "; cin.getline(a.name, 50);

    cout << "  Account Type (1-Savings / 2-Current) : ";
    int t; cin >> t;
    if (t == 1) strcpy(a.type, "Savings");
    else        strcpy(a.type, "Current");

    cout << "  Initial Deposit (min ₹500) : ";
    while (!(cin >> a.balance) || a.balance < 500) {
        cout << "  Minimum deposit is ₹500. Try again: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "  Phone Number : ";
    cin  >> a.phone;

    ofstream fout(FILE_NAME, ios::binary | ios::app);
    fout.write(reinterpret_cast<char*>(&a), sizeof(a));
    fout.close();

    cout << "\n  ✔  Account created successfully!\n";
    pause();
}

// ─────────────────────────────────────────────
//  2. DEPOSIT
// ─────────────────────────────────────────────
void deposit() {
    clearScreen();
    printHeader("DEPOSIT AMOUNT");

    int accNo;
    cout << "  Enter Account Number : ";
    cin  >> accNo;

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    if (!file) { cout << "\n  No records found.\n"; pause(); return; }

    Account a;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&a), sizeof(a))) {
        if (a.accNumber == accNo) {
            found = true;
            double amt;
            cout << "  Current Balance : ₹" << fixed << setprecision(2) << a.balance << "\n";
            cout << "  Enter Deposit Amount : ₹";
            while (!(cin >> amt) || amt <= 0) {
                cout << "  Invalid amount. Try again: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            a.balance += amt;
            file.seekp(-static_cast<int>(sizeof(a)), ios::cur);
            file.write(reinterpret_cast<char*>(&a), sizeof(a));
            cout << "\n  ✔  ₹" << fixed << setprecision(2) << amt << " deposited successfully!\n";
            cout << "  New Balance : ₹" << a.balance << "\n";
            break;
        }
    }
    file.close();
    if (!found) cout << "\n  ✖  Account not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  3. WITHDRAW
// ─────────────────────────────────────────────
void withdraw() {
    clearScreen();
    printHeader("WITHDRAW AMOUNT");

    int accNo;
    cout << "  Enter Account Number : ";
    cin  >> accNo;

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    if (!file) { cout << "\n  No records found.\n"; pause(); return; }

    Account a;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&a), sizeof(a))) {
        if (a.accNumber == accNo) {
            found = true;
            double amt;
            cout << "  Current Balance : ₹" << fixed << setprecision(2) << a.balance << "\n";
            cout << "  Enter Withdrawal Amount : ₹";
            while (!(cin >> amt) || amt <= 0) {
                cout << "  Invalid amount. Try again: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (amt > a.balance) {
                cout << "\n  ✖  Insufficient balance!\n";
            } else {
                a.balance -= amt;
                file.seekp(-static_cast<int>(sizeof(a)), ios::cur);
                file.write(reinterpret_cast<char*>(&a), sizeof(a));
                cout << "\n  ✔  ₹" << fixed << setprecision(2) << amt << " withdrawn successfully!\n";
                cout << "  Remaining Balance : ₹" << a.balance << "\n";
            }
            break;
        }
    }
    file.close();
    if (!found) cout << "\n  ✖  Account not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  4. BALANCE CHECK
// ─────────────────────────────────────────────
void checkBalance() {
    clearScreen();
    printHeader("BALANCE ENQUIRY");

    int accNo;
    cout << "  Enter Account Number : ";
    cin  >> accNo;

    ifstream fin(FILE_NAME, ios::binary);
    if (!fin) { cout << "\n  No records found.\n"; pause(); return; }

    Account a;
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&a), sizeof(a))) {
        if (a.accNumber == accNo) {
            found = true;
            cout << "\n  ─── Account Details ──────────────────────\n";
            cout << "  Account No : " << a.accNumber << "\n";
            cout << "  Name       : " << a.name      << "\n";
            cout << "  Type       : " << a.type      << "\n";
            cout << "  Balance    : ₹" << fixed << setprecision(2) << a.balance << "\n";
            cout << "  Phone      : " << a.phone     << "\n";
            cout << "  ──────────────────────────────────────────\n";
            break;
        }
    }
    fin.close();
    if (!found) cout << "\n  ✖  Account not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  5. DISPLAY ALL ACCOUNTS
// ─────────────────────────────────────────────
void displayAll() {
    clearScreen();
    printHeader("ALL ACCOUNT RECORDS");

    ifstream fin(FILE_NAME, ios::binary);
    if (!fin) { cout << "  No records found.\n"; pause(); return; }

    Account a;
    int count = 0;
    printTableHeader();

    while (fin.read(reinterpret_cast<char*>(&a), sizeof(a))) {
        printAccount(a);
        count++;
    }
    fin.close();

    cout << "  " << string(75, '-') << "\n";
    if (count == 0) cout << "  No account records found.\n";
    else            cout << "  Total Accounts: " << count << "\n";
    pause();
}

// ─────────────────────────────────────────────
//  6. DELETE ACCOUNT
// ─────────────────────────────────────────────
void deleteAccount() {
    clearScreen();
    printHeader("DELETE ACCOUNT");

    int accNo;
    cout << "  Enter Account Number to delete : ";
    cin  >> accNo;

    ifstream fin(FILE_NAME, ios::binary);
    if (!fin) { cout << "\n  No records found.\n"; pause(); return; }

    ofstream fout("temp.dat", ios::binary);
    Account a;
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&a), sizeof(a))) {
        if (a.accNumber == accNo) { found = true; continue; }
        fout.write(reinterpret_cast<char*>(&a), sizeof(a));
    }
    fin.close(); fout.close();

    remove(FILE_NAME.c_str());
    rename("temp.dat", FILE_NAME.c_str());

    if (found) cout << "\n  ✔  Account " << accNo << " deleted successfully!\n";
    else       cout << "\n  ✖  Account not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────────
void showMenu() {
    clearScreen();
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║       BANK MANAGEMENT APPLICATION        ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
    cout << "       1.  Create Account\n";
    cout << "       2.  Deposit\n";
    cout << "       3.  Withdraw\n";
    cout << "       4.  Balance Enquiry\n";
    cout << "       5.  Display All Accounts\n";
    cout << "       6.  Delete Account\n";
    cout << "       7.  Exit\n\n";
    cout << "  Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        while (!(cin >> choice)) {
            cout << "  Invalid input. Enter a number: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit();       break;
            case 3: withdraw();      break;
            case 4: checkBalance();  break;
            case 5: displayAll();    break;
            case 6: deleteAccount(); break;
            case 7:
                clearScreen();
                cout << "\n  Thank you for using Bank Management Application!\n\n";
                break;
            default:
                cout << "\n  ✖  Invalid choice! Enter 1-7.\n";
                pause();
        }
    } while (choice != 7);
    return 0;
}
