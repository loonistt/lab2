#include "cs.h"
#include "logger.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CS::CS() : id(nextId++), workshop(0), ActiveWorkshop(0), score(0) {}

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
    out << "CS ID: " << cs.id << "\n"
        << "Name: " << cs.name << "\n"
        << "Workshops: " << cs.workshop << " (active: " << cs.ActiveWorkshop << ")\n"
        << "Unused workshops: " << cs.getUnusedPercentage() << "%\n"
        << "Score: " << cs.score << "\n\n";
    return out;
}

istream& operator>>(istream& in, CS& cs) {
    cout << "Enter name of the compressor station: ";
    INPUT_LINE(in, cs.name);

    cout << "Enter the number of workshops (1-50): ";
    int workshops = GetCorrectNumber<int>(1, 50);
    if (workshops > 0 && workshops <= 50) {
        cs.workshop = workshops;
        if (cs.ActiveWorkshop > cs.workshop) {
            cs.ActiveWorkshop = cs.workshop;
        }
    }
    else {
        throw invalid_argument("Number of workshops must be between 1 and 50");
    }

    cout << "Enter the number of active workshops (0-" << workshops << "): ";
    int active = GetCorrectNumber<int>(0, workshops);
    if (active >= 0 && active <= cs.workshop) {
        cs.ActiveWorkshop = active;
    }
    else {
        throw invalid_argument("Active workshops must be between 0 and " + to_string(cs.workshop));
    }

    cout << "Enter the compressor station score (0-10): ";
    float score_val = GetCorrectNumber<float>(0, 10);
    if (score_val >= 0 && score_val <= 10) {
        cs.score = score_val;
    }
    else {
        throw invalid_argument("Score must be between 0 and 10");
    }

    return in;
}

void CS::editCS() {
    cout << "Enter new value of active workshops (0-" << workshop << "): ";
    int active = GetCorrectNumber<int>(0, workshop);

    if (active >= 0 && active <= workshop) {
        ActiveWorkshop = active;
    }
    else {
        throw invalid_argument("Active workshops must be between 0 and " + to_string(workshop));
    }
}