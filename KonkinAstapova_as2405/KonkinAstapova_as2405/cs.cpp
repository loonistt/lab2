#include "cs.h"
#include "logcheckshow.h"
#include <iostream>
using namespace std;

ostream& operator << (ostream& out, const CS& cs) {
    float unusedPercent = ((cs.workshop - cs.ActiveWorkshop) * 100.0f) / cs.workshop;
    out << "CS ID: " << cs.id << "\n"
        << "Name: " << cs.name << "\n"
        << "Workshops: " << cs.workshop << " (active: " << cs.ActiveWorkshop << ")\n"
        << "Unused workshops: " << unusedPercent << "%\n"
        << "Score: " << cs.score << "\n\n";
    return out;
}

void addCsData(CS& cs) {
    cout << "Enter name of the compressor station: ";
    getline(cin >> ws, cs.name);

    while (true) {
        cout << "Enter the number of workshops: ";
        cin >> cs.workshop;
        if (checkCinError() || cs.workshop <= 0 || cs.workshop > 50) {
            cout << "Number of workshops must be between 1 and 50.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter the number of active workshops: ";
        cin >> cs.ActiveWorkshop;
        if (checkCinError() || cs.ActiveWorkshop < 0 || cs.ActiveWorkshop > cs.workshop) {
            cout << "Active workshops must be between 0 and " << cs.workshop << ".\n";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter the compressor station score (0-10): ";
        cin >> cs.score;
        if (checkCinError() || cs.score < 0 || cs.score > 10) {
            cout << "Score must be between 0 and 10.\n";
        }
        else {
            break;
        }
    }
}

void editCsData(CS& cs) {
    while (true) {
        cout << "Enter new value of active workshops: ";
        cin >> cs.ActiveWorkshop;
        if (checkCinError() || cs.ActiveWorkshop < 0 || cs.ActiveWorkshop > cs.workshop) {
            cout << "Active workshops must be between 0 and " << cs.workshop << ".\n";
        }
        else {
            break;
        }
    }
}