#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pipe {
private:
    int id;
    string name;
    float length;
    float diameter;
    bool fixing;

public:
    Pipe();
    Pipe(int new_id);

    int getId() const { return id; }
    string getName() const { return name; }
    float getLength() const { return length; }
    float getDiameter() const { return diameter; }
    bool getFixing() const { return fixing; }

    void setName(const string& new_name) { name = new_name; }
    void setLength(float new_length);
    void setDiameter(float new_diameter);
    void setFixing(bool new_fixing) { fixing = new_fixing; }

    friend void addPipeData(Pipe& pipe);
    friend void editPipeData(Pipe& pipe);
    friend ostream& operator<<(ostream& out, const Pipe& pipe);
};

void addPipeData(Pipe& pipe);
void editPipeData(Pipe& pipe);
ostream& operator<<(ostream& out, const Pipe& pipe);