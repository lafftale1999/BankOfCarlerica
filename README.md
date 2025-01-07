# BankOfCarlerica

## Content
1. [Description](#description)
2. [Functionality](#functionality)
3. [Installation](#installation)
4. [User Instructions](#user-instructions)

---

## 1. Description
This is a project aimed at learning more about search algorithms and datastructures. My personal goal was to simulate a banking system where the user can act as a banker with access to the system.

---

## 2. Functionality
- Generating random clients using the GenerateClients class.
- Binary search for Clients in ClientStorage.
- Linear search in file via TransactionLink, which also search and adds to a templated cache.
- Templated queue which is used simulate random customers.
- AccountStorage contains a map of {"Account", Account}.
- All banking features as new client, new account, close account, update balance and see transaction history.

---

## 3. Installation
- Languages used: C++ and Makefile
- Compiler: G++

## 4. User Instructions
If it's the first time using the program, make sure that the files transactions.txt, clients.txt and accounts.txt contains data. If that's the case, just run the BankOfCarlerica.exe file in the root directory of the project. Otherwhise uncomment GenerateClients in main.cpp and let it do some magic stuff. This will take some time, maybe a minute or two depending or you computerado.
  
The program contains an easily navigated menu using a numbered list and user input. All choices will be made between 0 - N and then "Enter".
