#include <iostream>
#include <string>
#include <ctime>
#include<cstdlib>
#define maxStations 100

using namespace std;
const int MaxUsers = 100;
const int MaxSub = 100;

int firstLineStations = 35, secondLineStations = 20, thirdLineStations = 29;
int lineStations[3] = { firstLineStations, secondLineStations, thirdLineStations };
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


struct MetroStations {
	int id, line;
	string name;
};
MetroStations stations[3][maxStations];
struct destination {
	string station;
	int id,line ;

};
struct departure {
	string station;
	int id, line;
	
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
void ViewUsersAccountsAdmin(User users[MaxUsers], int numUsers) {
	cout << "Accounts:\n";
	for (int i = 0; i < numUsers; i++) {
		cout << "Email: " << users[i].UserAccount.email << "\n";
	}
}
void EditUsersAccountsAdmin(User users[MaxUsers], int numUsers, int id) {
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
void DeleteUsersAccountsAdmin(User users[MaxUsers], int &numUsers, int id) {
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
void CreateNewPlanAdmin(Subscription UserSubscriptionTypes[], int& numSub) {
	string newName;
	string type;
	int newValidityDays;
	float newPrice;
	int NewIndex;
	bool IndexExists = false;
	cin>>type;
	cin >> newName;
	cin >> newValidityDays;
	cin >> newPrice;
	cin >> NewIndex;
/*
Here comes the code of the subscription type whether it is Student, Wallet or Public


*/
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
	string type;
	int newValidityDays;
	float newPrice;
	int NewIndex;
	bool IndexExists;
	cin >> newName;
	cin >> newValidityDays;
	cin >> newPrice;
	cin >> NewIndex;
	cin>>type;
	/*
Here comes the code of the subscription type whether it is Student, Wallet or Public


*/
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
			numSub = numSub - 1; // Decrement the count of Subsciription plans
			cout << "User Subscription Plan deleted successfully!\n";
			return;

						
			cout << "Subscription Plan not found!\n";
		}
	}
}
void StationsInitialization(MetroStations stations[3][maxStations]) {
	// Initialize stations for Line 1
	MetroStations line1Stations[] = {
		{1, 1, "El Marg El Gedida"},
		{2, 1, "El Marg"},
		{3, 1, "Ezbet El Nakhl"},
		{4, 1, "Ain Shams"},
		{5, 1, "El-Matareyya"},
		{6, 1, "Helmeyet El-Zaitoun"},
		{7, 1, "Hadayek El-Zaitoun"},
		{8, 1, "Saray El-Qobba"},
		{9, 1, "Hammamat El-Qobba"},
		{10, 1, "Kobri El-Qobba"},
		{11, 1, "Manshiet El-Sadr"},
		{12, 1, "El-Demerdash"},
		{13, 1, "Ghamra"},
		{14, 1, "Al Shohadaa"},
		{15, 1, "Orabi"},
		{16, 1, "Nasser"},
		{17, 1, "Sadat"},
		{18, 1, "Saad Zaghloul"},
		{19, 1, "Al Sayeda Zeinab"},
		{20, 1, "El-Malek El-Saleh"},
		{21, 1, "Mar Girgis"},
		{22, 1, "El-Zahraa"},
		{23, 1, "Dar El-Salam"},
		{24, 1, "Hadayek El-Maadi"},
		{25, 1, "Maadi"},
		{26, 1, "Sakanat El-Maadi"},
		{27, 1, "Tora El-Balad"},
		{28, 1, "Kozzika"},
		{29, 1, "Tora El-Asmant"},
		{30, 1, "El-Maasara"},
		{31, 1, "Hadayek Helwan"},
		{32, 1, "Wadi Hof"},
		{33, 1, "Helwan University"},
		{34, 1, "Ain Helwan"},
		{35, 1, "Helwan"}
	};

	// Copy stations for Line 1 to the array of struct
	for (int i = 0; i < firstLineStations; ++i) {
		stations[0][i] = line1Stations[i];
	}
	
	// Initialize stations for Line 2
	MetroStations line2Stations[] = {
		{1, 2,  "Shubra El-Kheima"},
		{2, 2,  "Kolleyyet El-Zeraa"},
		{3, 2,  "Mezallat"},
		{4, 2,  "Khalafawy"},
		{5, 2,  "St. Teresa"},
		{6, 2,  "Rod El-Farag"},
		{7, 2,  "Masarra"},
		{8, 2,  "Al Shohadaa"},
		{9, 2,  "Ataba"},
		{10, 2, "Mohamed Naguib"},
		{11, 2, "Sadat"},
		{12, 2, "Opera"},
		{13, 2, "Dokki"},
		{14, 2, "Bohooth"},
		{15, 2, "Cairo University"},
		{16, 2, "Faisal"},
		{17, 2, "Giza"},
		{18, 2, "Omm El-Misryeen"},
		{19, 2, "Sakiat Mekki"},
		{20, 2, "El-Monib"}
	};

	// Copy stations for Line 2 to the array of struct
	for (int i = 0; i < secondLineStations; ++i) {
		stations[1][i] = line2Stations[i];
	}


		// Initialize stations for Line 3
		MetroStations line3Stations[] = {
			{1, 3,  "Mohawar Rod El Farag"},
			{2, 3,  "Al Tareeq Al Daery"},
			{3, 3,  "Al Qawmeya Al Arabeya"},
			{4, 3,  "Al Bohy"},
			{5, 3,  "Imbaba"},
			{6, 3,  "Sudan"},
			{7, 3,  "El Kit Kat"},
			{8, 3,  "Safaa Hegazy"},
			{9, 3,  "Maspero"},
			{10, 3, "Nasser"},
			{11, 3, "Al Ataba"},
			{12, 3, "Bab El Shaaria"},
			{13, 3, "Al Gesh"},
			{14, 3, "Abdu Basha"},
			{15, 3, "Al Abbasiya"},
			{16, 3, "Fair Zone"},
			{17, 3, "Cairo Stadium"},
			{18, 3, "Kolleyet El-Banat"},
			{19, 3, "Al Ahram"},
			{20, 3, "Haroun"},
			{21, 3, "Heliopolis"},
			{22, 3, "Alf Maskan"},
			{23, 3, "Nady El Shams"},
			{24, 3, "Al Nozha"},
			{25, 3, "Hisham Barakat"},
			{26, 3, "Qubba"},
			{27, 3, "Omar Ibn El-Khattab"},
			{28, 3, "Al Haykstep"},
			{29, 3, "Adly Mansour"}
		};

		// Copy stations for Line 3 to the array of struct
		for (int i = 0; i < thirdLineStations; ++i) {
			stations[2][i] = line3Stations[i];
		}
	}
void inputDepartureAndDestination(departure& userDeparture , destination& userDestination) {

	cout << "Enter the metro line number you are going from: \n" << "Enter 1 or 2 or 3 \n";
	cin >> userDeparture.line;
	while (userDeparture.line != 1 && userDeparture.line != 2 && userDeparture.line != 3) {
		cout << "you entered a wrong line number \n" << "Enter the metro line again: \n";
		cout << "Enter 1 or 2 or 3\n";
		cin >> userDeparture.line;
	}
	cout << "Enter your departure station \n";
	cin.ignore();
	getline(cin, userDeparture.station);
	
	cout << "Enter the metro line number you are heading: \n" << "Enter 1 or 2 or 3 \n";
	cin >> userDestination.line;
	while (userDestination.line != 1 && userDestination.line != 2 && userDestination.line != 3) {
		cout << "you entered a wrong line number \n" << "Enter the metro line again: \n";
		cout << "Enter 1 or 2 or 3\n";
		cin >> userDestination.line;
	}
	cout << "Enter your destination station \n";
	cin.ignore();
	getline(cin, userDestination.station);
}
int GetDepartureId(departure& userDeparture) {
	int NumberOfStations;
	

	if (userDeparture.line == 1)
		NumberOfStations = 35;
	else if (userDeparture.line == 2)
		NumberOfStations = 20;
	else if (userDeparture.line == 3)
		NumberOfStations = 29;
	else return -1;

	for (int i = 0; i < NumberOfStations; i++) {
		if (userDeparture.station == stations[userDeparture.line - 1][i].name) {
			return stations[userDeparture.line - 1][i].id;

		}
	}
}
int GetDestinationId(destination& userDestination) {
	int NumberOfStations;
	if (userDestination.line == 1)
		NumberOfStations = 35;
	else if (userDestination.line == 2)
		NumberOfStations = 20;
	else if (userDestination.line == 3)
		NumberOfStations = 29;
	else return -1;
	


	for (int i = 0; i < NumberOfStations; i++) {
		if (userDestination.station == stations[userDestination.line - 1][i].name) {

			return stations[userDestination.line - 1][i].id;
		}
	}
}
int CalulateNumberOfStations(departure& userDeparture, destination& userDestination) {
	int NumberOfStations;
	if (userDeparture.line == userDestination.line)
		NumberOfStations = abs(userDestination.id - userDeparture.id) +1;
	else if (userDeparture.line == 1 && userDestination.line == 2)
		NumberOfStations = abs(userDeparture.id - 14) + abs(userDestination.id - 8)+1;

	else if (userDeparture.line == 1 && userDestination.line == 3) {
		if (userDeparture.id <= 14 && userDestination.id >= 11)
		NumberOfStations = abs(userDeparture.id - 16) + abs(userDestination.id - 10) - 1;
	else
		NumberOfStations = abs(userDeparture.id - 16) + abs(userDestination.id - 10) + 1;
	}
	else if (userDeparture.line == 2 && userDestination.line == 1)
		NumberOfStations = abs(userDeparture.id - 8) + abs(userDestination.id - 14)+1;

	else if (userDeparture.line == 2 && userDestination.line == 3) {
		if (userDeparture.id >= 11 && userDestination.id <= 10)
			NumberOfStations = abs(userDeparture.id - 9) + abs(userDestination.id - 11) - 1;
		else 
			NumberOfStations = abs(userDeparture.id - 9) + abs(userDestination.id - 11) + 1;

	}
	else if (userDeparture.line == 3 && userDestination.line == 1){
	if (userDeparture.id>= 11 && userDestination.id<= 14)
	    	NumberOfStations = abs(userDeparture.id - 10) + abs(userDestination.id - 16) - 1;
	else
		NumberOfStations = abs(userDeparture.id - 10) + abs(userDestination.id - 16) + 1;
	}

	else if (userDeparture.line == 3 && userDestination.line == 2) {
		if (userDeparture.id <= 10 && userDestination.id >= 11)
			NumberOfStations = abs(userDeparture.id - 11) + abs(userDestination.id - 9) - 1;
		else
			NumberOfStations = abs(userDeparture.id - 10) + abs(userDestination.id - 16) + 1;
	}

	return NumberOfStations;

	// opera to safaa hegazy cus of sadat we didnt make it a transition station
	//fair zone to ghamra
	
}


void AddMetroStation(MetroStations stations[3][maxStations]) {
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
void ViewMetroStations(MetroStations stations[3][maxStations]) {
	int lineNumber, NumberOfStations;
	char option;
	do {
		cout << "Enter the line you want to view \n";
		cin >> lineNumber;

		if (lineNumber >= 1 && lineNumber <= 3) {
			NumberOfStations = lineStations[lineNumber - 1];

			cout << "Stations:\n";
			for (int i = 0; i < NumberOfStations; i++) {
				cout << i + 1 << "->" << stations[lineNumber - 1][i].name << "\n";
			}
		}
		cout << "Do you want to view another line ? (y/n) \n";
		cin >> option;
	} while (option == 'y' || option == 'Y');
	
}
void EditMetroStation(MetroStations stations[3][maxStations]) {
	
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
			if (id == stations[lineNumber-1][i].id) {
				cout << "Enter the new station for the metro:" << endl;
				cin.ignore();
				getline(cin, NewStation);
				stations[lineNumber-1][i].name = NewStation;
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
void DeleteMetroStation(MetroStations stations[3][maxStations]) {
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
				firstLineStations = NumberOfStations;
			else if (lineNumber == 2)
				secondLineStations = NumberOfStations;
			else if (lineNumber == 3)
				thirdLineStations = NumberOfStations;
		}
		else {
			cout << "Station not found!\n";
		}
	}
	else {
		cout << "Invalid line number!\n";
	}
}

int main() {
	
}

