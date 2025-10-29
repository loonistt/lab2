#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Pipe {
    int id;
    string name;
    float length;
    float diameter;
    bool fixing = false;

    Pipe() : id(0) {}
    Pipe(int new_id) : id(new_id) {}
};

ostream& operator << (ostream& out, const Pipe& pipe);
void addPipeData(Pipe& pipe);
void editPipeData(Pipe& pipe);