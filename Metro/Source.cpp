#include <iostream>
#include <ctime>
using namespace std;
const int MaxUsers = 100;
const int MaxSub = 100;
int numUsers = 2;
int numSub = 2;
struct Account {
	string email;
	string password;
};
struct Subscription {
	string subName;
	int ValidityDays;
	float SubPrice;
	int index;
};
struct User {
	int id;
	Account UserAccount;
	float Balance;
	Subscription Sub;

};

Subscription UsersSubscriptionTypes[MaxSub];
User users[MaxUsers];
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
void ViewUsersAccounts(User users[MaxUsers], int numUsers) {
	cout << "Accounts:\n";
	for (int i = 0; i < numUsers; i++) {
		cout << "Email: " << users[i].UserAccount.email << "\n";
	}
}
void EditUsersAccounts(User users[MaxUsers], int numUsers, int id) {
	string NewEmail;
	for (int i = 0; i < numUsers;i++) {
		if (id == users[i].id) {
			cout << "Enter the new email for the user:" << endl;
			cin >> NewEmail;
			users[i].UserAccount.email = NewEmail;
			return;
		}
	}
	cout << "User Not Found";
	
}
void DeleteUsersAccounts(User users[MaxUsers], int &numUsers, int id) {
	for (int i = 0; i < numUsers; i++) {
		if (id == users[i].id) {

			users[i] = users[i + 1];
			numUsers = numUsers - 1; // Decrement the count of users
			cout << "User account deleted successfully!\n";
			return;


			cout << "User not found!\n";




		}
	}
}
void CreateNewPlan(Subscription UserSubscriptionTypes[], int& numSub) {
	string newName;
	int newValidityDays;
	float newPrice;
	int NewIndex;
	bool IndexExists = false;

	cin >> newName;
	cin >> newValidityDays;
	cin >> newPrice;
	cin >> NewIndex;

	if (numSub <= 100) {
		UserSubscriptionTypes[numSub].subName = newName;
		UserSubscriptionTypes[numSub].ValidityDays = newValidityDays;
		UserSubscriptionTypes[numSub].SubPrice = newPrice;

		// Check for existing index throughout all elements
		for (int i = 0; i < numSub; i++) {
			if (UserSubscriptionTypes[i].index == NewIndex) {
				IndexExists = true;
				break;
			}
		}

		while (IndexExists) {
			cout << "Subscription index already exists. Please enter a new index: ";
			cin >> NewIndex;

			IndexExists = false;
			for (int i = 0; i < numSub; i++) {
				if (UserSubscriptionTypes[i].index == NewIndex) {
					IndexExists = true;
					break;
				}
			}
		}

		UserSubscriptionTypes[numSub].index = NewIndex;
		numSub++;
	}
	else {
		cout << "Maximum number of subscription plans reached.\n";
	}
}
void ModifySubscriptionAdmin(Subscription UsersSubscriptionTypes[],int index,int numSubscriptions) {
	string newName;
	int newValidityDays;
	float newPrice;
	int NewIndex;
	bool IndexExists;
	cin >> newName;
	cin >> newValidityDays;
	cin >> newPrice;
	cin >> NewIndex;
	for (int i = 0; i < numSub;i++) {
		if (index==UsersSubscriptionTypes[i].index) {
			UsersSubscriptionTypes[i].subName = newName;
			UsersSubscriptionTypes[i].ValidityDays = newValidityDays;
			UsersSubscriptionTypes[i].SubPrice = newPrice;
			bool IndexExists = false;
			for (int i = 0; i < numSub; i++) {
				if (UsersSubscriptionTypes[i].index == NewIndex) {
					IndexExists = true;
					
				}
				else {
					UsersSubscriptionTypes[i].index = NewIndex;
				}
			}

			while (IndexExists) {
				cout << "Subscription index already exists. Please enter a new index: ";
				cin >> NewIndex;

				IndexExists = false;
				for (int i = 0; i < numSub; i++) {
					if (UsersSubscriptionTypes[i].index == NewIndex) {
						IndexExists = true;
						break;
					}
				}
			}
			

						
		}
	}
	
}
void DeleteSubscriptions(Subscription UsersSubscriptionTypes[], int& numSub, int index) {
	for (int i = 0; i < numSub; i++) {
		if (index == users[i].id) {

			UsersSubscriptionTypes[i] = UsersSubscriptionTypes[i + 1];
			numSub = numSub - 1; // Decrement the count of users
			cout << "User Subscription Plan deleted successfully!\n";
			return;

						
			cout << "Subscription Plan not found!\n";




		}
	}
}
int main() {
	
}

