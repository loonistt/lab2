#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "pipe.h"
#include "cs.h"
using namespace std;

class ActionLogger {
private:
    ofstream logFile;
    string filename;

public:
    ActionLogger(const string& logFilename = "actions.log");
    ~ActionLogger();

    void logAddPipe(const Pipe& pipe);
    void logAddCS(const CS& cs);
    void logEditPipe(int id, bool newStatus);
    void logEditCS(int id, int newActive);
    void logDeletePipe(int id);
    void logDeleteCS(int id);

    void logBatchEdit(const unordered_set<int>& pipeIds, bool newStatus);
    void logBatchEdit(const unordered_map<int, bool>& pipeStatuses);

    void logSaveToFile(const string& filename);
    void logLoadFromFile(const string& filename);

    void logViewAllObjects();
    void logSearchPipesByName(const string& name);
    void logSearchPipesByStatus(bool status);
    void logSearchCSByName(const string& name);
    void logSearchCSByUnusedPercentage(float minPercent, float maxPercent);

    void logReplayFromFile(const string& filename);
    void logMessage(const string& message);
    void logMenuAction(const string& action);
};