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
void Deposit(PERSON p[], int size, string custName, float amount);
void NewCopy(ofstream& outfile, PERSON p[], int size);
PERSON * readData(int & size);

int main() {

	string first, last;
	int size = 0;
	float amount;

	PERSON *p;

	p = readData(size);

	Display(p, size);

	FindRichest(p, size);

	cout << "Enter name: ";
	cin >> first;
	cin >> last;
	first =first.substr(0,9);
	last = last.substr(0,10);
	// combining strings with a space inbetween.
	first.append(" ");
	first.append(last);

	cout << "Amount: ";
	cin >> amount;

	Deposit(p, size, first, amount);

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

	cout << endl << "Highest balance: " << p[richest].Name << endl;

};


void Deposit(PERSON p[], int size, string custName, float amount) {

	char name[20];
	bool found = false;
	std::strcpy(name, custName.c_str());
	for (int i = 0; i < size; i++) {
		// compares both char, if equal then it will update the blance.
		if (strcmp(p[i].Name, name) == 0) {
			p[i].Balance += amount;
			cout << "New balance: " << p[i].Balance << endl;
			found = true;
			break;
		}
	};
	if (found == false)
	cout << "Record not found." << endl;
};

void NewCopy(ofstream& outfile, PERSON p[], int size) {
	cout << fixed << setprecision(2);
	for (int i = 0; i < size; i++) {
		outfile << p[i].Name << " " << p[i].Balance << "\n";

	};

	cout << "File updated..." << endl;

};

PERSON * readData(int & size){

	string first, last;
	float money, amount;
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

	PERSON *p;
	p = new PERSON [size];


	// inputs information from file into array
	for (int i = 0; i < size; i++) {
		infile >> first;
		infile >> last;
		infile >> money;

		// resize 9 for first, 10 for last
		first =first.substr(0,9);
		last = last.substr(0,10);
		// combining strings with a space inbetween.
		first.append(" ");
		first.append(last);

		std::strcpy(p[i].Name, first.c_str());

		p[i].Balance = money;

	};
		infile.close();
	return p;
};
