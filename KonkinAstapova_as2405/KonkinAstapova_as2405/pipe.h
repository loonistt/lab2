#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pipe {
private:
    static int nextId;
    int id;
    string name;
    float length;
    float diameter;
    bool fixing;

public:
    Pipe();

    int getId() const { return id; }
    string getName() const { return name; }
    float getLength() const { return length; }
    float getDiameter() const { return diameter; }
    bool getFixing() const { return fixing; }

    void setName(const string& new_name) { name = new_name; }
    void setLength(float new_length);
    void setDiameter(float new_diameter);
    void setFixing(bool new_fixing) { fixing = new_fixing; }

    friend ostream& operator<<(ostream& out, const Pipe& pipe);
    friend istream& operator>>(istream& in, Pipe& pipe);
    void editPipe();
};

int Pipe::nextId = 1;