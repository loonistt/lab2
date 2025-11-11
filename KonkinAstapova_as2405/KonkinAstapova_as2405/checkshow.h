#pragma once
#include <iostream>
#include <string>
using namespace std;

inline bool checkCinError();
void showMenu();

inline bool checkCinError() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error, incorrect value.\n";
        return true;
    }
    return false;
}