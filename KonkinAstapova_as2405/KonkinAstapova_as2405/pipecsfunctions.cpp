#include "pipecsfunctions.h"
#include "logger.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;


void PipelineSystem::addPipe() {
    Pipe pipe;

    cin >> pipe;

    pipes.emplace(pipe.getId(), pipe);
    cout << "New pipe added successfully! ID: " << pipe.getId() << "\n\n";
}

void PipelineSystem::addCS() {
    CS cs;
    cin >> cs;
    stations.emplace(cs.getId(), cs);
    cout << "New compressor station added successfully! ID: " << cs.getId() << "\n\n";
}

void PipelineSystem::viewAllObjects() {
    if (pipes.empty()) {
        cout << "No pipes available.\n\n";
    }
    else {
        cout << "Pipes\n";
        for (const auto& pipe_pair : pipes) {
            cout << pipe_pair.second;
        }
    }

    if (stations.empty()) {
        cout << "No compressor stations available.\n\n";
    }
    else {
        cout << "Compressor Stations\n";
        for (const auto& cs_pair : stations) {
            cout << cs_pair.second;
        }
    }
}

void PipelineSystem::editPipe() {
    int id;
    cout << "Enter pipe ID to edit: ";
    id = GetCorrectNumber<int>(0, INT_MAX);

    if (pipes.count(id)) {
        pipes[id].editPipe();
        cout << "Pipe edited successfully!\n\n";
    }
    else {
        cout << "Pipe with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::editCS() {
    int id;
    cout << "Enter compressor station ID to edit: ";
    id = GetCorrectNumber<int>(0, INT_MAX);

    if (stations.count(id)) {
        stations[id].editCS();
        cout << "Compressor station edited successfully!\n\n";
    }
    else {
        cout << "Compressor station with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::deletePipe() {
    int id;
    cout << "Enter pipe ID to delete: ";
    id = GetCorrectNumber<int>(0, INT_MAX);

    if (pipes.count(id)) {
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
    id = GetCorrectNumber<int>(0, INT_MAX);

    if (stations.count(id)) {
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

    int choice = GetCorrectNumber<int>(1, 2);

    unordered_set<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        INPUT_LINE(cin, name);
        results = findPipesByName(name);
    }
    else if (choice == 2) {
        cout << "Enter status (0 - in repair, 1 - working): ";
        int status = GetCorrectNumber<int>(0, 1);
        results = findPipesByFixing(status == 1);
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

    int choice = GetCorrectNumber<int>(1, 2);

    unordered_set<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        INPUT_LINE(cin, name);
        results = findCSByName(name);
    }
    else if (choice == 2) {
        float minPercent, maxPercent;
        cout << "Enter minimum unused percentage: ";
        minPercent = GetCorrectNumber<float>(0, 100);
        cout << "Enter maximum unused percentage: ";
        maxPercent = GetCorrectNumber<float>(minPercent, 100);
        results = findCSByUnusedPercentage(minPercent, maxPercent);
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
    int choice = GetCorrectNumber<int>(0, 1); 

    unordered_set<int> pipesToEdit;
    if (choice == 1) {
        pipesToEdit = pipeIds;
    }
    else {
        cout << "Enter pipe IDs to edit (one per line, -1 to finish): ";
        int id;
        while (true) {
            id = GetCorrectNumber<int>(-1, INT_MAX); 
            if (id == -1) break;
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
            cout << "Enter status for pipe ID " << id << " (0 - in repair, 1 - working): ";
            bool newStatus = GetCorrectBool();
            pipeStatuses[id] = newStatus;
        }
    }

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
            Pipe pipe;

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
        }

        int csCount;
        file >> csCount;
        for (int i = 0; i < csCount; i++) {
            int id;
            file >> id;
            CS cs;

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
        }

        file.close();
        cout << "Data loaded from " << filename << " successfully!\n\n";
    }
    else {
        cout << "Error opening file for reading.\n\n";
    }
}

void PipelineSystem::clearAllData() {
    pipes.clear();
    stations.clear();
}