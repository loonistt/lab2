#include "menufilter.h"
#include "logcheckshow.h"
#include <iostream>
using namespace std;

void searchPipesMenu(PipelineSystem& system) {
    cout << "Search pipes:\n";
    cout << "1. By name\n";
    cout << "2. By repair status\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    vector<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);
        results = system.findPipesByName(name);
    }
    else if (choice == 2) {
        int status;
        cout << "Enter status (0 - in repair, 1 - working): ";
        cin >> status;
        results = system.findPipesByFixing(status == 1);
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    if (results.empty()) {
        cout << "No pipes found.\n\n";
    }
    else {
        cout << "Found " << results.size() << " pipes:\n";
        for (int id : results) {
            cout << "Pipe ID: " << id << endl;
        }
        cout << endl;
    }
}

void searchCSMenu(PipelineSystem& system) {
    cout << "Search compressor stations:\n";
    cout << "1. By name\n";
    cout << "2. By unused workshops percentage\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    vector<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);
        results = system.findCSByName(name);
    }
    else if (choice == 2) {
        float minPercent, maxPercent;
        cout << "Enter minimum unused percentage: ";
        cin >> minPercent;
        cout << "Enter maximum unused percentage: ";
        cin >> maxPercent;
        results = system.findCSByUnusedPercentage(minPercent, maxPercent);
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    if (results.empty()) {
        cout << "No compressor stations found.\n\n";
    }
    else {
        cout << "Found " << results.size() << " compressor stations:\n";
        for (int id : results) {
            cout << "CS ID: " << id << endl;
        }
        cout << endl;
    }
}