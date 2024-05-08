#include <iostream>
#include <string>
#include <ctime>
#include<cstdlib>
#include <cstdio>
#include<fstream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iomanip>

#define maxStations 100
#define MaxUser 10
#define MaxSub 100
using namespace std;
int constantPrice[4] = {6,8,12,15};
int indexOfUsers = 0;
int numSub = 1;
int NumberOfStations;
int firstLineStations, secondLineStations, thirdLineStations;
int lineStations[3] = { firstLineStations, secondLineStations, thirdLineStations };
int transitionStations[10];
struct Ride {
    string rideID;
    string checkInStation;
    string checkOutStation;
    string rideDate;
    float cost;
};

struct Subscription {
    string subName;
    string startDate;
    string endDate;
    int ValidityDays;
    char index;
    int stage;
    int ridesCount;
    float price[4];
    int fullRides;
}SubTypes[4];

struct Account {
    string username;
    string email;
    string password;
};

struct User {
    int id;
    Account UserAccount;
    float balance;
    Subscription Sub;
    Ride ridedetails[200];
    bool SubFound = false;
    bool signedUp = false;
    int ridesCount;
    float walletMoney;
};

struct MetroStations {
    int id, line;
    char symbol;
    string name;
};

MetroStations stations[3][maxStations];

struct destination {
    string station;
    int id, line;

};

struct departure {
    string station;
    int id, line;

};
bool isBalancePositive(float balance) {
    return balance > 0;
}

Subscription UsersSubscriptionTypes[MaxSub];
User users[MaxUser];
bool login_status; // in each struct
void checkBalance(float balance) {
    bool cannotAdd;

    do{
        if (balance < 0) {
            cout << "Cannot add balance in negative!" << endl;
            cin >> balance;
            cannotAdd = true;


        }
        else if (balance>0) {
            cannotAdd = false;
        }


    } while (cannotAdd == true);
    
    
}
void DeletScreen() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("CLS");
}
int readUserCount() {
    int count = 0;
    ifstream infile("user_count.txt");

    if (infile.is_open()) {
        infile >> count;
        infile.close();
    }
    else {
        cerr << "Warning: User count file not found. Assuming initial count as 0." << endl;
    }

    return count;
}
int realUsers = readUserCount();
departure userDeparture;
destination userDestination;
void UserIdGenerator() {

    users[realUsers].id = realUsers;
}
void IncrementUserNumber() {
    realUsers++;
}
void DecrementUserNumber() {
    realUsers--;
}
bool findEmail(string email, User users[]) {
    for (int i = 0; i < realUsers; i++) {
        if (email == users[i].UserAccount.email)
            return true;
    }
    return false;
}
bool find(string email, string password, User users[]) {
    for (int i = 0; i < realUsers; i++) {
        if (email == users[i].UserAccount.email && password == users[i].UserAccount.password) {
            indexOfUsers = users[i].id;
            return true;

        }
    }
    return false;
}
void StoreTheNumberOfRides() {
    ofstream outfile("numberRides.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            outfile << users[i].Sub.ridesCount << endl;

        }
        outfile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void ReadTheNumberOfRides() {
    fstream infile("numberRides.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            infile >> users[i].Sub.ridesCount;


        }
        infile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void StoreTheNumberOfUsers() {
    ofstream outfile("user_count.txt");

    if (outfile.is_open()) {
        outfile << realUsers << endl;
        outfile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void StoreTheDataOfUsers() {
    ofstream outfile("users.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            outfile << users[i].UserAccount.email << " " << users[i].UserAccount.password << " "
                << users[i].id << " " << users[i].balance << " " << users[i].Sub.subName << " " << users[i].SubFound<<""<<users[i].walletMoney << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open users file." << endl;
    }
}
void StoreTheDataOfRides() {
    ofstream outfile("rides.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            for (int j = 0; j < users[i].Sub.ridesCount; j++) {
                outfile << users[i].ridedetails[j].checkInStation << " " << users[i].ridedetails[j].checkOutStation<<" " << users[i].ridedetails[j].rideID
                    << " " << users[i].ridedetails[j].cost << " " << users[i].ridedetails[j].rideDate << endl;
            }
            cout << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open rides file." << endl;
    }
}
void ReadFromFileTheDataOfRides() {
    ifstream infile("rides.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            for (int j = 0; j < 200 && j < users[i].Sub.ridesCount; j++) {
                infile >> users[i].ridedetails[j].checkInStation >> users[i].ridedetails[j].checkOutStation>> users[i].ridedetails[j].rideID
                    >> users[i].ridedetails[j].cost >> users[i].ridedetails[j].rideDate;
            }
        }
        infile.close();
    }
    else {
        cerr << "Error: Could not open rides file." << endl;
    }
}
bool buyTicket;
void ReadFromFileTheDataOfUsers() {
    ifstream infile("users.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            infile >> users[i].UserAccount.email >> users[i].UserAccount.password
                >> users[i].id >> users[i].balance >> users[i].Sub.subName >> users[i].SubFound;
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open users file." << endl;
    }
}
bool SignUp() {
    User temp;

    cout << "Enter your name or press 0 to exit: ";
    cin >> temp.UserAccount.username;
    if (temp.UserAccount.username == "0") {
        cout << "Exiting sign-up..." << endl;
        return false;
    }
    else {
        users[realUsers].UserAccount.username = temp.UserAccount.username;
    }

    string email;
    while (true) {
        cout << "Enter your email or press 0 to exit: ";
        cin >> email;
        if (email == "0") {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
        if (findEmail(email, users)) {
            cout << "This email already exists. Please enter another email." << endl;
        }
        else {
            temp.UserAccount.email = email;
            users[realUsers].UserAccount.email = email;
            break; // Break out of the loop if the email is new
        }
    }

    string confirm_email;
    while (true) {
        cout << "Confirm your email or press 0 to exit: ";
        cin >> confirm_email;
        if (confirm_email == "0") {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
        if (temp.UserAccount.email != confirm_email) {
            cout << "Emails do not match. Please re-enter your email." << endl;
        }
        else {
            break; // Break out of the loop if the emails match
        }
    }

    cout << "Enter your password or press 0 to exit: ";
    cin >> temp.UserAccount.password;
    if (temp.UserAccount.password == "0") {
        cout << "Exiting sign-up..." << endl;
        return false;
    }

    string confirm_password;
    while (true) {
        cout << "Confirm your password or press 0 to exit: ";
        cin >> confirm_password;
        if (confirm_password == "0") {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
        if (temp.UserAccount.password != confirm_password) {
            cout << "Passwords do not match. Please re-enter your password." << endl;
        }
        else {
            break; // Break out of the loop if the passwords match
        }
    }

    cout << "Enter your balance or press 0 to exit: ";
    cin >> temp.balance;
    if (temp.balance == 0) {
        cout << "Exiting sign-up..." << endl;
        return false;
    }

    while (temp.balance < 50 || temp.balance < 0) {
        if (temp.balance < 0) {
            cout << "Balance cannot be negative!" << endl;
        }
        else if (temp.balance < 50) {
            cout << "Minimum balance is 50. Please enter another balance: ";
        }
        cin >> temp.balance;
        if (temp.balance == 0) {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
    }

    // If all data is entered correctly, proceed to store the user's information
    users[realUsers].UserAccount.password = temp.UserAccount.password;
    users[realUsers].balance = temp.balance;
    UserIdGenerator();
    indexOfUsers = users[realUsers].id;
    users[realUsers].signedUp = true;
    cout << "Signed Up successfully!" << endl;

    IncrementUserNumber();
    DeletScreen();

    return true;
}

bool isAdmin;
void UpdatePersonalInformation();

bool Login() {
    char choice;
    User temp;
    cout << "Enter your Email or "<<left<<setw(20)<<" You can Press ----> 0 to exit: "<<endl;
    cin >> temp.UserAccount.email;
    if (temp.UserAccount.email == "0") {
        cout << "Exiting login..." << endl;
        return false;
    }

    cout << "Enter your Password or press 0 to exit: ";
    cin >> temp.UserAccount.password;
    if (temp.UserAccount.password == "0") {
        cout << "Exiting login..." << endl;
        return false;
    }

    if (temp.UserAccount.email == "admin.com" && temp.UserAccount.password == "1") {
        isAdmin = true;
        cout << "Logged in as admin!" << endl;
        DeletScreen();
        login_status = true;
        return true;
    }

    if (find(temp.UserAccount.email, temp.UserAccount.password, users)) {
        cout << "Logged in successfully! " << endl;
        DeletScreen();
        login_status = true;
        users[indexOfUsers].SubFound = true;
        return true;
    }
    else if (isAdmin) {
        cout << "Welcome Admin!" << endl;
        DeletScreen();
        return true;
    }
    else {
        cout << "This user doesn't exist!" << endl;
        DeletScreen();
        return false;
    }
}
int readrealSub() {
    int count = 0;
    ifstream infile("realsub.txt");

    if (infile.is_open()) {
        infile >> count;
        infile.close();
    }
    else {
        cerr << "Warning: User count file not found. Assuming initial count as 0." << endl;
    }

    return count;
}
int realSub = readrealSub();
void StoreTheDataOfSub() {
    ofstream outfile("datasub.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            // Write the subscription data and prices separately
            outfile << SubTypes[i].subName << " " << SubTypes[i].index << " "
                << " " << SubTypes[i].ValidityDays << " " << SubTypes[i].ridesCount << " ";
            outfile << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open SubData file." << endl;
    }
}
void StoreThePrices() {
    ofstream outfile("price.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            for (int j = 0; j < 4; j++) {
                outfile << SubTypes[i].price[j] << " "; // Access SubTypes[i].price[j]
            }
            outfile << endl; // Add a newline after each set of prices for clarity
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadFromFileThePrices() {
    ifstream infile("price.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            for (int j = 0; j < 4; j++) {
                infile >> SubTypes[i].price[j];
            }

        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadFromFileTheDataOfSub() {
    ifstream infile("datasub.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            // Read the subscription data and prices separately
            infile >> SubTypes[i].subName >> SubTypes[i].index
                >> SubTypes[i].ValidityDays >> SubTypes[i].ridesCount;
           
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open SubData file." << endl;
    }
}

void StoreTheRealSub() {
    ofstream outfile("realsub.txt");

    if (outfile.is_open()) {
        outfile << realSub << endl;
        outfile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void ModifySubscriptionAdmin() {
    int NewValidity = 0;
    int NewRides = 0;
    string NewName;
    char id;

    cout << "Enter the type of the Subscription (S for student / M for public monthly / A for public annual / W for wallet):" << endl;
    cin >> id;

    for (int i = 0; i < realSub; i++) {
        if (id == SubTypes[i].index) {
            // Display subscription details before editing
            cout << "Subscription details before editing:\n";
            cout << left << setw(20) << "Name: " << SubTypes[i].subName << "\n";
            cout << left << setw(20) << "Validity Days: " << SubTypes[i].ValidityDays << " days\n";
            cout << left << setw(20) << "Trips Count: " << SubTypes[i].ridesCount << " trips\n";
            cout << "-----------------------------------------------------------" << endl;

            int choice;
            do {
                cout << "1 ---> Edit name" << endl << "2 ---> Edit Validity Days" << endl << "3 ---> Edit Trips Count" << endl << "4 ---> Exit" << endl; // Added option 4: Exit
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "Enter the new name for the subscription for users:" << endl;
                    cin >> NewName;
                    SubTypes[i].subName = NewName;
                    break;
                case 2:
                    cout << "Enter the new Validity days of subscription:" << endl;
                    cin >> NewValidity;
                    if (!isBalancePositive(NewValidity)) {
                        cout << "Validity days cannot be zero or negative. Do you want to enter a different value? (y/n)" << endl;
                        char response;
                        cin >> response;
                        if (response == 'n' || response == 'N') {
                            break;
                        }
                    }
                    SubTypes[i].ValidityDays = NewValidity;
                    break;
                case 3:
                    cout << "Enter the new Trips of subscription:" << endl;
                    cin >> NewRides;
                    if (!isBalancePositive(NewRides)) {
                        cout << "Trips count cannot be zero or negative. Do you want to enter a different value? (y/n)" << endl;
                        char response;
                        cin >> response;
                        if (response == 'n' || response == 'N') {
                            break;
                        }
                    }
                    SubTypes[i].ridesCount = NewRides;
                    break;
                case 4: // Added option 4: Exit
                    cout << "Exiting..." << endl;
                    return; // Exit the function
                default:
                    cout << "Invalid option. Please enter a valid option.\n";
                    // Clear input buffer
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Updated here
                    break;
                }
            } while (choice != 4); // Repeat until the user chooses to exit

            // Display subscription details after editing if no negative number was entered
            if (choice != 4 && (isBalancePositive(NewValidity) || isBalancePositive(NewRides))) {
                cout << "Subscription details after editing:\n";
                cout << left << setw(20) << "Name: " << SubTypes[i].subName << "\n";
                cout << left << setw(20) << "Validity Days: " << SubTypes[i].ValidityDays << " days\n";
                cout << left << setw(20) << "Trips Count: " << SubTypes[i].ridesCount << " trips\n";
                cout << "-----------------------------------------------------------" << endl;

                cout << "Subscription successfully edited!\n";
            }
            return;
        }
    }
    cout << "Subscription not found!\n";
}

void DeleteSubAdmin() {
    char id;
    bool validInput = false;

    do {
        cout << "Enter the type of the Subscription you want to delete (S for student / M for public monthly / A for public annual / W for wallet):" << endl;
        cin >> id;

        // Check if the entered option is valid
        if (id == 'S' || id == 'M' || id == 'A' || id == 'W') {
            validInput = true;
        }
        else {
            cout << "Invalid option! Please enter a valid option." << endl;
            // Clear input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!validInput);

    bool found = false; // Flag to check if the subscription was found and deleted

    for (int i = 0; i < realSub; i++) {
        if (id == SubTypes[i].index) {
            // Display subscription details before deletion
            cout << "Subscription details before deletion:\n";
            cout << left << setw(20) << "Name: " << SubTypes[i].subName << "\n";
            cout << left << setw(20) << "Validity Days: " << SubTypes[i].ValidityDays << " days\n";
            cout << left << setw(20) << "Trips Count: " << SubTypes[i].ridesCount << " trips\n";
            cout << "-----------------------------------------------------------" << endl;

            // Shift the elements to fill the gap
            for (int j = i; j < realSub - 1; j++) {
                SubTypes[j] = SubTypes[j + 1];
            }
            realSub--; // Decrement the count of subscriptions
            found = true;
            cout << "Subscription successfully deleted!\n";
            return;
        }
    }

    if (!found) {
        cout << "Subscription not found!\n";
    }
}






void ViewSubAdmin() {
    cout << "\nSubscriptions:\n";
    cout << left << setw(30) << "Name" << setw(30) << "Validity Days" << setw(30) << "Trips Count" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    for (int i = 0; i < realSub; i++) {
        cout << left << setw(30) << SubTypes[i].subName
            << setw(30) << SubTypes[i].ValidityDays << " days"
            << setw(30) << SubTypes[i].ridesCount << " trips" << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
    }
}

void AdminMenuSubscriptionManagement() {
    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Modify Subscription\n";
        cout << "2. Delete Subscription\n";
        cout << "3. View Subscriptions\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Please enter a valid option.\n";

            continue; // Skip the rest of the loop and start from the beginning
        }

        switch (choice) {
        case 1:
            ModifySubscriptionAdmin();
            break;
        case 2:
            DeleteSubAdmin();
            break;
        case 3:
            ViewSubAdmin();
            break;
        case 4:
            cout << "Exiting Admin Menu...\n";
            break;
        }
    } while (choice != 4);
}

void GetCurrentTime() {
    cout << __TIME__;

}
void CurrentDateAndTime() {
    // current date and time on the current system
    time_t now = time(0);

    string CurrentDateAndTime = ctime(&now);
    cout << CurrentDateAndTime;
}
void GetCurrentDate() {
    cout << __DATE__;

}
void ViewUsersAccountsAdmin(User users[MaxUser], int realUsers) {
    cout << "Accounts:\n";
    for (int i = 0; i < realUsers; i++) {
        cout << left << setw(20) << "Email: " << users[i].UserAccount.email << "\n";
        cout << left << setw(20) << "Password: " << users[i].UserAccount.password << "\n";
        cout << left << setw(20) << "ID: " << users[i].id << "\n";
        cout << left << setw(20) << "Balance: " << users[i].balance << "\n";
        cout << left << setw(20) << "Subscription: " << users[i].Sub.subName << "\n";
        cout << left << setw(20) << "Stage: " << users[i].Sub.stage << "\n";
        cout << left << setw(20) << "Start Date: " << users[i].Sub.startDate << "\n";
        cout << left << setw(20) << "End Date: " << users[i].Sub.endDate << "\n";

        cout << "-----------------------------------------------------------" << endl;
    }
}
void EditUsersAccountsAdmin(User users[MaxUser], int realUsers) {
    string NewEmail;
    string NewPassword;
    int id;
    ViewUsersAccountsAdmin(users, realUsers);
    cout << "Enter the ID of the user:" << endl;
    cin >> id;
    for (int i = 0; i < realUsers; i++) {

        if (id == users[i].id) {
            int choice;
            cout << "1 ---> Edit email" << endl << "2 ---> Edit Password" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter the new email for the user:" << endl;
                cin >> NewEmail;
                users[i].UserAccount.email = NewEmail;
                break;
            case 2:
                cout << "Enter the new password for the user:" << endl;
                cin >> NewPassword;
                users[i].UserAccount.password = NewPassword;
                break;
            default:
                cout << "Invalid option" << endl;
                break;
            }

        }
    }


}
void DeleteUsersAccountsAdmin() {
    for (int i = 0; i < realUsers; i++) {
        int id;
        cout << "Enter the id of the user you want to delete:" << endl;
        cin >> id;
        if (id == users[i].id) {

            users[i] = users[i + 1];
            DecrementUserNumber(); // Decrement the count of users
            cout << "User account deleted successfully!\n";
            return;


            cout << "User not found!\n";




        }
    }
}
void FareManagement() {
    char choice;
    do {
        char category;
        cout << "Enter 'E' to edit subscription prices or 'C' to edit constant prices: ";
        cin >> category;

        if (category == 'E') { // Editing subscription prices
            char stage, type;
            cout << "\nEnter the stage you want to change its prices (1-4): ";
            cin >> stage;
            cout << "Enter the subscription type (S for Student, W for Waller, M for PublicMonthly, A for PublicAnnual): ";
            cin >> type;
            float newPrice;

            int i = -1; // Initializing i outside the switch statement

            switch (stage) {
            case '1':
            case '2':
            case '3':
            case '4':
            {
                int stageIndex = stage - '1'; // Convert stage character to index (0-based)

                for (int j = 0; j < realSub; j++) {
                    if (type == SubTypes[j].index) {
                        i = j; // Update i if the subscription type is found
                        break;
                    }
                }

                if (i != -1) {
                    cout << "\nThe current price of stage " << stage << " for subscription type " << type << " is: "
                        << SubTypes[i].price[stageIndex] << endl;
                    cout << "Enter the new price for stage " << stage << " and subscription type " << type << ": ";
                    cin >> newPrice;
                    if (newPrice >= 0) { // Validate that price is not negative
                        SubTypes[i].price[stageIndex] = newPrice;
                        cout << "\nPrice updated successfully!" << endl;
                    }
                    else {
                        cout << "\nPrice cannot be negative. Please enter a valid price." << endl;
                    }
                }
                else {
                    cout << "\nSubscription type does not exist!" << endl;
                }
                break;
            }
            default:
                cout << "\nInvalid stage! Please enter a stage between 1 and 4." << endl;
                break;
            }
        }
        else if (category == 'C') { // Editing constant prices
            int stageIndex;
            cout << "\nEnter the stage for which you want to change the constant price (1-4): ";
            cin >> stageIndex;
            if (stageIndex >= 1 && stageIndex <= 4) {
                float newPrice;
                cout << "Enter the new constant price for stage " << stageIndex << ": ";
                cin >> newPrice;
                if (newPrice >= 0) { // Validate that price is not negative
                    constantPrice[stageIndex - 1] = newPrice;
                    cout << "\nConstant price for stage " << stageIndex << " updated successfully!" << endl;
                }
                else {
                    cout << "\nPrice cannot be negative. Please enter a valid price." << endl;
                }
            }
            else {
                cout << "\nInvalid stage! Please enter a stage between 1 and 4." << endl;
            }
        }
        else {
            cout << "\nInvalid category! Please enter 'S' for subscription types or 'C' for constant prices." << endl;
        }

        cout << "\nDo you want to edit another set of prices? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}



string CurrentDate() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Convert to a local time structure
    tm currentTimeStruct = *localtime(&currentTime);

    // Add the specified number of days


    // Normalize the date (adjust month and year if necessary)
    mktime(&currentTimeStruct);
    string DateString = to_string(currentTimeStruct.tm_mday) + "/" + to_string(currentTimeStruct.tm_mon + 1) + "/" + to_string(currentTimeStruct.tm_year + 1900);
    // Return the updated date structure
    return DateString;
}
string addDays() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Convert to a local time structure
    tm currentTimeStruct = *localtime(&currentTime);

    // Add the specified number of days
    currentTimeStruct.tm_mday += users[indexOfUsers].Sub.ValidityDays;

    // Normalize the date (adjust month and year if necessary)
    mktime(&currentTimeStruct);

    string DateString = to_string(currentTimeStruct.tm_mday) + "/" + to_string(currentTimeStruct.tm_mon + 1) + "/" + to_string(currentTimeStruct.tm_year + 1900);
    // Return the updated date structure
    return DateString;
}
void AddMetroStation() {
    int lineNumber, NumberOfStations;
    char option;
    do {
        bool stationAdded = false;
        cout << "Enter the line you want to add a station to: ";
        cin >> lineNumber;
        if (lineNumber >= 1 && lineNumber <= 3) {
            NumberOfStations = lineStations[lineNumber - 1];
            if (NumberOfStations < maxStations) {
                string NewStation;
                cout << "Enter the name of the new station: ";
                cin.ignore();
                getline(cin, NewStation);
                stations[lineNumber - 1][NumberOfStations].name = NewStation;
                stations[lineNumber - 1][NumberOfStations].id = NumberOfStations + 1;
                stations[lineNumber - 1][NumberOfStations].line = lineNumber;
                stations[lineNumber - 1][NumberOfStations].symbol = 'R';
                NumberOfStations++;
                lineStations[lineNumber - 1] = NumberOfStations; // Update the global variable
                stationAdded = true;
            }
            else {
                cout << "Cannot add more stations to this line. Maximum capacity reached.\n";
            }
        }
        else {
            cout << "Invalid line number!\n";
        }

        if (stationAdded) {
            cout << "Station added successfully!\n";
        }
        else {
            cout << "Error adding station!\n";
        }

        cout << "Do you want to add another station? (y/n): ";
        cin >> option;
    } while (option == 'y' || option == 'Y');
}
void ViewMetroStations(int lineNumber = 0) {
    int  NumberOfStations;
    char option;
    do {

        if (lineNumber == 0) {
            cout << "Enter the line number you want to view: " << endl;
            cin >> lineNumber;

        }


        while (lineNumber < 1 || lineNumber>3)
        {
            cout << "Wrong line number, Enter again: \n";
            cin >> lineNumber;

        }

        if (lineNumber >= 1 && lineNumber <= 3) {
            NumberOfStations = lineStations[lineNumber - 1];

            cout << "Stations:\n";
            for (int i = 0; i < NumberOfStations; i++) {
                cout << i + 1 << "->" << stations[lineNumber - 1][i].name << "\n";
            }
        }
        cout << "Do you want to view another line ? (y/n) \n";


        cin >> option;
        if (option == 'y' || option == 'Y')
            lineNumber = 0;

    } while (option == 'y' || option == 'Y');

}
void EditMetroStation() {

    int lineNumber, NumberOfStations, id;
    string NewStation;
    cout << "Enter the line you want to edit from: \n";
    cin >> lineNumber;
    cout << "Enter the number of the station you want to edit: ";
    cin >> id;

    if (lineNumber >= 1 && lineNumber <= 3) {
        NumberOfStations = lineStations[lineNumber - 1];
        bool stationFound = false;
        for (int i = 0; i < NumberOfStations; i++) {
            if (id == stations[lineNumber - 1][i].id) {
                cout << "Enter the new station for the metro:" << endl;
                cin.ignore();
                getline(cin, NewStation);
                stations[lineNumber - 1][i].name = NewStation;
                return;
            }
        }
        if (!stationFound)
            cout << "Station not found!\n";
    }
    else {
        cout << "Invalid line number!\n";
    }

}
void DeleteMetroStation() {
    int lineNumber, NumberOfStations, id;
    cout << "Enter the line you want to delete from: \n";
    cin >> lineNumber;
    cout << "Enter the number of the station you want to delete: ";
    cin >> id;
    if (lineNumber >= 1 && lineNumber <= 3) {
        NumberOfStations = lineStations[lineNumber - 1];
        bool stationFound = false;
        for (int i = 0; i < NumberOfStations; i++) {
            if (id == stations[lineNumber - 1][i].id) {
                // Shift stations after the deleted station one index to the left
                for (int j = i; j < NumberOfStations - 1; j++) {
                    stations[lineNumber - 1][j] = stations[lineNumber - 1][j + 1];
                    // Update the ID of the shifted station
                    stations[lineNumber - 1][j].id = j + 1; // Assuming IDs start from 1
                }
                NumberOfStations--; // Decrement the count of stations
                cout << "Metro station deleted successfully!\n";
                lineStations[lineNumber - 1] = NumberOfStations; // Update the global variable
                stationFound = true;
                break;
            }
        }
        if (stationFound) {
            // Update the global variable for the number of stations
            if (lineNumber == 1)
                lineStations[0] = NumberOfStations;
            else if (lineNumber == 2)
                lineStations[1] = NumberOfStations;
            else if (lineNumber == 3)
                lineStations[2] = NumberOfStations;
        }
        else {
            cout << "Station not found!\n";
        }
    }
    else {
        cout << "Invalid line number!\n";
    }
}
void StoreTheSubscriptionOfUsers() {
    ofstream outfile("subscription.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {

            outfile << users[i].Sub.endDate << " " << users[i].Sub.index << " " << users[i].Sub.ridesCount << " " << users[i].Sub.stage << " " << users[i].Sub.startDate << " " << users[i].Sub.subName << " " << users[i].Sub.ValidityDays << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadTheSubscriptionOfUsers() {
    ifstream infile("subscription.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {

            infile >> users[i].Sub.endDate >> users[i].Sub.index >> users[i].Sub.ridesCount >> users[i].Sub.stage >> users[i].Sub.startDate >> users[i].Sub.subName >> users[i].Sub.ValidityDays >> users[i].walletMoney;
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}





void ReadStationNumbersToFile() {
    ifstream infile("stationNumbers.txt");
    if (infile.is_open()) {
        infile >> lineStations[0] >> lineStations[1] >> lineStations[2];
        infile.close();
    }
    else {
        cerr << "Error: Could not open file for reading." << endl;
    }
}
void StoreStationNumbersToFile() {
    ofstream outfile("stationNumbers.txt");
    if (outfile.is_open()) {
        outfile << lineStations[0] << " " << lineStations[1] << " " << lineStations[2];
        outfile.close();
    }
    else {
        cerr << "Error: Could not open file for writing." << endl;
    }
}

void UserManagementAdmin() {
    char anotherFunction = 'y'; // Flag for continuing admin operations

    while (anotherFunction == 'y' || anotherFunction == 'Y') {
        // Check if there are any users before proceeding
        if (realUsers == 0) {
            cout << "There are no users to manage." << endl;
            break; // Exit the loop if no users
        }

        // Display user accounts
        ViewUsersAccountsAdmin(users, realUsers);

        int choice;
        cout << "Choose what you want to do:" << endl;
        cout << "------------------------------------" << endl;
        cout << "1 = Edit Users Data" << endl;
        cout << "2 = Delete Users" << endl;
        cout << "3 = Exit" << endl; // Add exit option
        cin >> choice;

        switch (choice) {
        case 1:
            EditUsersAccountsAdmin(users, realUsers);
            DeletScreen();
            break;
        case 2:
            DeleteUsersAccountsAdmin();
            DeletScreen();
            break;
        case 3:
            anotherFunction = 'n'; // Set flag to exit
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
        }

        // Prompt to continue with admin operations
        if (realUsers > 0 && anotherFunction != 'n') {
            cout << "Do you want to perform another operation (y/n)? ";
            cin >> anotherFunction;
        }
    }
}
void StoreTheDataOfStations() {
    ofstream outfile("stations.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < lineStations[0]; i++) {
            outfile << stations[0][i].line << " " << stations[0][i].name << " " << stations[0][i].symbol << endl;
        }
        for (int i = 0; i < lineStations[1]; i++) {
            outfile << stations[1][i].line << " " << stations[1][i].name << " " << stations[1][i].symbol << endl;
        }

        for (int i = 0; i < lineStations[2]; i++) {
            outfile << stations[2][i].line << " " << stations[2][i].name << " " << stations[2][i].symbol << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open stations file." << endl;
    }
}
void ReadFromFileTheDataOfStations() {
    ifstream infile("stations.txt");

    if (infile.is_open()) {
        for (int i = 0; i < lineStations[0]; i++) {
            infile >> stations[0][i].line;
            stations[0][i].id = i + 1;
            infile >> stations[0][i].name;
            infile >> stations[0][i].symbol;
        }
        for (int i = 0; i < lineStations[1]; i++) {
            infile >> stations[1][i].line;
            if (stations[1][i].line == 3)
            {
                break;
            }
            stations[1][i].id = i + 1;
            infile >> stations[1][i].name;
            infile >> stations[1][i].symbol;
        }
        for (int i = 0; i < lineStations[2]; i++) {
            infile >> stations[2][i].line;
            stations[2][i].id = i + 1;
            infile >> stations[2][i].name;

            infile >> stations[2][i].symbol;
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open stations file." << endl;
    }
}
void StationsManagementAdmin() {
    int choice;
    char anotherFunction;


    do {

        ViewMetroStations();
        cout << "Choose what you want to do:" << endl;
        cout << "------------------------------------" << endl;
        cout << "1 = Add Stations" << endl;
        cout << "2 = Edit Stations" << endl;
        cout << "3 = Delete Stations" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            AddMetroStation();
            DeletScreen();
            break;


        case 2:
            EditMetroStation();
            DeletScreen();
            break;
        case 3:
            DeleteMetroStation();
            DeletScreen();
            break;
        }
        cout << "Do you want another function ?(y/n)";

        cin >> anotherFunction;
    } while (anotherFunction == 'y' || anotherFunction == 'Y');






}
void viewUserRideHistory() {
    char choice;
    do {
        if (users[indexOfUsers].Sub.ridesCount > 0) {
            cout << users[indexOfUsers].UserAccount.username << " Rides:" << endl;
            for (int i = users[indexOfUsers].Sub.ridesCount - 1; i >= 0; i--) {
                cout << "Ride " << setw(10) << i + 1 << endl;
                cout << "------------------------------------------\n";
                cout << left << setw(15) << "Date:" << users[indexOfUsers].ridedetails[i].rideDate << endl;
                cout << left << setw(15) << "Ride ID:" << users[indexOfUsers].ridedetails[i].rideID << endl;
                cout << left << setw(15) << "From station:" << users[indexOfUsers].ridedetails[i].checkInStation << endl;
                cout << left << setw(15) << "To station:" << users[indexOfUsers].ridedetails[i].checkOutStation << endl;
               // if (buyTicket || users[indexOfUsers].Sub.index == 'W') {
                    cout << left << setw(15) << "Cost:" << users[indexOfUsers].ridedetails[i].cost << endl;
                //}
                cout << "------------------------------------------\n";
            }
        }
        else {
            cout << "No rides booked." << endl;
        }

        cout << "Do you want to return to the main menu? (y/n): ";
        cin >> choice;
    } while (choice != 'y' && choice != 'Y');
}

void viewAllRides() {
    char choice;
    do {
        for (int i = realUsers - 1; i >= 0; i--) {
            cout << users[i].UserAccount.email << " Rides:" << endl;
            cout << "-------------------------------------\n";
            for (int j = users[i].Sub.ridesCount - 1; j >= 0; j--) {
                cout << "Ride " << j + 1 << ":" << endl;
                cout << "Date: " << users[i].ridedetails[j].rideDate << endl;
                cout << "Ride ID: " << users[i].ridedetails[j].rideID << endl;
                cout << "From station: " << users[i].ridedetails[j].checkInStation << endl;
                cout << "To station: " << users[i].ridedetails[j].checkOutStation << endl;
                cout << "Cost: " << users[i].ridedetails[j].cost << endl;
                cout << "-------------------------------------\n";
            }
        }

        cout << "Do you want to return to the main menu? (y/n): ";
        cin >> choice;
    } while (choice != 'y' && choice != 'Y');
}
void subtype()
{
    int choice;


    for (int i = 0; i < realSub; i++) {
        cout << i + 1 << " " << SubTypes[i].subName << endl;
    }

    bool c;
    do
    {
        c = false;
        cin >> choice;
        for (int j = 1; j <= realSub; j++) {
            if (choice == j) {

                users[indexOfUsers].Sub.index = SubTypes[j - 1].index;
                users[indexOfUsers].Sub.subName = SubTypes[j - 1].subName;
                users[indexOfUsers].Sub.ValidityDays = SubTypes[j - 1].ValidityDays;
               
                c = true;
            }




        }
        if (!c) {
            cout << "invaled choice re enter your type of subscrbtion again\n";
        }


    } while (c == false);

}
int buyCostStages(int& stage) {
    char ch;
    char subIndex = users[indexOfUsers].Sub.index;

    // Find the index of the subscription type
    int i;
    for (i = 0; i < realSub; i++) {
        if (SubTypes[i].index == subIndex) {
            break;
        }
    }



    cout << "You must pay " << SubTypes[i].price[stage - 1] << endl;
    cout << "Press 'y' to continue payment: " << endl;
    
    // While loop for user confirmation (y or Y)
    while (true) {
        cin >> ch;

        if (ch == 'y' || ch == 'Y') {
            DeletScreen();
            return SubTypes[i].price[stage - 1];
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'Y' to confirm payment: ";
        }
    }
}
void purchasesubscribtion(int& walletprice, int& stage, float& cost) {
    subtype(); // Assuming this is a valid function call

    char subscriptionType = users[indexOfUsers].Sub.index;

    if (subscriptionType == 'S' || subscriptionType == 'M' || subscriptionType == 'A') {
        int i;
        for (i = 0; i < realSub; i++) {
            if (SubTypes[i].index == subscriptionType) {
                break;
            }
        }

        users[indexOfUsers].Sub.ValidityDays = SubTypes[i].ValidityDays;
        users[indexOfUsers].Sub.fullRides = SubTypes[i].ridesCount;
        cout << "Which stage do you want?" << endl;
        cout << "1: 2 to 9 stations, Price: " << SubTypes[i].price[0] << endl;
        cout << "2: 10 to 16 stations, Price: " << SubTypes[i].price[1] << endl;
        cout << "3: 17 to 23 stations, Price: " << SubTypes[i].price[2] << endl;
        cout << "4: More than 23 stations, Price: " << SubTypes[i].price[3] << endl;
        cin >> stage;

        cost = buyCostStages(stage);

        if (cost > users[indexOfUsers].balance) {
            cout << "Add balance because the balance is not enough." << endl;
            int add;
            cin >> add;

            while ((users[indexOfUsers].balance + add) < cost) {
                cout << "Added balance is still not enough. Please add more balance: ";
                int moreToAdd;
                cin >> moreToAdd;
                add += moreToAdd;
            }

            users[indexOfUsers].balance += add;
        }

       
        else {
            users[indexOfUsers].balance -= cost;
            users[indexOfUsers].Sub.ridesCount = 0;
            users[indexOfUsers].Sub.startDate = CurrentDate();
            users[indexOfUsers].Sub.endDate = addDays();
            users[indexOfUsers].Sub.stage = stage;
        }

       
      
    }
    else {
        cout << "You must have in your Wallet Money multiple of 10 and less than 400." << endl;
        cout << "Select the money at wallet: ";

        do {
            cin >> walletprice;
            if (walletprice % 10 != 0 || walletprice > 400 || walletprice <= 0) {
                cout << "Invalid amount. Please enter a valid amount (multiple of 10, less than 400, and greater than 0): ";
            }
            else {
                break;
            }
        } while (true);

        users[indexOfUsers].walletMoney = walletprice;
        users[indexOfUsers].balance -= walletprice;
    }

    users[indexOfUsers].Sub.startDate = CurrentDate(); // Assuming CurrentDate() is a valid function returning a string
    users[indexOfUsers].Sub.endDate = addDays(); // Assuming addDays() is a valid function returning a string
    users[indexOfUsers].SubFound = true;
}


void inputDeparture(departure& userDeparture) {

    cout << "Enter the metro line number you are going from: \n" << "Enter 1 or 2 or 3 \n";
    cin >> userDeparture.line;
    while (userDeparture.line != 1 && userDeparture.line != 2 && userDeparture.line != 3) {
        cout << "you entered a wrong line number \n" << "Enter the metro line again: \n";
        cout << "Enter 1 or 2 or 3" << endl;
        cin >> userDeparture.line;
    }
  

    cout << "Enter your departure station (ID):\n " << endl;
    cin >> userDeparture.id;

}

string GetDepartureName(departure& userDeparture) {
    int NumberOfStations;
    
        if (userDeparture.line == 1)
            NumberOfStations = lineStations[0]; //35
        else if (userDeparture.line == 2)
            NumberOfStations = lineStations[1]; //20
        else if (userDeparture.line == 3)
            NumberOfStations = lineStations[2];//29
  

        for (int i = 0; i < NumberOfStations; i++) {
            if (userDeparture.id == stations[userDeparture.line - 1][i].id)
            {
               
                return stations[userDeparture.line - 1][i].name;
            }
        }
       
  

}
string GetDestinationName(destination& userDestination) {
    int NumberOfStations;

    if (userDestination.line == 1)
        NumberOfStations = lineStations[0]; //35
    else if (userDestination.line == 2)
        NumberOfStations = lineStations[1]; //20
    else if (userDestination.line == 3)
        NumberOfStations = lineStations[2];//29


    for (int i = 0; i < NumberOfStations; i++) {
        if (userDestination.id == stations[userDestination.line - 1][i].id)
        {

            return stations[userDestination.line - 1][i].name;
        }
    }



}

void inputDestination(destination& userDestination) {
    cout << "Enter the metro line number you are heading: \n" << "Enter 1 or 2 or 3 \n";
    cin >> userDestination.line;
    while (userDestination.line != 1 && userDestination.line != 2 && userDestination.line != 3) {
        cout << "you entered a wrong line number \n" << "Enter the metro line again: \n";
        cout << "Enter 1 or 2 or 3" << endl;
        cin >> userDestination.line;
    }
   
    cout << "Enter your destination station (ID): \n " << endl;
    cin >> userDestination.id;
}
void GetTransitionalStationsId() {

    // shohada = 0,1 attaba = 2,3 , nasser 4,5 

    for (int i = 0; i < lineStations[0]; i++) {
        if (stations[0][i].symbol == 'S')
        {
            transitionStations[0] = i + 1;
        }
        if (stations[0][i].symbol == 'N')
        {
            transitionStations[4] = i + 1;
        }
    }
    for (int i = 0; i < lineStations[1]; i++) {
        if (stations[1][i].symbol == 'S')
        {
            transitionStations[1] = i + 1;
        }
        if (stations[1][i].symbol == 'A')
        {
            transitionStations[2] = i + 1;
        }
    }

    for (int i = 0; i < lineStations[2]; i++) {
        if (stations[2][i].symbol == 'A')
        {
            transitionStations[3] = i + 1;
        }
        if (stations[2][i].symbol == 'N')
        {
            transitionStations[5] = i + 1;
        }
    }
}


void InitializeRide(departure& userDeparture, destination& userDestination) {

    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].rideID = to_string(users[indexOfUsers].id) + to_string(users[indexOfUsers].Sub.ridesCount);
   users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].checkInStation = GetDepartureName(userDeparture);
    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].checkOutStation = GetDestinationName(userDestination);
    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].rideDate = CurrentDate();
    users[indexOfUsers].Sub.ridesCount++;
   
}

bool purchaseTicket(int ticketPriceIndex) {
    if ((users[indexOfUsers].balance - constantPrice[ticketPriceIndex]) < 0) {
        cout << "You Don't have enough balance!" << endl;
        return false;
    }
    else {



        return true;
    }
}
int CalulateNumberOfStations(departure& userDeparture, destination& userDestination);
int reEnterTheRide(departure& userDeparture, destination& userDestination, int& NumberOfStations) {
    inputDeparture(userDeparture);
    inputDestination(userDestination);
    NumberOfStations = 0;
    return CalulateNumberOfStations(userDeparture, userDestination);
}
bool canInitializeTheRide;
void walletDeduction(int NumberOfStations) {
    if (users[indexOfUsers].Sub.index == 'W') {
        int priceToDeduct = 0;

        if (1 < NumberOfStations && NumberOfStations < 10) {
            priceToDeduct = constantPrice[0];
        }
        else if (9 < NumberOfStations && NumberOfStations < 17) {
            priceToDeduct = constantPrice[1];
        }
        else if (16 < NumberOfStations && NumberOfStations < 24) {
            priceToDeduct = constantPrice[2];
        }
        else {
            priceToDeduct = constantPrice[3];
        }

        // Check if the price to deduct exceeds the wallet balance
        if (users[indexOfUsers].walletMoney < priceToDeduct) {
            cout << "Insufficient funds in the wallet please go and add money to the wallet in manage subscription!." << endl;
            canInitializeTheRide = false;
            return; // Exit the function if balance is insufficient
        }
        else {
            users[indexOfUsers].walletMoney -= priceToDeduct;
            canInitializeTheRide = true;
            // Store the cost in the ridedetails structure
            // Assuming ridesCount is the index to store the next ride
            
            
           
            // Increment the ridesCount for the next ride

            cout << "The remaining money in the wallet: " << users[indexOfUsers].walletMoney << endl;
        }

        // Deduct the price from the wallet balance
       
    }
}

int CalulateNumberOfStations(departure& userDeparture, destination& userDestination) {
    int NumberOfStations;

    // Your existing logic to calculate NumberOfStations...

    //cout << transitionStations[0] << ' ' << ' ' << transitionStations[1] << ' ' << transitionStations[2] << ' ' << transitionStations[3] << ' ' << transitionStations[4] << ' ' << transitionStations[5] << endl;
    if (userDeparture.line == userDestination.line)
        NumberOfStations = abs(userDestination.id - userDeparture.id) + 1;
    else if (userDeparture.line == 1 && userDestination.line == 2)
        NumberOfStations = abs(userDeparture.id - transitionStations[0]) + abs(userDestination.id - transitionStations[1]) + 1;
    // int a [10] { shohada line one , shohada line 2 , nasser line one , nasser line 3}
    else if (userDeparture.line == 1 && userDestination.line == 3) {
        if (userDeparture.id <= transitionStations[0] && userDestination.id >= transitionStations[3])
            NumberOfStations = abs(userDeparture.id - transitionStations[4]) + abs(userDestination.id - transitionStations[5]) - 1;
        else
            NumberOfStations = abs(userDeparture.id - transitionStations[4]) + abs(userDestination.id - transitionStations[5]) + 1;
    }
    else if (userDeparture.line == 2 && userDestination.line == 1)
        NumberOfStations = abs(userDeparture.id - transitionStations[1]) + abs(userDestination.id - transitionStations[0]) + 1;

    else if (userDeparture.line == 2 && userDestination.line == 3) {
        if (userDeparture.id >= transitionStations[3] && userDestination.id <= transitionStations[5])
            NumberOfStations = abs(userDeparture.id - transitionStations[2]) + abs(userDestination.id - transitionStations[3]) - 1;

        else
            NumberOfStations = abs(userDeparture.id - transitionStations[2]) + abs(userDestination.id - transitionStations[3]) + 1;
    }
    else if (userDeparture.line == 3 && userDestination.line == 1) {
        if (userDeparture.id >= transitionStations[3] && userDestination.id <= transitionStations[0])
            NumberOfStations = abs(userDeparture.id - transitionStations[5]) + abs(userDestination.id - transitionStations[4]) - 1;
        else
            NumberOfStations = abs(userDeparture.id - transitionStations[5]) + abs(userDestination.id - transitionStations[4]) + 1;
    }

    else if (userDeparture.line == 3 && userDestination.line == 2) {
        if (userDeparture.id <= transitionStations[5] && userDestination.id >= transitionStations[3])
            NumberOfStations = abs(userDeparture.id - transitionStations[3]) + abs(userDestination.id - transitionStations[2]) - 1;
        else
            NumberOfStations = abs(userDeparture.id - transitionStations[5]) + abs(userDestination.id - transitionStations[4]) + 1;
    }
    if (users[indexOfUsers].Sub.index == 'W') {
        walletDeduction(NumberOfStations);
    }
    char option;    // to choose either to choose again or to use balance
    switch (users[indexOfUsers].Sub.stage) {
    case 1:
        if (NumberOfStations > 9 && NumberOfStations <= 16) {
            cout << "Number of stations is more than the stage you have chosen (stage 1)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
               if (purchaseTicket(1)) {
                   users[indexOfUsers].balance -= constantPrice[1];
                   users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[1];
                   
                   buyTicket = true;
                }
               
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture(userDeparture);
                inputDestination(userDestination);
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
                return NumberOfStations;
            }
        }
        else if (NumberOfStations > 16 && NumberOfStations <= 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 1)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(2)) {
                    users[indexOfUsers].balance -= constantPrice[2];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[2];
                
                    buyTicket = true;
                }
               
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture(userDeparture);
                inputDestination(userDestination);
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
                return NumberOfStations;
            }
        }
        else if (NumberOfStations > 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 1)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(3)) {
                    users[indexOfUsers].balance -= constantPrice[3];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[3];
       
                    buyTicket = true;
                }
              
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture(userDeparture);
                inputDestination(userDestination);
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
                return NumberOfStations;
            }
        }
        break;
    case 2:
        if (NumberOfStations > 16 && NumberOfStations <= 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 2)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(2)) {
                    users[indexOfUsers].balance -= constantPrice[2];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[2];
             
                    buyTicket = true;
                }
               
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture(userDeparture);
                inputDestination(userDestination);
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
                return NumberOfStations;
            }
        }
        else if (NumberOfStations > 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 2)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(3)) {
                    users[indexOfUsers].balance -= constantPrice[3];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[3];
       
                    buyTicket = true;
                }
                
                
                
                
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture(userDeparture);
                inputDestination(userDestination);
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
                return NumberOfStations;
            }
        }
        break;
    case 3:
        if (NumberOfStations > 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 3)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(3)) {
                    
                    users[indexOfUsers].balance -= constantPrice[3];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[3];
            
                    buyTicket = true;
                }
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture(userDeparture);
                inputDestination(userDestination);
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
                return NumberOfStations;
            }
        }
        break;
    }
   

 
   
    return NumberOfStations;
}


int checkInAndCheckOut(departure& userDeparture, destination& userDestination) {
    
    if ((users[indexOfUsers].Sub.fullRides-users[indexOfUsers].Sub.ridesCount <= 0 || users[indexOfUsers].Sub.ValidityDays <= 0 ) && (users[indexOfUsers].Sub.index=='M'|| users[indexOfUsers].Sub.index == 'A'||users[indexOfUsers].Sub.index == 'S')) {
        cout << "Your subscription is invalid. Please renew your subscription." << endl;
        return 0; // Return 0 to indicate failure
    }
    GetTransitionalStationsId();
    ViewMetroStations();
    inputDeparture(userDeparture);
    inputDestination(userDestination);
    int NumberOfStations = CalulateNumberOfStations(userDeparture, userDestination);
    if (NumberOfStations != 0) {
        cout << NumberOfStations << " Stations";
       
    }
    else
        cout << "Not enough money! \n";
    if (users[indexOfUsers].Sub.index=='W' &&!canInitializeTheRide){

    }
    else {
        InitializeRide(userDeparture, userDestination);
    }
    
    return NumberOfStations;
}




void viewDetails(int walletprice, int valid, int NumberOfStations) {
    cout << "The number of rides: " << users[indexOfUsers].Sub.ridesCount << endl;
    cout << "The type of Subscription: " << users[indexOfUsers].Sub.subName << endl;
    if (users[indexOfUsers].Sub.index == 'W') {
        cout << "The remaining money in the Wallet is " << users[indexOfUsers].walletMoney << endl;

    }
    else if (users[indexOfUsers].Sub.index == 'A' || users[indexOfUsers].Sub.index == 'M' || users[indexOfUsers].Sub.index == 'S'){
    cout << "The stage of Subscription: " << users[indexOfUsers].Sub.stage << endl;
    cout << "The start of Subscription: " << users[indexOfUsers].Sub.startDate << endl;
    cout << "The End of Subscription: " << users[indexOfUsers].Sub.endDate << endl;
    cout << "The days valid of Subscription: " << users[indexOfUsers].Sub.ValidityDays << endl;
    cout << "The remaining rides: " << users[indexOfUsers].Sub.fullRides - users[indexOfUsers].Sub.ridesCount << endl;
}
}
bool checkTheSub(int walletprice)
{
    char subIndex = users[indexOfUsers].Sub.index;
    for (int i = 0; i < realSub; i++) {
        if (SubTypes[i].index == subIndex) {
            if (SubTypes[i].ridesCount - users[indexOfUsers].Sub.ridesCount == 0) {
                cout << "Your subscription is not valid" << endl;
                return true;
            }
            break;
        }
    }

    if (subIndex == 'W') {
        if (walletprice < 6) {
            cout << "Your subscription is not valid" << endl;
            return true;
        }
    }
    else if (CurrentDate() == users[indexOfUsers].Sub.endDate) {
        return true;
    }

    return false;
}
void ManageSubscription(int& walletprice, int valid, int NumberOfStations, float& cost, int& stage) {
    int q;
    viewDetails(users[indexOfUsers].balance, valid, NumberOfStations);

    cout << "Do you want to upgrade or renew subscription?" << endl;
    cout << "1: Renew" << endl;
    cout << "2: Upgrade" << endl;
    cout << "3: Exit Manage Subscription" << endl;
    cout << "Choose: ";
    cin >> q;

    while (q != 1 && q != 2 && q != 3) {
        cout << "Invalid choice. Please choose again: ";
        cin >> q;
    }

    if (q == 1) {
        bool indexFound = false;
        for (int i = 0; i < realSub; i++) {
            if (users[indexOfUsers].Sub.index == SubTypes[i].index) {
                indexFound = true;
                break;
            }
        }

        if (((users[indexOfUsers].Sub.index == 'S') || (users[indexOfUsers].Sub.index == 'M') || (users[indexOfUsers].Sub.index == 'A')) && indexFound) {
            do {
                if (cost <= users[indexOfUsers].balance) {
                    users[indexOfUsers].balance -= cost;
                    users[indexOfUsers].Sub.ridesCount = 0; // Reset rides count
                    users[indexOfUsers].Sub.startDate = CurrentDate();
                    users[indexOfUsers].Sub.endDate = addDays();
                    cout << users[indexOfUsers].Sub.ridesCount;
                }
                else {
                    cout << "Add balance because the balance is not enough" << endl;
                    int add;
                    cin >> add;

                    while ((users[indexOfUsers].balance + add) < cost) {
                        cout << "Added balance is still not enough. Please add more balance: ";
                        int moreToAdd;
                        cin >> moreToAdd;
                        add += moreToAdd;
                    }

                    users[indexOfUsers].balance += add;
                    users[indexOfUsers].balance -= cost;
                    users[indexOfUsers].Sub.ridesCount = 0; // Reset rides count
                    users[indexOfUsers].Sub.startDate = CurrentDate();
                    users[indexOfUsers].Sub.endDate = addDays();
                }
            } while (cost > users[indexOfUsers].balance);
        }
        else if (users[indexOfUsers].Sub.index == 'W' && indexFound) {
            // Handling wallet subscription
            users[indexOfUsers].Sub.ridesCount = 0; // Reset rides count
            cout << "You must have in your Wallet Money multiple of 10 and less than 400." << endl;

            int walletprice;
            do {
                cout << "Enter the money to add to the wallet: ";
                cin >> walletprice;

                if (walletprice <= 0) {
                    cout << "Invalid amount. Please enter a positive value." << endl;
                }
                else if (walletprice % 10 != 0 || walletprice > 400) {
                    cout << "Entered money must be a multiple of ten and less than 400." << endl;
                }
            } while (walletprice <= 0 || walletprice % 10 != 0 || walletprice > 400);

            while (users[indexOfUsers].balance < walletprice) {
                cout << "The entered wallet price exceeds your balance." << endl;
                cout << "Do you want to update your profile to add more balance? (y/n): ";
                char response;
                cin >> response;

                if (response == 'y' || response == 'Y') {
                    // Call updateProfile function here
                    UpdatePersonalInformation();
                    cout << "Profile updated successfully." << endl;
                    break;
                }
                else if (response == 'n' || response == 'N') {
                    // Return to the beginning of the loop to ask for wallet price again
                    cout << "Please enter another wallet price: ";
                    cin >> walletprice;
                }
                else {
                    // Invalid input, ask the user to enter again
                    cout << "Invalid choice. Please enter 'y' for yes or 'n' for no." << endl;
                }
            }

            users[indexOfUsers].walletMoney += walletprice;
            users[indexOfUsers].balance -= walletprice; // Deduct wallet price from balance
        }
        else {
            cout << "Your old Subscription is not found. You can go to upgrade!" << endl;
        }
    }
    else if (q == 2) {
        purchasesubscribtion(walletprice, stage, cost);
        users[indexOfUsers].Sub.ridesCount = 0;
    }
    else if (q == 3) {
        return;
    }
}







void LogOut();
void AdminMainMenu() {
    char choice;
    while (true) {
        int next;
        cout << "Choose what you want to do:" << endl;
        cout << "------------------------------------" << endl;
        cout << "1 = User Management" << endl;
        cout << "2 = Station Managemnt" << endl;
        cout << "3 = Fare Management" << endl;
        cout << "4 = View User Ride History" << endl;
        cout << "5 = Subscription Management" << endl; // New option
        cout << "6 = Log Out" << endl;

        cin >> next;
        if (next == 1) {
            DeletScreen();
            UserManagementAdmin();
            DeletScreen();
        }
        else if (next == 2) {
            DeletScreen();
            StationsManagementAdmin();
            DeletScreen();
        }
        else if (next == 3) {
            DeletScreen();
            FareManagement();
            DeletScreen();
        }
        else if (next == 4) {
            DeletScreen();
            viewAllRides();
            DeletScreen();
        }
        else if (next == 5) { // New option
            DeletScreen();
            AdminMenuSubscriptionManagement();
            DeletScreen();
        }
        else if (next == 6) {
            DeletScreen();
            LogOut();
            isAdmin = false;
            DeletScreen();
            break;
        }
        else {
            cout << "Invalid option" << endl;
        }
    }
}
void UpdatePersonalInformation() {
    int choose;
    char complete;

    do {
        cout << "What do you want to change?" << endl;
        cout << "1: Name " << endl;
        cout << "2: Password " << endl;
        cout << "3: Email " << endl;
        cout << "4: Balance" << endl;
        cout << "5: Exit" << endl; // Added option 5: Exit
        cout << "Choose: " << endl;
        cin >> choose;

        while (choose > 5 || choose < 1) { // Adjusted the upper limit to include option 5
            cout << "Sorry, please repeat your choice:" << endl;
            cin >> choose;
        }

        if (choose == 1) {
            cout << "Change your name" << endl;
            cin.ignore(); // Ignore the newline character left in the buffer
            getline(cin, users[indexOfUsers].UserAccount.username);
        }
        else if (choose == 2) {
            cout << "Change your password" << endl;
            cin.ignore(); // Ignore the newline character left in the buffer
            getline(cin, users[indexOfUsers].UserAccount.password);
        }
        else if (choose == 3) {
            cout << "Change your email" << endl;
            cin.ignore(); // Ignore the newline character left in the buffer
            getline(cin, users[indexOfUsers].UserAccount.email);
        }
        else if (choose == 4) {
            cout << "Change your balance" << endl;
            do {
                cin >> users[indexOfUsers].balance;
                if (!isBalancePositive(users[indexOfUsers].balance)) {
                    cout << "Balance cannot be zero or negative. Please enter a valid balance:" << endl;
                }
            } while (!isBalancePositive(users[indexOfUsers].balance));
        }
        else if (choose == 5) { // Added option 5: Exit
            cout << "Exiting..." << endl;
            break; // Exit the loop
        }

        cout << "Do you want to change anything else? (y/n)" << endl;
        cin >> complete;
    } while (complete == 'y' || complete == 'Y');
}


void drawHeader() {
    cout << setw(70) << "----------------------" << endl;
    cout << setw(70) << "|     MetroMate      |" << endl;
    cout << setw(70) << "----------------------" << endl;
    cout << string(120, '-') << endl << endl;

}
void userMenu(departure& userDeparture, destination& userDestination)

{
    drawHeader();
    float cost=0;
    int valid = 0;
    int stage; // sub stage
    // when the user to do any thing else  
    int next = 0;
    int walletprice; // when the sub is wallet 
    if (users[indexOfUsers].SubFound == false)
    {
        purchasesubscribtion(walletprice, stage, cost);
    }
    while (true) {
        cout << "Hello " << users[indexOfUsers].UserAccount.email << endl;
        cout << "Your Balance:" << users[indexOfUsers].balance << endl;
        if (users[indexOfUsers].Sub.index=='W') {
            cout << "Wallet Money " << users[indexOfUsers].walletMoney << endl;
       }
        cout << "Choose: " << endl;
        cout << "-------------------------------" << endl;
        cout << "1: Add Ride " << endl;
        cout << "2: Manage Subscription" << endl;
        cout << "3: View Ride History" << endl;
        cout << "4: Update Personal Information" << endl;
        cout << "5: Log Out" << endl;
        cin >> next;

        if (next == 1) {
            DeletScreen();
            NumberOfStations = checkInAndCheckOut(userDeparture, userDestination);
            DeletScreen();
        }
        else if (next == 2) {
            DeletScreen();
            ManageSubscription(walletprice, valid, NumberOfStations, cost, stage);
            DeletScreen();
        }
        else if (next == 3) {
            DeletScreen();

            viewUserRideHistory();
            DeletScreen();
        }
        else if (next == 4) {
            DeletScreen();
            UpdatePersonalInformation();
            DeletScreen();
        }
        else if (next == 5) {
            DeletScreen();
            LogOut();
            DeletScreen();
            break; // Break out of the loop when user chooses to log out
        }
        else {
            cout << "Invalid choice. Please choose again." << endl;
        }
    }
}
int close;
void Store();
void MainMenu() {
    int accountExist;

    do {
        cout << "1. Log In\n";
        cout << "2. Sign Up\n";
        cout << "3. Close the program\n";
        cout << "Enter your choice: ";
        cin >> accountExist;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the input buffer
            continue; // Skip to the next iteration
        }
        switch (accountExist) {
        case 1:
            if (Login()) {
                if (isAdmin)
                    AdminMainMenu();
                else
                    userMenu(userDeparture, userDestination);
            }
            break; // Added break statement

        case 2:
            if (SignUp()) {


                userMenu(userDeparture, userDestination);
            }
            break; // Added break statement

        case 3:
            cout << "See you later!" << endl;
            DeletScreen();
            Store();
            exit(0);
            break; // Added break statement

        default:
            cout << "Invalid choice\n";
            break;
        }


    } while (accountExist != 1 || accountExist != 2 || accountExist != 3);
}

void Read() {
    readrealSub();
    ReadFromFileTheDataOfSub();
    ReadFromFileThePrices();
    readUserCount();
    ReadFromFileTheDataOfUsers();
    ReadTheNumberOfRides();
    ReadFromFileTheDataOfRides();
    ReadStationNumbersToFile();
    ReadFromFileTheDataOfStations();
    ReadTheSubscriptionOfUsers();
    


}

int main()
{

    Read();
    MainMenu();
    Store();


}
void Store() {
   
    StoreTheDataOfUsers();
    StoreTheNumberOfUsers();
    StoreTheNumberOfRides();
    StoreStationNumbersToFile();
    StoreTheDataOfStations();
    StoreTheDataOfRides();
    StoreThePrices();
    StoreTheSubscriptionOfUsers();
    StoreTheRealSub();
    StoreTheDataOfSub();


}
void LogOut() {
    if (login_status) {
        cout << "Are you sure you want to logout?(y/n)";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "Logged out successfully." << endl;
            isAdmin = false;
            DeletScreen();
            MainMenu();
        }

    }

}



