#pragma once
#include "pipe.h"
#include "cs.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class PipelineSystem {
private:
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> stations;

public:
    PipelineSystem() {}  

    void addPipe();
    void addCS();
    void viewAllObjects();
    void editPipe();
    void editCS();
    void deletePipe();
    void deleteCS();
    void searchPipesMenu();
    void searchCSMenu();
    unordered_set<int> findPipesByName(const string& name);
    unordered_set<int> findPipesByFixing(bool fixing);
    unordered_set<int> findCSByName(const string& name);
    unordered_set<int> findCSByUnusedPercentage(float minPercent, float maxPercent);

    void batchEditPipes(const unordered_set<int>& pipeIds);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);

    void clearAllData();
};