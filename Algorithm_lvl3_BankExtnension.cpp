#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void showAllClients();
void addNewClients();
void deleteClient();
void updateClient();
void findClient();
void exitScreen();
void mainMenu();
void goBackToMainMenu();
void goBackToTransactionMenu();
void depositScreen();
void withdrawScreen();
void totalBalanceScreen();
void transactionMenu();

const string clientFileName = "Clients.txt";
const string usersFileName = "users.txt";
//Structures
struct stClient {
    string accountNumber;
    string pinCode;
    string name;
    string phoneNumber;
    double accountBalance = 0;
    bool markToDelete = false;
};
// Enums
enum enMainMenuChoices { show = 1, add = 2, del = 3, update = 4, serach = 5, transactions = 6, endApp = 7 };
enum enTransactionMenuChoices { deposit = 1, withdraw = 2, totalBalance = 3, goBack = 4 };
// General Functions
string readString() {
    string s1 = "";
    cout << "Please Enter Account Number? ";
    getline(cin >> ws, s1);
    return s1;
}

vector<string>split(string line, string delim = "#//#") {

    vector<string>split;
    string sWord;
    short pos = 0;
    while ((pos = line.find(delim)) != std::string::npos)
    {
        sWord = line.substr(0, pos);
        if (sWord != "")
        {
            split.push_back(sWord);
        }
        line.erase(0, pos + delim.length());
    }
    if (line != "")
    {
        split.push_back(line);
    }
    return split;
}

stClient convertLineToRecord(string line, string delim = "#//#") {
    stClient record;
    vector<string>data;
    data = split(line, delim);
    record.accountNumber = data[0];
    record.pinCode = data[1];
    record.name = data[2];
    record.phoneNumber = data[3];
    record.accountBalance = stod(data[4]);
    return record;
}

string convertRecordToLine(stClient record, string delim = "#//#") {
    string line = "";
    line += record.accountNumber + delim;
    line += record.pinCode + delim;
    line += record.name + delim;
    line += record.phoneNumber + delim;
    line += to_string(record.accountBalance);
    return line;
}

vector<stClient>loadRecordsFromFile(string fileName) {

    vector<stClient>vClients;
    fstream myFile;
    myFile.open(fileName, ios::in);
    string line;
    stClient client;
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            client = convertLineToRecord(line);
            vClients.push_back(client);
        }
    }
    return vClients;

}

bool findClientByAccountNumber(string accountNumber, vector<stClient>& vClients, stClient& client) {

    for (stClient& C : vClients) {
        if (C.accountNumber == accountNumber)
        {
            client = C;
            return true;
        }

    }
    return false;
}

bool checkIfClientAlreadySinged(string accountNumber) {

    vector<stClient>vClients = loadRecordsFromFile(clientFileName);

    for (stClient& C : vClients) {

        if (C.accountNumber == accountNumber)
        {
            return true;
        }
    }
    return false;
}

void printRecord(stClient record) {

    cout << "\nThe Following are Client Record\n\n";

    cout << setw(17) << left << "Account Number" << ": " << record.accountNumber << endl;
    cout << setw(17) << left << "Pin Code" << ": " << record.pinCode << endl;
    cout << setw(17) << left << "Name" << ": " << record.name << endl;
    cout << setw(17) << left << "Phone Number" << ": " << record.phoneNumber << endl;
    cout << setw(17) << left << "Account Balance" << ": " << record.accountBalance << endl << endl;
}

vector<stClient>saveDataToFile(string fileName, vector<stClient>& vClient) {
    fstream myFile;
    myFile.open(fileName, ios::out);
    if (myFile.is_open())
    {
        string dataLine;
        for (stClient& c : vClient) {
            if (c.markToDelete == false)
            {
                dataLine = convertRecordToLine(c);
                myFile << dataLine << endl;
            }

        }
        myFile.close();
    }
    return vClient;
}
//Show All Clients
void headerOfClientList(int size) {

    cout << setw(50) << "Client List (" << size << ") Client/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Account Number" << setw(3) << "|";
    cout << " Pin Code" << setw(3) << "|";
    cout << " Client Name" << setw(30) << "|";
    cout << " Phone" << setw(10) << "|";
    cout << " Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";

}

void printList(stClient data) {

    cout << "|" << left << setw(17) << data.accountNumber << "|";
    cout << left << setw(11) << data.pinCode << "|";
    cout << left << setw(41) << data.name << "|";
    cout << left << setw(15) << data.phoneNumber << "|";
    cout << left << data.accountBalance;
    cout << left << endl;
}

void printAllClientsRecords(vector<stClient>& vFileContent) {

    headerOfClientList(vFileContent.size());

    for (stClient& C : vFileContent) {

        printList(C);
    }
}
// Add New Clients
stClient readClient() {
    stClient data;

    cout << "Account Number  ? ";
    getline(cin >> ws, data.accountNumber);
    if (checkIfClientAlreadySinged(data.accountNumber))
    {
        do
        {
            cout << "Client With [" << data.accountNumber << "] Already exists , Enter Another Account Number? ";
            getline(cin >> ws, data.accountNumber);

        } while (checkIfClientAlreadySinged(data.accountNumber));
    }

    cout << "Pin Code        ? ";
    getline(cin, data.pinCode);
    cout << "Name            ? ";
    getline(cin, data.name);
    cout << "Phone number    ? ";
    getline(cin, data.phoneNumber);
    cout << "Account balance ? ";
    cin >> data.accountBalance;

    return data;
}

void addLineToFile(string fileName, string line) {

    fstream myFile;

    myFile.open(fileName, ios::out | ios::app);
    if (myFile.is_open())
    {
        myFile << line << endl;
    }
    myFile.close();
}

void addClientToFile() {
    stClient data = readClient();
    addLineToFile(clientFileName, convertRecordToLine(data));

}

void addClientsLoop() {
    char addMore = 'Y';
    do
    {
        system("cls");
        cout << "\nAdd New Client!\n\n";
        addClientToFile();
        cout << "Client Added Successfully, Do You Want to Add More? y / n ";
        cin >> addMore;
    } while (toupper(addMore) == 'Y');

}
// Delete Client
bool markClientToDelete(string accountNumber, vector<stClient>& vClients) {

    for (stClient& C : vClients) {
        if (C.accountNumber == accountNumber)
        {
            C.markToDelete = true;
            return true;
        }
    }
    return false;
}

bool deleteClientByAccountNumber(string accountNumber, vector<stClient>& vClients) {
    stClient client;
    char answer = 'n';
    if (findClientByAccountNumber(accountNumber, vClients, client))
    {
        printRecord(client);
        cout << "\n\n Are You Sure You Want To Delete This Client ? y/n ";
        cin >> answer;
        if (toupper(answer) == 'Y')
        {
            markClientToDelete(accountNumber, vClients);
            saveDataToFile(clientFileName, vClients);
            vClients = loadRecordsFromFile(clientFileName);
            cout << "\n\n Deleted Successfully\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nclient With [" << accountNumber << "] is not Found!\n\n";
        return false;
    }
}
// Update Client
stClient updateClientInfo(string accountNumber) {
    stClient data;
    data.accountNumber = accountNumber;
    cout << "Pin Code        ? ";
    getline(cin >> ws, data.pinCode);
    cout << "Name            ? ";
    getline(cin, data.name);
    cout << "Phone number    ? ";
    getline(cin, data.phoneNumber);
    cout << "Account balance ? ";
    cin >> data.accountBalance;
    return data;
}

bool updateClientRecord(string accountNumber, vector<stClient>& vClient) {
    stClient client;
    char answer = 'Y';
    if (findClientByAccountNumber(accountNumber, vClient, client))
    {
        printRecord(client);
        cout << "\n\n Are You Sure You Want To Update This Client's Record? y/n ";
        cin >> answer;
        if (toupper(answer) == 'Y')
        {
            for (stClient& c : vClient) {
                if (c.accountNumber == accountNumber)
                {
                    c = updateClientInfo(accountNumber);
                    break;
                }
            }
            saveDataToFile(clientFileName, vClient);
            cout << "\nClient Updated Successfully\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nclient With [" << accountNumber << "] is not Found!\n\n";
        return false;
    }
}
//User's Choices
enMainMenuChoices mainMenuChoices() {
    short choice = 0;
    do
    {
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice > 7 || choice < 1);

    return (enMainMenuChoices)choice;

}

enTransactionMenuChoices transactionChoicees() {

    short choice = 0;
    do
    {
        cin >> choice;
    } while (choice > 4 || choice < 1);

    return (enTransactionMenuChoices)choice;

}
//Performances
void performMainMenuChoices(enMainMenuChoices choice) {
    switch (choice)
    {
    case show:
        system("cls");
        showAllClients();
        goBackToMainMenu();
        break;
    case add:
        system("cls");
        addNewClients();
        goBackToMainMenu();
        break;
    case del:
        system("cls");
        deleteClient();
        goBackToMainMenu();
        break;
    case update:
        system("cls");
        updateClient();
        goBackToMainMenu();
        break;
    case serach:
        system("cls");
        findClient();
        goBackToMainMenu();
        break;
    case transactions:
        system("cls");
        transactionMenu();
        break;
    case endApp:
        system("cls");
        exitScreen();
        break;
    default:
        mainMenu();
        break;
    }


}

void performTransactionMenuChoices(enTransactionMenuChoices choice) {
    switch (choice)
    {
    case deposit:
        system("cls");
        depositScreen();
        goBackToTransactionMenu();
        break;
    case withdraw:
        system("cls");
        withdrawScreen();
        goBackToTransactionMenu();
        break;
    case totalBalance:
        system("cls");
        totalBalanceScreen();
        goBackToTransactionMenu();
        break;
    case goBack:
        system("cls");
        mainMenu();
        break;
    default:
        mainMenu();
        break;
    }
}
//Total Balances
double calculateTotalBalance() {
    vector<stClient>vClient = loadRecordsFromFile(clientFileName);

    double totalBalances = 0;
    for (stClient c : vClient) {
        totalBalances += c.accountBalance;
    }
    return totalBalances;
}

void showTotalBalance(int size, vector<stClient>& vClient) {

    cout << setw(50) << "Client List (" << size << ") Client/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Account Number" << setw(3) << "|";
    cout << " Client Name" << setw(30) << "|";
    cout << " Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";
    for (stClient& data : vClient) {
        cout << "|" << left << setw(17) << data.accountNumber << "|";
        cout << left << setw(41) << data.name << "|";
        cout << left << data.accountBalance;
        cout << left << endl;
    }
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";
}
// Function that Deposit Balance To CLient By Account Number.
bool depositBalanceToClientByAccountNumber(double newBalance, string accountNumber, vector<stClient>& vClient) {


    char answer = 'n';
    cout << "Are You Sure You Want To Perform This Transaction ? y/n ";
    cin >> answer;
    if (toupper(answer) == 'Y')
    {
        for (stClient& c : vClient) {

            if (accountNumber == c.accountNumber)
            {
                c.accountBalance += newBalance;
                saveDataToFile(clientFileName, vClient);
                cout << "\nDone Successfully, New Balance is " << c.accountBalance << endl;
                return true;
            }
        }
    }

    return false;
}
// Menus
void mainMenu() {

    system("cls");

    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Main Menu Screen\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << " Show Client List.\n";
    cout << setw(10) << right << "[2]" << " Add New Client.\n";
    cout << setw(10) << right << "[3]" << " Delete Client.\n";
    cout << setw(10) << right << "[4]" << " Update Client Info.\n";
    cout << setw(10) << right << "[5]" << " Find Client.\n";
    cout << setw(10) << right << "[6]" << " Transactions.\n";
    cout << setw(10) << right << "[7]" << " Exit.\n";
    cout << "___________________________________________\n";
    cout << "Choose What You Want To Do? [1 - 7]  ";
    performMainMenuChoices(mainMenuChoices());
}

void transactionMenu() {
    system("cls");
    cout << "___________________________________________\n";
    cout << "\n" << right << setw(27) << "transaction Menu Screen\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << "Deposit\n";
    cout << setw(10) << right << "[2]" << "WithDraw\n";
    cout << setw(10) << right << "[3]" << "Total Balance\n";
    cout << setw(10) << right << "[4]" << "MainMenu\n";
    cout << "___________________________________________\n";
    cout << "Choose What You Want To Do? [1 - 4]  ";
    performTransactionMenuChoices(transactionChoicees());
}

void totalBalanceMenu(stClient data, int size) {
    cout << setw(50) << "Client List (" << size << ") Client/s\n\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| Account Number" << setw(3) << "|";
    cout << " Client Name" << setw(30) << "|";
    cout << " Balance";
    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------\n\n";

    cout << "|" << left << setw(17) << data.accountNumber << "|";
    cout << left << setw(41) << data.name << "|";
    cout << left << data.accountBalance;
    cout << left << endl;
}
//main
int main()
{
    mainMenu();
    system("pause");
    return 0;
}
//Ui Logic
void showAllClients() {
    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    if (clients.size() == 0)
    {
        cout << "\t\t\tNo Clients Available in the system!\n";
    }
    else
    {
        printAllClientsRecords(clients);
    }

}

void addNewClients() {

    cout << "________________________________\n";
    cout << setw(21) << right << "Add Client\n";
    cout << "________________________________\n\n";
    addClientsLoop();



}

void deleteClient() {


    cout << "________________________________\n";
    cout << setw(20) << right << "Delete Client\n";
    cout << "________________________________\n\n";

    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    string accountNumber = readString();

    deleteClientByAccountNumber(accountNumber, clients);

}

void updateClient() {


    cout << "________________________________\n";
    cout << setw(20) << right << "Update Client\n";
    cout << "________________________________\n\n";

    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    string accountNumber = readString();

    updateClientRecord(accountNumber, clients);


}

void findClient() {


    cout << "________________________________\n";
    cout << setw(20) << right << "Find Client\n";
    cout << "________________________________\n\n";

    vector<stClient>clients = loadRecordsFromFile(clientFileName);
    string accountNumber = readString();
    stClient client;

    if (findClientByAccountNumber(accountNumber, clients, client))
    {
        printRecord(client);
    }
    else
    {
        cout << "Client With [" << accountNumber << "] is not Found!\n";
    }
}

void exitScreen() {
    cout << "\n________________________________\n";
    cout << "\t\tProgram Ends (-: \n";
    cout << "\n________________________________\n";
}

void goBackToMainMenu() {
    cout << "\n\nPress Any Key TO Go Back To main Menu...";
    system("pause>0");
    mainMenu();
}

void goBackToTransactionMenu() {

    cout << "\n\nPress Any Key TO Go Back To Transaction Menu...";
    system("pause>0");
    transactionMenu();
}

void depositScreen() {

    cout << "________________________________\n";
    cout << setw(20) << right << "Deposit Screen\n";
    cout << "________________________________\n\n";
    vector<stClient>vClient = loadRecordsFromFile(clientFileName);
    stClient client;
    string accountNumber = readString();
    double deposit = 0;

    while (!findClientByAccountNumber(accountNumber, vClient, client))
    {
        cout << "\n Client with account number (" << accountNumber << ") not Found Please Enter Signed Account Number : ";
        accountNumber = readString();
    }
    printRecord(client);

    cout << "\n\nPlease Enter How Much You Want To Deposit : ";
    cin >> deposit;

    depositBalanceToClientByAccountNumber(deposit, accountNumber, vClient);

}

void withdrawScreen() {

    cout << "________________________________\n";
    cout << setw(20) << right << "Withdraw Screen\n";
    cout << "________________________________\n\n";

    vector<stClient>vClient = loadRecordsFromFile(clientFileName);
    stClient client;
    string accountNumber = readString();
    double withdraw = 0;

    while (!findClientByAccountNumber(accountNumber, vClient, client))
    {
        cout << "\n Client with account number (" << accountNumber << ") not Found Please Enter Signed Account Number : ";
        accountNumber = readString();
    }

    printRecord(client);

    cout << "\n\nPlease Enter How Much You Want To Withdraw : ";

    cin >> withdraw;

    while (withdraw > client.accountBalance)
    {
        cout << "Sorry , There isn't Enough Money to withdraw You Can withdraw up to : " << client.accountBalance << endl;
        cout << "\n\nPlease Enter How Much You Want To Withdraw : ";
        cin >> withdraw;
    }

    //Using Deposit Function but Sending amount Multplied by -1 To With Draw It.
    depositBalanceToClientByAccountNumber(withdraw * -1, accountNumber, vClient);
}

void totalBalanceScreen() {
    vector<stClient>vClient = loadRecordsFromFile(clientFileName);
    stClient client;

    if (vClient.size() == 0)
    {
        cout << "\t\t\tThere Is No Clients Found!\n";
    }
    else
    {
        showTotalBalance(vClient.size(), vClient);
        cout << "\n\t\t\tTotal Balance = " << calculateTotalBalance();
    }
}
