#pragma once
#include <iostream>
#include <string>
using namespace std;

struct CS {
    int id;
    string name;
    int workshop;
    int ActiveWorkshop;
    float score;

    CS() : id(0) {}
    CS(int new_id) : id(new_id) {}
};

ostream& operator << (ostream& out, const CS& cs);
void addCsData(CS& cs);
void editCsData(CS& cs);