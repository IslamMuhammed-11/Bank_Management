# Bank_Management

💳 Bank Management System (C++)

A console-based Bank Management System built with C++ using a functional programming approach.
This project focuses on clean separation of concerns, file handling, and manual data serialization using plain text.

🚀 Features
📋 Show all Clients
➕ Add new Client
❌ Delete Client
✏️ Update Client info
🔍 Find Client by account number
💰 Deposit Money
💸 Withdraw Money
📊 Show total Balances Across all clients
🧠 Concepts Practiced

This project was built to Strengthen core programming Skills and Foundations:

Functional Programming (no OOP, pure functions style)
Separation of Concerns (UI / Logic / Data clearly separated)
File Handling (Read / Write using fstream)
Data Persistence using plain text files
Manual Serialization & Deserialization
Custom split() function
Custom record-to-line and line-to-record conversion

🗂️ Data Storage

All data is stored in a simple text file:
"Clients.txt"

Each client is saved in this format:
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance

Example:
A123#//#1234#//#Eslam Mohammed#//#01012345678#//#5000

⚙️ How It Works
Data is loaded from file into a vector<stClient>
All operations (add/update/delete) modify the vector
Changes are written back to the file
Deletion is handled using a markToDelete flag
Transactions update balances and persist immediately

🧩 Project Structure
UI Layer → Menus & user interaction
Logic Layer → Business operations (add, delete, update, etc.)
Data Layer → File read/write + parsing

🛠️ Technologies Used
C++
STL (vector, string, fstream, iomanip)
Console-based interface

▶️ How to Run
Clone the repo
Open in any C++ compiler (VS / CodeBlocks / g++)
Run the program

🎯 What I Learned
How to design a real-world system without OOP
Managing state using vectors and files
Writing clean reusable functions
Handling edge cases (duplicate accounts, insufficient balance, etc.)
Building a full CRUD system from scratch

📌 Future Improvements
Convert to OOP design (Classes & encapsulation)
Add authentication system (users & roles)

💡 Notes
This project is meant for practice and learning, not production use.
