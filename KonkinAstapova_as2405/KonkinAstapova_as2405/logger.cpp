#include "logger.h"

ActionLogger::ActionLogger(const string& logFilename) : filename(logFilename) {
    logFile.open(filename, ios::trunc);
    if (logFile.is_open()) {
        logFile << "Session started" << endl;
    }
}

ActionLogger::~ActionLogger() {
    if (logFile.is_open()) {
        logFile << "Session ended" << endl;
        logFile.close();
    }
}

void ActionLogger::logAddPipe(const Pipe& pipe) {
    if (logFile.is_open()) {
        logFile << "ADD_PIPE " << pipe.getId() << " \"" << pipe.getName()
            << "\" " << pipe.getLength() << " " << pipe.getDiameter()
            << " " << pipe.getFixing() << endl;
    }
}

void ActionLogger::logAddCS(const CS& cs) {
    if (logFile.is_open()) {
        logFile << "ADD_CS " << cs.getId() << " \"" << cs.getName()
            << "\" " << cs.getWorkshop() << " " << cs.getActiveWorkshop()
            << " " << cs.getScore() << endl;
    }
}

void ActionLogger::logEditPipe(int id, bool newStatus) {
    if (logFile.is_open()) {
        logFile << "EDIT_PIPE " << id << " " << newStatus << endl;
    }
}

void ActionLogger::logEditCS(int id, int newActive) {
    if (logFile.is_open()) {
        logFile << "EDIT_CS " << id << " " << newActive << endl;
    }
}

void ActionLogger::logDeletePipe(int id) {
    if (logFile.is_open()) {
        logFile << "DELETE_PIPE " << id << endl;
    }
}

void ActionLogger::logDeleteCS(int id) {
    if (logFile.is_open()) {
        logFile << "DELETE_CS " << id << endl;
    }
}

void ActionLogger::logBatchEdit(const unordered_map<int, bool>& pipeStatuses) {
    if (logFile.is_open()) {
        logFile << "Batch edit started for " << pipeStatuses.size() << " pipes with individual statuses" << endl;

        for (const auto& pipe_pair : pipeStatuses) {
            logFile << "EDIT_PIPE " << pipe_pair.first << " " << pipe_pair.second << endl;
        }

        logFile << "Batch edit completed" << endl;
    }
}

void ActionLogger::logSaveToFile(const string& filename) {
    if (logFile.is_open()) {
        logFile << "SAVE_TO_FILE \"" << filename << "\"" << endl;
    }
}

void ActionLogger::logLoadFromFile(const string& filename) {
    if (logFile.is_open()) {
        logFile << "LOAD_FROM_FILE \"" << filename << "\"" << endl;
    }
}

void ActionLogger::logViewAllObjects() {
    if (logFile.is_open()) {
        logFile << "VIEW_ALL_OBJECTS" << endl;
    }
}

void ActionLogger::logSearchPipesByName(const string& name) {
    if (logFile.is_open()) {
        logFile << "SEARCH_PIPES_BY_NAME \"" << name << "\"" << endl;
    }
}

void ActionLogger::logSearchPipesByStatus(bool status) {
    if (logFile.is_open()) {
        logFile << "SEARCH_PIPES_BY_STATUS " << (status ? "working" : "repair") << endl;
    }
}

void ActionLogger::logSearchCSByName(const string& name) {
    if (logFile.is_open()) {
        logFile << "SEARCH_CS_BY_NAME \"" << name << "\"" << endl;
    }
}

void ActionLogger::logSearchCSByUnusedPercentage(float minPercent, float maxPercent) {
    if (logFile.is_open()) {
        logFile << "SEARCH_CS_BY_UNUSED " << minPercent << " " << maxPercent << endl;
    }
}

void ActionLogger::logReplayFromFile(const string& filename) {
    if (logFile.is_open()) {
        logFile << "REPLAY_FROM_FILE \"" << filename << "\"" << endl;
    }
}

void ActionLogger::logMenuAction(const string& action) {
    if (logFile.is_open()) {
        logFile << "MENU_ACTION " << action << endl;
    }
}