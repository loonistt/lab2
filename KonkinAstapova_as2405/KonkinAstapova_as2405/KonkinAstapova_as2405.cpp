#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Pipe {
	string name;
	float length;
	float diameter;
	bool fixing = false;
};

struct CS {
	string name;
	int workshop;
	int ActiveWorkshop;
	float score;
};

void showMenu() {
	cout << "Pipelines and Compressor Stations \n\n";
	cout << "Menu: \n";
	cout << "1. Add a pipe \n";
	cout << "2. Add a compressor station \n";
	cout << "3. View all objects \n";
	cout << "4. Edit a pipe \n";
	cout << "5. Edit a compressor station \n";
	cout << "6. Save to file \n";
	cout << "7. Load from file \n";
	cout << "0. Exit \n\n";
	cout << "Please select an action :";
}

bool checkCinError() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error, incorrect value.\n";
		return true;
	}
	return false;
}

void addPipe(Pipe& pipe) {
	cout << "Enter name of the pipe: ";
	getline(cin >> ws, pipe.name);

	while (true) {
		cout << "\nEnter pipe length (in meters): ";
		cin >> pipe.length;

		if (checkCinError()) {
			continue;
		}
		if (pipe.length <= 0) {
			cout << "Length can`t be less than 0 meters or be 0.\n";
		}
		else if (pipe.length > 50) {
			cout << "Length can`t be more than 50 meters.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nEnter pipe diameter (in millimeters): ";
		cin >> pipe.diameter;

		if (checkCinError()) {
			continue;
		}
		if (pipe.diameter <= 0) {
			cout << "Diameter can`t be less than 0 millimeters or be 0.\n";
		}
		else if (pipe.diameter > 2500) {
			cout << "Diameter can`t be more than 2500 millimeters.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nChoose pipe status (0 - fixing, 1 - not fixing): ";
		cin >> pipe.fixing;
		if (checkCinError()) {
			continue;
		}
		break;
	}
}

void addCs(CS& cs) {
	cout << "Enter name of the compressor station: ";
	getline(cin >> ws, cs.name);

	while (true) {
		cout << "\nEnter the number of workshops: ";
		cin >> cs.workshop;
		if (checkCinError()) {
			continue;
		}
		if (cs.workshop <= 0) {
			cout << "The number of workshops can`t be less than 0 or be 0.\n";
		}
		else if (cs.workshop > 50) {
			cout << "The number of workshops can`t be more than 50.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nEnter the number of active workshops: ";
		cin >> cs.ActiveWorkshop;

		if (checkCinError()) {
			continue;
		}
		if (cs.ActiveWorkshop < 0) {
			cout << "The number of active workshops can`t be less than 0.\n";
		}
		else if (cs.ActiveWorkshop > cs.workshop) {
			cout << "The number of active workshops can`t be more than the number of workshops.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nEnter the compressor station score: ";
		cin >> cs.score;

		if (checkCinError()) {
			continue;
		}
		if (cs.score > 10) {
			cout << "Sсore must be in range from 0 to 10.";
		}
		else if (cs.score < 0) {
			cout << "Sсore must be in range from 0 to 10.";
		}
		else {
			break;
		}
	}
}

ostream& operator << (ostream& out, const Pipe& pipe) {
	out << "Information about pipes:\n\n"
		<< "Name: " << pipe.name
		<< "\nLength: " << pipe.length
		<< "\nDiameter: " << pipe.diameter
		<< "\nStatus: " << ((pipe.fixing) ? "not " : "") << "fixing\n\n\n";
	return out;
}

ostream& operator << (ostream& out, const CS& cs) {
	out << "Information about compressor stations:\n\n"
		<< "Name: " << cs.name
		<< "\nNumber of workshops: " << cs.workshop
		<< "\nNumber of active workshops: " << cs.ActiveWorkshop
		<< "\nScore: " << cs.score << "\n\n\n";
	return out;
}

void editPipe(Pipe& pipe) {
	while (true) {
		cout << "Enter new pipe status (0 - fixing, 1 - not fixing): ";
		cin >> pipe.fixing;
		if (checkCinError()) {
			continue;
		}
		break;
	}
}

void editCs(CS& cs) {
	while (true) {
		cout << "\nEnter new value of active workshops: ";
		cin >> cs.ActiveWorkshop;

		if (checkCinError()) {
			continue;
		}
		if (cs.ActiveWorkshop < 0) {
			cout << "The number of active workshops can`t be less than 0.\n";
		}
		else if (cs.ActiveWorkshop > cs.workshop) {
			cout << "The number of active workshops can`t be more than the number of workshops.\n";
		}
		else {
			break;
		}
	}
}

void savePipe(Pipe& pipe, bool pipeAvail) {
	ofstream file;
	file.open("data.txt");

	if (file.is_open()) {
		if (pipeAvail)
			file << "1" << "\n" << pipe.name << "\n" << pipe.length << "\n" << pipe.diameter << "\n" << pipe.fixing << "\n";
		else
			file << "0\n";
	}
	file.close();
}

void saveCs(CS& cs, bool csAvail) {
	ofstream file;
	file.open("data.txt", ios::app);

	if (file.is_open() && csAvail)
		file << "1" << "\n" << cs.name << "\n" << cs.workshop << "\n" << cs.ActiveWorkshop << "\n" << cs.score << "\n";
	else
		file << "0";
	file.close();
}

bool loadPipe(Pipe& pipe, ifstream& file) {
	int pipeCount;

	if (file.is_open()) {
		file >> pipeCount;
		if (pipeCount == 1) {
			getline(file >> ws, pipe.name);
			file >> pipe.length;
			file >> pipe.diameter;
			file >> pipe.fixing;
		}
		if (pipeCount)
			return true;
	}
	return false;
}

bool loadCs(CS& cs, ifstream& file) {
	int csCount;

	if (file.is_open()) {
		file >> csCount;
		if (csCount == 1) {
			getline(file >> ws, cs.name);
			file >> cs.workshop;
			file >> cs.ActiveWorkshop;
			file >> cs.score;
		}
		if (csCount)
			return true;
	}
	return false;
}

int main()
{
	Pipe pipe;
	bool pipeAvail = false;
	CS cs;
	bool csAvail = false;

	while (true) {
		showMenu();
		int action;
		cin >> action;

		if (cin.good() && action >= 0 && action <= 7) {
			switch (action) {
			case 0:
				return 0;

			case 1:
				if (pipeAvail) {
					cout << "Pipe is already there.\n\n";
				}
				else {
					addPipe(pipe);
					cout << "New pipe added successfully!\n\n";
					pipeAvail = true;
				}
				break;

			case 2:
				if (csAvail) {
					cout << "Compressor station is already there.\n\n";
				}
				else {
					addCs(cs);
					cout << "New compressor station added successfully!\n\n";
					csAvail = true;
				}
				break;
			case 3:
				if (pipeAvail) {
					cout << pipe;
				}
				else {
					cout << "Pipe doesn't there.\n\n";
				}
				if (csAvail) {
					cout << cs;
				}
				else {
					cout << "Compressor station doesn't there.\n\n";
				}
				break;
			case 4:
				if (pipeAvail) {
					editPipe(pipe);
					cout << "The pipe was successfully edited!\n\n";
				}
				else {
					cout << "Error, pipe doesn't there.\n\n";
				}
				break;
			case 5:
				if (csAvail) {
					editCs(cs);
					cout << "The compressor station was successfully edited!\n\n";
				}
				else {
					cout << "Error, compressor station doesn't there.\n\n";
				}
				break;
			case 6:
				savePipe(pipe, pipeAvail);
				if (pipeAvail)
					cout << "The pipe was successfully saved!\n\n";
				else
					cout << "The pipe doesn't there.\n\n";

				saveCs(cs, csAvail);
				if (csAvail) {
					cout << "The compressor station was successfully saved!\n\n";
				}
				else
					cout << "The compressor station doesn't there.\n\n";

				break;
			case 7:
				ifstream file;
				file.open("data.txt");
				pipeAvail = loadPipe(pipe, file);
				if (pipeAvail)
					cout << "The pipe was successfully loaded!\n\n";
				else
					cout << "Pipe doesn't there.\n\n";

				csAvail = loadCs(cs, file);
				if (csAvail) {
					cout << "The compressor station was successfully loaded!\n\n";
				}
				else
					cout << "The compressor station doesn't there.\n\n";
				break;
			}
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error, incorrect value.\n\n";
		}
	}
	return 0;
}