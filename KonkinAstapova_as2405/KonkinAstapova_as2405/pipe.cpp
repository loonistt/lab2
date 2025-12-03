#include "pipe.h"
#include "logger.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Pipe::Pipe() : id(nextId++), length(0), diameter(0), fixing(false) {}

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
    out << "Pipe ID: " << pipe.id << "\n"
        << "Name: " << pipe.name << "\n"
        << "Length: " << pipe.length << "m\n"
        << "Diameter: " << pipe.diameter << "mm\n"
        << "Status: " << (pipe.fixing ? "Working" : "In repair") << "\n\n";
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    cout << "Enter name of the pipe: ";
    INPUT_LINE(in, pipe.name);

    cout << "Enter pipe length (in meters, 0-50): ";
    float len = GetCorrectNumber<float>(0, 50);
    if (len > 0 && len <= 50) {
        pipe.length = len;
    }
    else {
        throw invalid_argument("Length must be between 0 and 50 meters");
    }

    cout << "Enter pipe diameter (in millimeters, 0-2500): ";
    float diam = GetCorrectNumber<float>(0, 2500);
    if (diam > 0 && diam <= 2500) {
        pipe.diameter = diam;
    }
    else {
        throw invalid_argument("Diameter must be between 0 and 2500 millimeters");
    }

    cout << "Choose pipe status (0 - in repair, 1 - working): ";
    pipe.fixing = GetCorrectBool();

    return in;
}

void Pipe::editPipe() {
    cout << "Enter new pipe status (0 - in repair, 1 - working): ";
    bool newStatus = GetCorrectBool();
    fixing = newStatus;  
}