#pragma once
#include <iostream>
#include <string>
using namespace std;

class CS {
private:
    int id;
    string name;
    int workshop;
    int ActiveWorkshop;
    float score;

public:
    CS();
    CS(int new_id);

    int getId() const { return id; }
    string getName() const { return name; }
    int getWorkshop() const { return workshop; }
    int getActiveWorkshop() const { return ActiveWorkshop; }
    float getScore() const { return score; }

    void setName(const string& new_name) { name = new_name; }
    void setWorkshop(int new_workshop);
    void setActiveWorkshop(int new_active);
    void setScore(float new_score);

    float getUnusedPercentage() const;

    friend void addCsData(CS& cs);
    friend void editCsData(CS& cs);
    friend ostream& operator<<(ostream& out, const CS& cs);
};

void addCsData(CS& cs);
void editCsData(CS& cs);
ostream& operator<<(ostream& out, const CS& cs);