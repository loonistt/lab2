#include "pipecsfunctions.h"
#include "checkshow.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;


void PipelineSystem::addPipe() {
    Pipe pipe(nextPipeId++);
    addPipeData(pipe);
    pipes.emplace(pipe.getId(), pipe);

    logger.logAddPipe(pipe);
    cout << "New pipe added successfully! ID: " << pipe.getId() << "\n\n";
}

void PipelineSystem::addCS() {
    CS cs(nextCsId++);
    addCsData(cs);
    stations.emplace(cs.getId(), cs);

    logger.logAddCS(cs);
    cout << "New compressor station added successfully! ID: " << cs.getId() << "\n\n";
}

void PipelineSystem::viewAllObjects() {
    logger.logViewAllObjects();

    if (pipes.empty()) {
        cout << "No pipes available.\n\n";
    }
    else {
        cout << "Pipes:\n";
        for (const auto& pipe_pair : pipes) {
            cout << pipe_pair.second;
        }
    }

    if (stations.empty()) {
        cout << "No compressor stations available.\n\n";
    }
    else {
        cout << "Compressor stations:\n";
        for (const auto& cs_pair : stations) {
            cout << cs_pair.second;
        }
    }
}

void PipelineSystem::editPipe() {
    int id;
    cout << "Enter pipe ID to edit: ";
    cin >> id;

    if (pipes.count(id)) {
        editPipeData(pipes[id]);
        bool newStatus = pipes[id].getFixing();

        logger.logEditPipe(id, newStatus);
        cout << "Pipe edited successfully!\n\n";
    }
    else {
        cout << "Pipe with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::editCS() {
    int id;
    cout << "Enter compressor station ID to edit: ";
    cin >> id;

    if (stations.count(id)) {
        editCsData(stations[id]);
        int newActive = stations[id].getActiveWorkshop();

        logger.logEditCS(id, newActive);
        cout << "Compressor station edited successfully!\n\n";
    }
    else {
        cout << "Compressor station with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::deletePipe() {
    int id;
    cout << "Enter pipe ID to delete: ";
    cin >> id;

    if (pipes.count(id)) {
        logger.logDeletePipe(id);
        pipes.erase(id);
        cout << "Pipe deleted successfully!\n\n";
    }
    else {
        cout << "Pipe with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::deleteCS() {
    int id;
    cout << "Enter compressor station ID to delete: ";
    cin >> id;

    if (stations.count(id)) {
        logger.logDeleteCS(id);
        stations.erase(id);
        cout << "Compressor station deleted successfully!\n\n";
    }
    else {
        cout << "Compressor station with ID " << id << " not found.\n\n";
    }
}

unordered_set<int> PipelineSystem::findPipesByName(const string& name) {
    unordered_set<int> result;
    for (const auto& pipe_pair : pipes) {
        if (pipe_pair.second.getName().find(name) != string::npos) {
            result.insert(pipe_pair.first);
        }
    }
    return result;
}

unordered_set<int> PipelineSystem::findPipesByFixing(bool fixing) {
    unordered_set<int> result;
    for (const auto& pipe_pair : pipes) {
        if (pipe_pair.second.getFixing() == fixing) {
            result.insert(pipe_pair.first);
        }
    }
    return result;
}

unordered_set<int> PipelineSystem::findCSByName(const string& name) {
    unordered_set<int> result;
    for (const auto& cs_pair : stations) {
        if (cs_pair.second.getName().find(name) != string::npos) {
            result.insert(cs_pair.first);
        }
    }
    return result;
}

unordered_set<int> PipelineSystem::findCSByUnusedPercentage(float minPercent, float maxPercent) {
    unordered_set<int> result;
    for (const auto& cs_pair : stations) {
        float unusedPercent = cs_pair.second.getUnusedPercentage();
        if (unusedPercent >= minPercent && unusedPercent <= maxPercent) {
            result.insert(cs_pair.first);
        }
    }
    return result;
}

void PipelineSystem::searchPipesMenu() {
    cout << "Search pipes:\n";
    cout << "1. By name\n";
    cout << "2. By repair status\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    unordered_set<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);

        logger.logSearchPipesByName(name);
        results = findPipesByName(name);

    }
    else if (choice == 2) {
        int status;
        cout << "Enter status (0 - in repair, 1 - working): ";
        cin >> status;

        logger.logSearchPipesByStatus(status == 1);
        results = findPipesByFixing(status == 1);

    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    if (results.empty()) {
        cout << "No pipes found.\n\n";
    }
    else {
        cout << "Found " << results.size() << " pipes:\n";
        for (int id : results) {
            if (pipes.count(id)) {
                cout << "ID: " << id << " - " << pipes[id].getName()
                    << " (Status: " << (pipes[id].getFixing() ? "Working" : "In repair") << ")\n";
            }
        }
        cout << endl;
    }
}

void PipelineSystem::searchCSMenu() {
    cout << "Search compressor stations:\n";
    cout << "1. By name\n";
    cout << "2. By unused workshops percentage\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    unordered_set<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);

        logger.logSearchCSByName(name);
        results = findCSByName(name);

    }
    else if (choice == 2) {
        float minPercent, maxPercent;
        cout << "Enter minimum unused percentage: ";
        cin >> minPercent;
        cout << "Enter maximum unused percentage: ";
        cin >> maxPercent;

        logger.logSearchCSByUnusedPercentage(minPercent, maxPercent);
        results = findCSByUnusedPercentage(minPercent, maxPercent);

    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    if (results.empty()) {
        cout << "No compressor stations found.\n\n";
    }
    else {
        cout << "Found " << results.size() << " compressor stations:\n";
        for (int id : results) {
            if (stations.count(id)) {
                float unusedPercent = stations[id].getUnusedPercentage();
                cout << "ID: " << id << " - " << stations[id].getName()
                    << " (Unused: " << unusedPercent << "%)\n";
            }
        }
        cout << endl;
    }
}


void PipelineSystem::batchEditPipes(const unordered_set<int>& pipeIds) {
    if (pipeIds.empty()) {
        cout << "No pipes to edit.\n\n";
        return;
    }

    cout << "Selected pipes for batch editing:\n";
    for (int id : pipeIds) {
        if (pipes.count(id)) {
            cout << "ID: " << id << " - " << pipes[id].getName() << endl;
        }
    }

    cout << "Edit all pipes? (1 - yes, 0 - select specific): ";
    int choice;
    cin >> choice;

    unordered_set<int> pipesToEdit;
    if (choice == 1) {
        pipesToEdit = pipeIds;
    }
    else {
        cout << "Enter pipe IDs to edit (one per line, -1 to finish): ";
        int id;
        while (cin >> id && id != -1) {
            if (pipeIds.find(id) != pipeIds.end()) {
                pipesToEdit.insert(id);
            }
            else {
                cout << "ID " << id << " not in search results.\n";
            }
        }
    }

    if (pipesToEdit.empty()) {
        cout << "No pipes selected for editing.\n\n";
        return;
    }

    unordered_map<int, bool> pipeStatuses;

    for (int id : pipesToEdit) {
        if (pipes.count(id)) {
            bool newStatus;
            while (true) {
                cout << "Enter status for pipe ID " << id << " (0 - in repair, 1 - working): ";
                cin >> newStatus;
                if (checkCinError()) continue;
                break;
            }
            pipeStatuses[id] = newStatus;
        }
    }

    logger.logBatchEdit(pipeStatuses);

    for (const auto& pipe_pair : pipeStatuses) {
        int id = pipe_pair.first;
        bool newStatus = pipe_pair.second;
        if (pipes.count(id)) {
            bool oldStatus = pipes[id].getFixing();
            pipes[id].setFixing(newStatus);
            cout << "Pipe ID " << id << " changed from "
                << (oldStatus ? "working" : "repair") << " to "
                << (newStatus ? "working" : "repair") << endl;
        }
    }
    cout << "Batch editing completed!\n\n";
}

void PipelineSystem::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << pipes.size() << "\n";
        for (const auto& pipe_pair : pipes) {
            const Pipe& pipe = pipe_pair.second;
            file << pipe.getId() << "\n" << pipe.getName() << "\n"
                << pipe.getLength() << "\n" << pipe.getDiameter() << "\n"
                << pipe.getFixing() << "\n";
        }

        file << stations.size() << "\n";
        for (const auto& cs_pair : stations) {
            const CS& cs = cs_pair.second;
            file << cs.getId() << "\n" << cs.getName() << "\n"
                << cs.getWorkshop() << "\n" << cs.getActiveWorkshop() << "\n"
                << cs.getScore() << "\n";
        }

        file.close();

        logger.logSaveToFile(filename);
        cout << "Data saved to " << filename << " successfully!\n\n";
    }
    else {
        cout << "Error opening file for writing.\n\n";
    }
}

void PipelineSystem::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();

        int pipeCount;
        file >> pipeCount;
        for (int i = 0; i < pipeCount; i++) {
            int id;
            file >> id;
            Pipe pipe(id);

            string name;
            getline(file >> ws, name);
            pipe.setName(name);

            float length, diameter;
            bool fixing;
            file >> length >> diameter >> fixing;
            pipe.setLength(length);
            pipe.setDiameter(diameter);
            pipe.setFixing(fixing);

            pipes.emplace(id, pipe);
            nextPipeId = max(nextPipeId, id + 1);
        }

        int csCount;
        file >> csCount;
        for (int i = 0; i < csCount; i++) {
            int id;
            file >> id;
            CS cs(id);

            string name;
            getline(file >> ws, name);
            cs.setName(name);

            int workshop, activeWorkshop;
            float score;
            file >> workshop >> activeWorkshop >> score;
            cs.setWorkshop(workshop);
            cs.setActiveWorkshop(activeWorkshop);
            cs.setScore(score);

            stations.emplace(id, cs);
            nextCsId = max(nextCsId, id + 1);
        }

        file.close();

        logger.logLoadFromFile(filename);
        cout << "Data loaded from " << filename << " successfully!\n\n";
    }
    else {
        cout << "Error opening file for reading.\n\n";
    }
}


void PipelineSystem::replayFromFile(const string& filename) {
    logger.logReplayFromFile(filename);

    clearAllData();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << "\n\n";
        return;
    }

    cout << "Replaying actions from: " << filename << endl;

    string line;
    while (getline(file, line)) {
        if (line.empty() || line.find("Session started") != string::npos || line.find("Session ended") != string::npos) {
            continue;
        }

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "ADD_PIPE") {
            int id;
            string name;
            float length, diameter;
            bool fixing;

            iss >> id;
            char quote;
            iss >> quote;
            getline(iss, name, '\"');
            iss >> length >> diameter >> fixing;

            Pipe pipe(id);
            pipe.setName(name);
            try {
                pipe.setLength(length);
                pipe.setDiameter(diameter);
            }
            catch (const invalid_argument& e) {
                cout << "Error adding pipe ID " << id << ": " << e.what() << endl;
                continue;
            }
            pipe.setFixing(fixing);

            pipes.emplace(id, pipe);
            nextPipeId = max(nextPipeId, id + 1);
            cout << "Added pipe ID " << id << endl;

        }
        else if (command == "ADD_CS") {
            int id, workshop, activeWorkshop;
            string name;
            float score;

            iss >> id;
            char quote;
            iss >> quote;
            getline(iss, name, '\"');
            iss >> workshop >> activeWorkshop >> score;

            CS cs(id);
            cs.setName(name);
            try {
                cs.setWorkshop(workshop);
                cs.setActiveWorkshop(activeWorkshop);
                cs.setScore(score);
            }
            catch (const invalid_argument& e) {
                cout << "Error adding CS ID " << id << ": " << e.what() << endl;
                continue;
            }

            stations.emplace(id, cs);
            nextCsId = max(nextCsId, id + 1);
            cout << "Added CS ID " << id << endl;

        }
        else if (command == "EDIT_PIPE") {
            int id;
            bool fixing;
            iss >> id >> fixing;

            if (pipes.count(id)) {
                bool oldStatus = pipes[id].getFixing();
                pipes[id].setFixing(fixing);
                cout << "Edited pipe ID " << id << " from "
                    << (oldStatus ? "working" : "repair") << " to "
                    << (fixing ? "working" : "repair") << endl;
            }
            else {
                cout << "Pipe ID " << id << " not found for editing" << endl;
            }

        }
        else if (command == "EDIT_CS") {
            int id, active;
            iss >> id >> active;

            if (stations.count(id)) {
                int oldActive = stations[id].getActiveWorkshop();
                try {
                    stations[id].setActiveWorkshop(active);
                    cout << "Edited CS ID " << id << " active workshops from "
                        << oldActive << " to " << active << endl;
                }
                catch (const invalid_argument& e) {
                    cout << "Error editing CS ID " << id << ": " << e.what() << endl;
                }
            }
            else {
                cout << "CS ID " << id << " not found for editing" << endl;
            }

        }
        else if (command == "DELETE_PIPE") {
            int id;
            iss >> id;

            if (pipes.count(id)) {
                pipes.erase(id);
                cout << "Deleted pipe ID " << id << endl;
            }
            else {
                cout << "Pipe ID " << id << " not found for deletion" << endl;
            }

        }
        else if (command == "DELETE_CS") {
            int id;
            iss >> id;

            if (stations.count(id)) {
                stations.erase(id);
                cout << "Deleted CS ID " << id << endl;
            }
            else {
                cout << "CS ID " << id << " not found for deletion" << endl;
            }

        }
        
        else if (command == "LOAD_FROM_FILE") {
            string loadFilename;
            char quote;
            iss >> quote;
            getline(iss, loadFilename, '\"');

            cout << "Loading data from: " << loadFilename << endl;
            loadFromFileForReplay(loadFilename);

        }
        else if (command == "SEARCH_PIPES_BY_NAME") {
            string name;
            char quote;
            iss >> quote;
            getline(iss, name, '\"');

            cout << "Searching pipes by name: " << name << endl;
            unordered_set<int> results = findPipesByName(name);
            if (results.empty()) {
                cout << "No pipes found with name containing: " << name << endl;
            }
            else {
                cout << "Found " << results.size() << " pipes:" << endl;
                for (int id : results) {
                    cout << "  ID: " << id << " - " << pipes[id].getName() << endl;
                }
            }

        }
        else if (command == "SEARCH_PIPES_BY_STATUS") {
            string statusStr;
            iss >> statusStr;
            bool status = (statusStr == "working");

            cout << "Searching pipes by status: " << (status ? "working" : "repair") << endl;
            unordered_set<int> results = findPipesByFixing(status);
            if (results.empty()) {
                cout << "No pipes found with status: " << (status ? "working" : "repair") << endl;
            }
            else {
                cout << "Found " << results.size() << " pipes:" << endl;
                for (int id : results) {
                    cout << "  ID: " << id << " - " << pipes[id].getName() << endl;
                }
            }

        }
        else if (command == "SEARCH_CS_BY_NAME") {
            string name;
            char quote;
            iss >> quote;
            getline(iss, name, '\"');

            cout << "Searching CS by name: " << name << endl;
            unordered_set<int> results = findCSByName(name);
            if (results.empty()) {
                cout << "No CS found with name containing: " << name << endl;
            }
            else {
                cout << "Found " << results.size() << " CS:" << endl;
                for (int id : results) {
                    cout << "  ID: " << id << " - " << stations[id].getName() << endl;
                }
            }

        }
        else if (command == "SEARCH_CS_BY_UNUSED") {
            float minPercent, maxPercent;
            iss >> minPercent >> maxPercent;

            cout << "Searching CS by unused percentage: " << minPercent << "-" << maxPercent << "%" << endl;
            unordered_set<int> results = findCSByUnusedPercentage(minPercent, maxPercent);
            if (results.empty()) {
                cout << "No CS found with unused percentage in range: " << minPercent << "-" << maxPercent << "%" << endl;
            }
            else {
                cout << "Found " << results.size() << " CS:" << endl;
                for (int id : results) {
                    float unusedPercent = stations[id].getUnusedPercentage();
                    cout << "  ID: " << id << " - " << stations[id].getName()
                        << " (" << unusedPercent << "% unused)" << endl;
                }
            }

        }
        else if (command == "VIEW_ALL_OBJECTS") {
            cout << "Viewing all objects:" << endl;
            viewAllObjectsForReplay();

        }
        else if (command == "SAVE_TO_FILE") {
            string saveFilename;
            char quote;
            iss >> quote;
            getline(iss, saveFilename, '\"');

            cout << "Saving data to: " << saveFilename << endl;
            saveToFile(saveFilename);
            }
        else if (command == "MENU_ACTION") {
            string menuAction;
            getline(iss >> ws, menuAction);
            cout << "Menu action: " << menuAction << endl;

        }
        else {
            cout << "Unknown command: " << command << endl;
        }
    }

    file.close();
    cout << "Replay completed! Pipes: " << pipes.size() << ", CS: " << stations.size() << "\n\n";
}


void PipelineSystem::loadFromFileForReplay(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int pipeCount;
        file >> pipeCount;
        for (int i = 0; i < pipeCount; i++) {
            int id;
            file >> id;

            if (pipes.count(id)) {
                cout << "Skip existing pipe ID " << id << endl;
                string temp;
                getline(file >> ws, temp);
                file >> temp >> temp >> temp;
                continue;
            }

            Pipe pipe(id);
            string name;
            getline(file >> ws, name);
            pipe.setName(name);

            float length, diameter;
            bool fixing;
            file >> length >> diameter >> fixing;
            pipe.setLength(length);
            pipe.setDiameter(diameter);
            pipe.setFixing(fixing);

            pipes.emplace(id, pipe);
            nextPipeId = max(nextPipeId, id + 1);
            cout << "Loaded pipe ID " << id << endl;
        }

        int csCount;
        file >> csCount;
        for (int i = 0; i < csCount; i++) {
            int id;
            file >> id;

            if (stations.count(id)) {
                cout << "Skip existing CS ID " << id << endl;
                string temp;
                getline(file >> ws, temp);
                file >> temp >> temp >> temp;
                continue;
            }

            CS cs(id);
            string name;
            getline(file >> ws, name);
            cs.setName(name);

            int workshop, activeWorkshop;
            float score;
            file >> workshop >> activeWorkshop >> score;
            cs.setWorkshop(workshop);
            cs.setActiveWorkshop(activeWorkshop);
            cs.setScore(score);

            stations.emplace(id, cs);
            nextCsId = max(nextCsId, id + 1);
            cout << "Loaded CS ID " << id << endl;
        }

        file.close();
        cout << "Data loaded from " << filename << " successfully!\n";
    }
    else {
        cout << "Error opening file for reading: " << filename << endl;
    }
}

void PipelineSystem::viewAllObjectsForReplay() {
    if (pipes.empty()) {
        cout << "No pipes available." << endl;
    }
    else {
        cout << "Pipes" << endl;
        for (const auto& pipe_pair : pipes) {
            cout << "ID: " << pipe_pair.second.getId()
                << " - " << pipe_pair.second.getName()
                << " (Status: " << (pipe_pair.second.getFixing() ? "working" : "repair") << ")" << endl;
        }
    }

    if (stations.empty()) {
        cout << "No compressor stations available." << endl;
    }
    else {
        cout << "Compressor stations" << endl;
        for (const auto& cs_pair : stations) {
            float unusedPercent = cs_pair.second.getUnusedPercentage();
            cout << "ID: " << cs_pair.second.getId()
                << " - " << cs_pair.second.getName()
                << " (Active: " << cs_pair.second.getActiveWorkshop()
                << "/" << cs_pair.second.getWorkshop()
                << ", Unused: " << unusedPercent << "%)" << endl;
        }
    }
    cout << endl;
}

void PipelineSystem::clearAllData() {
    pipes.clear();
    stations.clear();
    nextPipeId = 1;
    nextCsId = 1;
}