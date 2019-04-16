// David Devore

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

struct  PERSON {
	char  Name[20];
	float Balance;
};

void Display(PERSON p[], int size);
void FindRichest(PERSON p[], int size);
void Deposit(PERSON p[], int size);
void NewCopy(ofstream& outfile, PERSON p[], int size);

int main() {

	string first, last;
	float money;
	int  size = 0;
	bool check = false;

	ifstream infile;
	infile.open("data.txt");


	// Reads file, increase size for each line til end of file.
	while (check != true) {
		getline(infile, first);
		check = infile.eof();

		if (check == false)
			size++;
	};

	// clear eof and reset to top of file.
	infile.clear();
	infile.seekg(0, infile.beg);

	// create struct array using size

	PERSON p[size];

	// inputs information from file into array
	for (int i = 0; i < size; i++) {
		infile >> first;
		infile >> last;
		infile >> money;

		// combining strings with a space inbetween.
		first.append(" ");
		first.append(last);

		std::strcpy(p[i].Name, first.c_str());

		p[i].Balance = money;

	};

	int input = 0;
	while (input != 4){

	cout << "\nMenu:" << endl;
	cout << "1. Display" << endl;
	cout << "2. Find Richest" << endl;
	cout << "3. Deposit" << endl;
	cout << "4. Exit" << endl;
	cin >> input;

	if (input == 1)
		Display(p, size);
	if (input == 2)
		FindRichest(p, size);
	if (input == 3)
		Deposit(p, size);

	};

	cout << "Updating file before exiting..." << endl;

	infile.close();

	ofstream outfile;

	outfile.open("data.txt");

	NewCopy(outfile, p, size);

	outfile.close();
	return 0;
};

void Display(PERSON p[], int size) {

	cout << setw(5) <<"Name" << setw(20) << "Balance" << endl;
	cout << setfill ('-') << setw(30) << "\n";

// Resetting setfill to " " and formating float output
	cout << setfill (' ') << fixed << setprecision(2);

	for (int i = 0; i < size; i++) {
		cout << setw(20) << left << p[i].Name;
		cout << setw(5) << left << p[i].Balance << "\n";
	};

};

void FindRichest(PERSON p[], int size) {

	int richest = 0;

	for (int i = 0; i < size - 1; i++) {
		if (p[i].Balance > p[richest].Balance)
			richest = i;


	};

	cout << endl << "The customer with maximum balance is " << p[richest].Name << endl;

};


void Deposit(PERSON p[], int size) {

	float amount;
	string first, last;
	char name[20];

	cout << "Enter your full name to deposit money: ";
	cin >> first;
	cin >> last;

	// combining strings with a space inbetween.
	first.append(" ");
	first.append(last);

	std::strcpy(name, first.c_str());

	cout << name << ", how much would you like to deposit? ";
	cin >> amount;


	for (int i = 0; i < size; i++) {
		// compares both char, if equal then it will update the blance.
		if (strcmp(p[i].Name, name) == 0) {
			p[i].Balance += amount;
			cout << "Now your new balance is " << p[i].Balance << endl;
		};


	};
};

void NewCopy(ofstream& outfile, PERSON p[], int size) {
	cout << fixed << setprecision(2);
	for (int i = 0; i < size; i++) {
		outfile << p[i].Name << " " << p[i].Balance << "\n";

	};

	cout << "File updated, have a great day!" << endl;

};