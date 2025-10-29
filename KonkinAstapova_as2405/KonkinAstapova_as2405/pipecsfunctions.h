#pragma once
#include "pipe.h"
#include "cs.h"
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class PipelineSystem {
private:
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> stations;
    int nextPipeId = 1;
    int nextCsId = 1;

public:
    void addPipe();
    void addCS();
    void viewAllObjects();
    void editPipe();
    void editCS();

    vector<int> findPipesByName(const string& name);
    vector<int> findPipesByFixing(bool fixing);
    vector<int> findCSByName(const string& name);
    vector<int> findCSByUnusedPercentage(float minPercent, float maxPercent);

    void batchEditPipes(const vector<int>& pipeIds);
    void deletePipe();
    void deleteCS();
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};