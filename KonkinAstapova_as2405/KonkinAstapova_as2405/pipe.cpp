#include "pipe.h"
#include "logcheckshow.h"
#include <iostream>
using namespace std;

ostream& operator << (ostream& out, const Pipe& pipe) {
    out << "Pipe ID: " << pipe.id << "\n"
        << "Name: " << pipe.name << "\n"
        << "Length: " << pipe.length << "m\n"
        << "Diameter: " << pipe.diameter << "mm\n"
        << "Status: " << (pipe.fixing ? "Working" : "In repair") << "\n\n";
    return out;
}


void addPipeData(Pipe& pipe) {
    cout << "Enter name of the pipe: ";
    getline(cin >> ws, pipe.name);

    while (true) {
        cout << "Enter pipe length (in meters): ";
        cin >> pipe.length;
        if (checkCinError() || pipe.length <= 0 || pipe.length > 50) {
            cout << "Length must be between 0 and 50 meters.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter pipe diameter (in millimeters): ";
        cin >> pipe.diameter;
        if (checkCinError() || pipe.diameter <= 0 || pipe.diameter > 2500) {
            cout << "Diameter must be between 0 and 2500 millimeters.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Choose pipe status (0 - in repair, 1 - working): ";
        cin >> pipe.fixing;
        if (checkCinError()) continue;
        break;
    }
}

void editPipeData(Pipe& pipe) {
    while (true) {
        cout << "Enter new pipe status (0 - in repair, 1 - working): ";
        cin >> pipe.fixing;
        if (checkCinError()) continue;
        break;
    }
}