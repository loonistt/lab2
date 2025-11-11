#include "pipe.h"
#include "checkshow.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Pipe::Pipe() : id(0), length(0), diameter(0), fixing(false) {}

Pipe::Pipe(int new_id) : id(new_id), length(0), diameter(0), fixing(false) {}

void Pipe::setLength(float new_length) {
    if (new_length > 0 && new_length <= 50) {
        length = new_length;
    }
    else {
        throw invalid_argument("Length must be between 0 and 50 meters");
    }
}

void Pipe::setDiameter(float new_diameter) {
    if (new_diameter > 0 && new_diameter <= 2500) {
        diameter = new_diameter;
    }
    else {
        throw invalid_argument("Diameter must be between 0 and 2500 millimeters");
    }
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << "Pipe ID: " << pipe.getId() << "\n"
        << "Name: " << pipe.getName() << "\n"
        << "Length: " << pipe.getLength() << "m\n"
        << "Diameter: " << pipe.getDiameter() << "mm\n"
        << "Status: " << (pipe.getFixing() ? "Working" : "In repair") << "\n\n";
    return out;
}

void addPipeData(Pipe& pipe) {
    cout << "Enter name of the pipe: ";
    getline(cin >> ws, pipe.name);

    while (true) {
        cout << "Enter pipe length (in meters): ";
        float len;
        cin >> len;
        if (checkCinError()) continue;

        try {
            pipe.setLength(len);
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        cout << "Enter pipe diameter (in millimeters): ";
        float diam;
        cin >> diam;
        if (checkCinError()) continue;

        try {
            pipe.setDiameter(diam);
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
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