# Bank Management Application 🏦

A console-based Bank Management Application built in **C++** that simulates core banking operations using object-oriented programming and file handling.

---

## 📌 Project Overview

This project is developed as part of the **Thiranex C++ Internship Program**. It demonstrates real-world banking operations such as deposits, withdrawals, and balance inquiries while maintaining persistent customer records using binary file handling.

---

## ✨ Features

- 🏧 **Create Account** — Open a new Savings or Current account with minimum deposit validation
- 💰 **Deposit** — Add funds to an existing account
- 💸 **Withdraw** — Withdraw funds with insufficient balance check
- 📊 **Balance Enquiry** — Check account details and current balance
- 📋 **Display All Accounts** — View all customer accounts in a formatted table
- 🗑️ **Delete Account** — Permanently remove an account record
- 💾 **Persistent Storage** — All data stored in a binary file (`accounts.dat`)

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:** Structs, Binary File I/O (`fstream`), OOP principles, Input validation, Menu-driven operations

---

## 🚀 How to Run

### Prerequisites
- A C++ compiler (g++ recommended)

### Compile & Run

```bash
# Compile
g++ main.cpp -o bank_management

# Run on Linux/Mac
./bank_management

# Run on Windows
bank_management.exe
```

---

## 📂 File Structure

```
Bank-management-application-cpp/
│
├── main.cpp          # Main source code
├── README.md         # Project documentation
└── .gitignore        # Ignores generated data files
```

---

## 📸 Menu Preview

```
  ╔══════════════════════════════════════════╗
  ║       BANK MANAGEMENT APPLICATION       ║
  ╚══════════════════════════════════════════╝

       1.  Create Account
       2.  Deposit
       3.  Withdraw
       4.  Balance Enquiry
       5.  Display All Accounts
       6.  Delete Account
       7.  Exit
```

---

## 📝 Expected Outcome

A secure and functional banking system capable of performing deposits, withdrawals, and balance inquiries while maintaining persistent customer records.

---

## 👨‍💻 Author

Developed by **ARULSELVAN** as part of the Thiranex Internship Program.
