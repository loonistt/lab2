#include "pipecsfunctions.h"
#include "logcheckshow.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Pipe* PipelineSystem::findPipeById(int id) {
    for (auto& pipe : pipes) {
        if (pipe.id == id) {
            return &pipe;
        }
    }
    return nullptr;
}

CS* PipelineSystem::findCSById(int id) {
    for (auto& cs : stations) {
        if (cs.id == id) {
            return &cs;
        }
    }
    return nullptr;
}

void PipelineSystem::addPipe() {
    Pipe pipe(nextPipeId++);
    addPipeData(pipe);
    pipes.push_back(pipe);
    cout << "New pipe added successfully! ID: " << pipe.id << "\n\n";
    logAction("Added pipe with ID: " + to_string(pipe.id));
}

void PipelineSystem::addCS() {
    CS cs(nextCsId++);
    addCsData(cs);
    stations.push_back(cs);
    cout << "New compressor station added successfully! ID: " << cs.id << "\n\n";
    logAction("Added CS with ID: " + to_string(cs.id));
}

void PipelineSystem::viewAllObjects() {
    if (pipes.empty()) {
        cout << "No pipes available.\n\n";
    }
    else {
        for (const auto& pipe : pipes) {
            cout << pipe;
        }
    }

    if (stations.empty()) {
        cout << "No compressor stations available.\n\n";
    }
    else {
        for (const auto& cs : stations) {
            cout << cs;
        }
    }
}

void PipelineSystem::editPipe() {
    int id;
    cout << "Enter pipe ID to edit: ";
    cin >> id;

    Pipe* pipe = findPipeById(id);
    if (pipe) {
        editPipeData(*pipe);
        cout << "Pipe edited successfully!\n\n";
        logAction("Edited pipe with ID: " + to_string(id));
    }
    else {
        cout << "Pipe with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::editCS() {
    int id;
    cout << "Enter compressor station ID to edit: ";
    cin >> id;

    CS* cs = findCSById(id);
    if (cs) {
        editCsData(*cs);
        cout << "Compressor station edited successfully!\n\n";
        logAction("Edited CS with ID: " + to_string(id));
    }
    else {
        cout << "Compressor station with ID " << id << " not found.\n\n";
    }
}

vector<int> PipelineSystem::findPipesByName(const string& name) {
    vector<int> result;
    for (const auto& pipe : pipes) {
        if (pipe.name.find(name) != string::npos) {
            result.push_back(pipe.id);
        }
    }
    return result;
}

vector<int> PipelineSystem::findPipesByFixing(bool fixing) {
    vector<int> result;
    for (const auto& pipe : pipes) {
        if (pipe.fixing == fixing) {
            result.push_back(pipe.id);
        }
    }
    return result;
}

vector<int> PipelineSystem::findCSByName(const string& name) {
    vector<int> result;
    for (const auto& cs : stations) {
        if (cs.name.find(name) != string::npos) {
            result.push_back(cs.id);
        }
    }
    return result;
}

vector<int> PipelineSystem::findCSByUnusedPercentage(float minPercent, float maxPercent) {
    vector<int> result;
    for (const auto& cs : stations) {
        float unusedPercent = ((cs.workshop - cs.ActiveWorkshop) * 100.0f) / cs.workshop;
        if (unusedPercent >= minPercent && unusedPercent <= maxPercent) {
            result.push_back(cs.id);
        }
    }
    return result;
}

void PipelineSystem::batchEditPipes(const vector<int>& pipeIds) {
    if (pipeIds.empty()) {
        cout << "No pipes to edit.\n\n";
        return;
    }

    cout << "Selected pipes for batch editing:\n";
    for (int id : pipeIds) {
        Pipe* pipe = findPipeById(id);
        if (pipe) {
            cout << "ID: " << id << " - " << pipe->name << endl;
        }
    }

    cout << "Edit all pipes? (1 - yes, 0 - select specific): ";
    int choice;
    cin >> choice;

    vector<int> pipesToEdit;
    if (choice == 1) {
        pipesToEdit = pipeIds;
    }
    else {
        cout << "Enter pipe IDs to edit (one per line, -1 to finish): ";
        int id;
        while (cin >> id && id != -1) {
            if (find(pipeIds.begin(), pipeIds.end(), id) != pipeIds.end()) {
                pipesToEdit.push_back(id);
            }
            else {
                cout << "ID " << id << " not in search results.\n";
            }
        }
    }

    for (int id : pipesToEdit) {
        Pipe* pipe = findPipeById(id);
        if (pipe) {
            editPipeData(*pipe);
            logAction("Batch edited pipe with ID: " + to_string(id));
        }
    }
    cout << "Batch editing completed!\n\n";
}

void PipelineSystem::deletePipe() {
    int id;
    cout << "Enter pipe ID to delete: ";
    cin >> id;

    auto it = remove_if(pipes.begin(), pipes.end(),
        [id](const Pipe& pipe) { return pipe.id == id; });

    if (it != pipes.end()) {
        pipes.erase(it, pipes.end());
        cout << "Pipe deleted successfully!\n\n";
        logAction("Deleted pipe with ID: " + to_string(id));
    }
    else {
        cout << "Pipe with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::deleteCS() {
    int id;
    cout << "Enter compressor station ID to delete: ";
    cin >> id;

    auto it = remove_if(stations.begin(), stations.end(),
        [id](const CS& cs) { return cs.id == id; });

    if (it != stations.end()) {
        stations.erase(it, stations.end());
        cout << "Compressor station deleted successfully!\n\n";
        logAction("Deleted CS with ID: " + to_string(id));
    }
    else {
        cout << "Compressor station with ID " << id << " not found.\n\n";
    }
}

void PipelineSystem::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << pipes.size() << "\n";
        for (const auto& pipe : pipes) {
            file << pipe.id << "\n" << pipe.name << "\n" << pipe.length << "\n"
                << pipe.diameter << "\n" << pipe.fixing << "\n";
        }

        file << stations.size() << "\n";
        for (const auto& cs : stations) {
            file << cs.id << "\n" << cs.name << "\n" << cs.workshop << "\n"
                << cs.ActiveWorkshop << "\n" << cs.score << "\n";
        }

        file.close();
        cout << "Data saved to " << filename << " successfully!\n\n";
        logAction("Saved data to file: " + filename);
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
            getline(file >> ws, pipe.name);
            file >> pipe.length >> pipe.diameter >> pipe.fixing;
            pipes.push_back(pipe);
            nextPipeId = max(nextPipeId, id + 1);
        }

        int csCount;
        file >> csCount;
        for (int i = 0; i < csCount; i++) {
            int id;
            file >> id;
            CS cs(id);
            getline(file >> ws, cs.name);
            file >> cs.workshop >> cs.ActiveWorkshop >> cs.score;
            stations.push_back(cs);
            nextCsId = max(nextCsId, id + 1);
        }

        file.close();
        cout << "Data loaded from " << filename << " successfully!\n\n";
        logAction("Loaded data from file: " + filename);
    }
    else {
        cout << "Error opening file for reading.\n\n";
    }
}

void PipelineSystem::searchPipesMenu() {
    cout << "Search pipes:\n";
    cout << "1. By name\n";
    cout << "2. By repair status\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    vector<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);
        results = findPipesByName(name);
    }
    else if (choice == 2) {
        int status;
        cout << "Enter status (0 - in repair, 1 - working): ";
        cin >> status;
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
            cout << "Pipe ID: " << id << endl;
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

    vector<int> results;
    if (choice == 1) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);
        results = findCSByName(name);
    }
    else if (choice == 2) {
        float minPercent, maxPercent;
        cout << "Enter minimum unused percentage: ";
        cin >> minPercent;
        cout << "Enter maximum unused percentage: ";
        cin >> maxPercent;
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
            cout << "CS ID: " << id << endl;
        }
        cout << endl;
    }
}

