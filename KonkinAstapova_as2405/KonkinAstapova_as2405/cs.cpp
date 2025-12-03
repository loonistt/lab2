#include "cs.h"
#include "logger.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CS::CS() : id(0), workshop(0), ActiveWorkshop(0), score(0) {}

CS::CS(int new_id) : id(new_id), workshop(0), ActiveWorkshop(0), score(0) {}

void CS::setWorkshop(int new_workshop) {
    if (new_workshop > 0 && new_workshop <= 50) {
        workshop = new_workshop;
        if (ActiveWorkshop > workshop) {
            ActiveWorkshop = workshop;
        }
    }
    else {
        throw invalid_argument("Number of workshops must be between 1 and 50");
    }
}

void CS::setActiveWorkshop(int new_active) {
    if (new_active >= 0 && new_active <= workshop) {
        ActiveWorkshop = new_active;
    }
    else {
        throw invalid_argument("Active workshops must be between 0 and " + to_string(workshop));
    }
}

void CS::setScore(float new_score) {
    if (new_score >= 0 && new_score <= 10) {
        score = new_score;
    }
    else {
        throw invalid_argument("Score must be between 0 and 10");
    }
}

float CS::getUnusedPercentage() const {
    if (workshop == 0) return 0.0f;
    return ((workshop - ActiveWorkshop) * 100.0f) / workshop;
}

ostream& operator<<(ostream& out, const CS& cs) {
    out << "CS ID: " << cs.getId() << "\n"
        << "Name: " << cs.getName() << "\n"
        << "Workshops: " << cs.getWorkshop() << " (active: " << cs.getActiveWorkshop() << ")\n"
        << "Unused workshops: " << cs.getUnusedPercentage() << "%\n"
        << "Score: " << cs.getScore() << "\n\n";
    return out;
}

void addCsData(CS& cs) {
    cout << "Enter name of the compressor station: ";
    INPUT_LINE(cin, cs.name);

    cout << "Enter the number of workshops (1-50): ";
    int workshops = GetCorrectNumber<int>(1, 50); 
    try {
        cs.setWorkshop(workshops);
    }
    catch (const invalid_argument& e) {
        cout << "ERROR: " << e.what() << endl;
        throw;
    }

    cout << "Enter the number of active workshops (0-" << workshops << "): ";
    int active = GetCorrectNumber<int>(0, workshops);
    try {
        cs.setActiveWorkshop(active);
    }
    catch (const invalid_argument& e) {
        cout << "ERROR: " << e.what() << endl;
        throw;
    }

    cout << "Enter the compressor station score (0-10): ";
    float score_val = GetCorrectNumber<float>(0, 10);
    try {
        cs.setScore(score_val);
    }
    catch (const invalid_argument& e) {
        cout << "ERROR: " << e.what() << endl;
        throw;
    }
}

void editCsData(CS& cs) {
    cout << "Enter new value of active workshops (0-" << cs.getWorkshop() << "): ";
    int active = GetCorrectNumber<int>(0, cs.getWorkshop());

    try {
        cs.setActiveWorkshop(active);
    }
    catch (const invalid_argument& e) {
        cout << "ERROR: " << e.what() << endl;
        throw;
    }
}