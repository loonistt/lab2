#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <algorithm>
using namespace std;


void logAction(const string& action) {
    ofstream logfile("log.txt", ios::app);
    if (logfile.is_open()) {
        logfile << action << endl;
    }
    logfile.close();
}

struct Pipe {
    int id;
    string name;
    float length;
    float diameter;
    bool fixing = false;

    Pipe() : id(0) {}
    Pipe(int new_id) : id(new_id) {}
};

struct CS {
    int id;
    string name;
    int workshop;
    int ActiveWorkshop;
    float score;

    CS() : id(0) {}
    CS(int new_id) : id(new_id) {}
};


ostream& operator << (ostream& out, const Pipe& pipe) {
    out << "Pipe ID: " << pipe.id << "\n"
        << "Name: " << pipe.name << "\n"
        << "Length: " << pipe.length << "m\n"
        << "Diameter: " << pipe.diameter << "mm\n"
        << "Status: " << (pipe.fixing ? "Working" : "In repair") << "\n\n";
    return out;
}

ostream& operator << (ostream& out, const CS& cs) {
    float unusedPercent = ((cs.workshop - cs.ActiveWorkshop) * 100.0f) / cs.workshop;
    out << "CS ID: " << cs.id << "\n"
        << "Name: " << cs.name << "\n"
        << "Workshops: " << cs.workshop << " (active: " << cs.ActiveWorkshop << ")\n"
        << "Unused workshops: " << unusedPercent << "%\n"
        << "Score: " << cs.score << "\n\n";
    return out;
}

class PipelineSystem {
private:
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> stations;
    int nextPipeId = 1;
    int nextCsId = 1;

public:
    
    void addPipe() {
        Pipe pipe(nextPipeId++);
        addPipeData(pipe);
        pipes[pipe.id] = pipe;
        cout << "New pipe added successfully! ID: " << pipe.id << "\n\n";
        logAction("Added pipe with ID: " + to_string(pipe.id));
    }

    void addCS() {
        CS cs(nextCsId++);
        addCsData(cs);
        stations[cs.id] = cs;
        cout << "New compressor station added successfully! ID: " << cs.id << "\n\n";
        logAction("Added CS with ID: " + to_string(cs.id));
    }

    
    void viewAllObjects() {
        if (pipes.empty()) {
            cout << "No pipes available.\n\n";
        }
        else {
            for (const auto& pipe_pair : pipes) {
                cout << pipe_pair.second;
            }
        }

        if (stations.empty()) {
            cout << "No compressor stations available.\n\n";
        }
        else {
            for (const auto& cs_pair : stations) {
                cout << cs_pair.second;
            }
        }
    }

    
    void editPipe() {
        int id;
        cout << "Enter pipe ID to edit: ";
        cin >> id;

        if (pipes.count(id)) {
            editPipeData(pipes[id]);
            cout << "Pipe edited successfully!\n\n";
            logAction("Edited pipe with ID: " + to_string(id));
        }
        else {
            cout << "Pipe with ID " << id << " not found.\n\n";
        }
    }

    void editCS() {
        int id;
        cout << "Enter compressor station ID to edit: ";
        cin >> id;

        if (stations.count(id)) {
            editCsData(stations[id]);
            cout << "Compressor station edited successfully!\n\n";
            logAction("Edited CS with ID: " + to_string(id));
        }
        else {
            cout << "Compressor station with ID " << id << " not found.\n\n";
        }
    }

    
    vector<int> findPipesByName(const string& name) {
        vector<int> result;
        for (const auto& pipe_pair : pipes) {
            if (pipe_pair.second.name.find(name) != string::npos) {
                result.push_back(pipe_pair.first);
            }
        }
        return result;
    }

    vector<int> findPipesByFixing(bool fixing) {
        vector<int> result;
        for (const auto& pipe_pair : pipes) {
            if (pipe_pair.second.fixing == fixing) {
                result.push_back(pipe_pair.first);
            }
        }
        return result;
    }

   
    vector<int> findCSByName(const string& name) {
        vector<int> result;
        for (const auto& cs_pair : stations) {
            if (cs_pair.second.name.find(name) != string::npos) {
                result.push_back(cs_pair.first);
            }
        }
        return result;
    }

    vector<int> findCSByUnusedPercentage(float minPercent, float maxPercent) {
        vector<int> result;
        for (const auto& cs_pair : stations) {
            const CS& cs = cs_pair.second;
            float unusedPercent = ((cs.workshop - cs.ActiveWorkshop) * 100.0f) / cs.workshop;
            if (unusedPercent >= minPercent && unusedPercent <= maxPercent) {
                result.push_back(cs_pair.first);
            }
        }
        return result;
    }

    
    void batchEditPipes(const vector<int>& pipeIds) {
        if (pipeIds.empty()) {
            cout << "No pipes to edit.\n\n";
            return;
        }

        cout << "Selected pipes for batch editing:\n";
        for (int id : pipeIds) {
            if (pipes.count(id)) {
                cout << "ID: " << id << " - " << pipes[id].name << endl;
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
            editPipeData(pipes[id]);
            logAction("Batch edited pipe with ID: " + to_string(id));
        }
        cout << "Batch editing completed!\n\n";
    }

    
    void deletePipe() {
        int id;
        cout << "Enter pipe ID to delete: ";
        cin >> id;

        if (pipes.erase(id)) {
            cout << "Pipe deleted successfully!\n\n";
            logAction("Deleted pipe with ID: " + to_string(id));
        }
        else {
            cout << "Pipe with ID " << id << " not found.\n\n";
        }
    }

    void deleteCS() {
        int id;
        cout << "Enter compressor station ID to delete: ";
        cin >> id;

        if (stations.erase(id)) {
            cout << "Compressor station deleted successfully!\n\n";
            logAction("Deleted CS with ID: " + to_string(id));
        }
        else {
            cout << "Compressor station with ID " << id << " not found.\n\n";
        }
    }

    
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            
            file << pipes.size() << "\n";
            for (const auto& pipe_pair : pipes) {
                const Pipe& pipe = pipe_pair.second;
                file << pipe.id << "\n" << pipe.name << "\n" << pipe.length << "\n"
                    << pipe.diameter << "\n" << pipe.fixing << "\n";
            }

            
            file << stations.size() << "\n";
            for (const auto& cs_pair : stations) {
                const CS& cs = cs_pair.second;
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

    void loadFromFile(const string& filename) {
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
                pipes[id] = pipe;
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
                stations[id] = cs;
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

private:
    
    void addPipeData(Pipe& pipe) {
        cout << "Enter name of the pipe: ";
        getline(cin >> ws, pipe.name);

        while (true) {
            cout << "Enter pipe length (in meters): ";
            cin >> pipe.length;
            if (checkCinError() || pipe.length <= 0 || pipe.length > 50) {
                cout << "Length must be between 0 and 50 meters.\n";
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter pipe diameter (in millimeters): ";
            cin >> pipe.diameter;
            if (checkCinError() || pipe.diameter <= 0 || pipe.diameter > 2500) {
                cout << "Diameter must be between 0 and 2500 millimeters.\n";
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Choose pipe status (0 - in repair, 1 - working): ";
            cin >> pipe.fixing;
            if (checkCinError()) continue;
            break;
        }
    }

    void addCsData(CS& cs) {
        cout << "Enter name of the compressor station: ";
        getline(cin >> ws, cs.name);

        while (true) {
            cout << "Enter the number of workshops: ";
            cin >> cs.workshop;
            if (checkCinError() || cs.workshop <= 0 || cs.workshop > 50) {
                cout << "Number of workshops must be between 1 and 50.\n";
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the number of active workshops: ";
            cin >> cs.ActiveWorkshop;
            if (checkCinError() || cs.ActiveWorkshop < 0 || cs.ActiveWorkshop > cs.workshop) {
                cout << "Active workshops must be between 0 and " << cs.workshop << ".\n";
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the compressor station score (0-10): ";
            cin >> cs.score;
            if (checkCinError() || cs.score < 0 || cs.score > 10) {
                cout << "Score must be between 0 and 10.\n";
            }
            else {
                break;
            }
        }
    }

    void editPipeData(Pipe& pipe) {
        while (true) {
            cout << "Enter new pipe status (0 - in repair, 1 - working): ";
            cin >> pipe.fixing;
            if (checkCinError()) continue;
            break;
        }
    }

    void editCsData(CS& cs) {
        while (true) {
            cout << "Enter new value of active workshops: ";
            cin >> cs.ActiveWorkshop;
            if (checkCinError() || cs.ActiveWorkshop < 0 || cs.ActiveWorkshop > cs.workshop) {
                cout << "Active workshops must be between 0 and " << cs.workshop << ".\n";
            }
            else {
                break;
            }
        }
    }

    bool checkCinError() {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error, incorrect value.\n";
            return true;
        }
        return false;
    }
};

void showMenu() {
    cout << "Pipelines and Compressor Stations Management System\n\n";
    cout << "Menu:\n";
    cout << "1. Add a pipe\n";
    cout << "2. Add a compressor station\n";
    cout << "3. View all objects\n";
    cout << "4. Edit a pipe\n";
    cout << "5. Edit a compressor station\n";
    cout << "6. Delete a pipe\n";
    cout << "7. Delete a compressor station\n";
    cout << "8. Search pipes\n";
    cout << "9. Search compressor stations\n";
    cout << "10. Batch edit pipes\n";
    cout << "11. Save to file\n";
    cout << "12. Load from file\n";
    cout << "0. Exit\n\n";
    cout << "Please select an action: ";
}

void searchPipesMenu(PipelineSystem& system) {
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
        results = system.findPipesByName(name);
    }
    else if (choice == 2) {
        int status;
        cout << "Enter status (0 - in repair, 1 - working): ";
        cin >> status;
        results = system.findPipesByFixing(status == 1);
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

void searchCSMenu(PipelineSystem& system) {
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
        results = system.findCSByName(name);
    }
    else if (choice == 2) {
        float minPercent, maxPercent;
        cout << "Enter minimum unused percentage: ";
        cin >> minPercent;
        cout << "Enter maximum unused percentage: ";
        cin >> maxPercent;
        results = system.findCSByUnusedPercentage(minPercent, maxPercent);
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

int main() {
    PipelineSystem system;

    while (true) {
        showMenu();
        int action;
        cin >> action;

        if (cin.fail() || action < 0 || action > 12) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error, incorrect value.\n\n";
            continue;
        }

        switch (action) {
        case 0:
            return 0;
        case 1:
            system.addPipe();
            break;
        case 2:
            system.addCS();
            break;
        case 3:
            system.viewAllObjects();
            break;
        case 4:
            system.editPipe();
            break;
        case 5:
            system.editCS();
            break;
        case 6:
            system.deletePipe();
            break;
        case 7:
            system.deleteCS();
            break;
        case 8:
            searchPipesMenu(system);
            break;
        case 9:
            searchCSMenu(system);
            break;
        case 10: {
            string name;
            cout << "Enter pipe name for batch editing: ";
            getline(cin >> ws, name);
            vector<int> results = system.findPipesByName(name);
            system.batchEditPipes(results);
            break;
        }
        case 11: {
            string filename;
            cout << "Enter filename to save: ";
            getline(cin >> ws, filename);
            system.saveToFile(filename);
            break;
        }
        case 12: {
            string filename;
            cout << "Enter filename to load: ";
            getline(cin >> ws, filename);
            system.loadFromFile(filename);
            break;
        }
        }
    }

    return 0;
}