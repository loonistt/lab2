#include "pipecsfunctions.h"
#include "checkshow.h"
#include <iostream>
using namespace std;

int main() {
    PipelineSystem system;

    while (true) {
        showMenu();
        int action;
        cin >> action;

        if (cin.fail() || action < 0 || action > 14) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error, incorrect value.\n\n";
            continue;
        }

        switch (action) {
        case 0:
            system.logMenuAction("EXIT");
            return 0;
        case 1:
            system.logMenuAction("ADD_PIPE");
            system.addPipe();
            break;
        case 2:
            system.logMenuAction("ADD_CS");
            system.addCS();
            break;
        case 3:
            system.logMenuAction("VIEW_ALL_OBJECTS");
            system.viewAllObjects();
            break;
        case 4:
            system.logMenuAction("EDIT_PIPE");
            system.editPipe();
            break;
        case 5:
            system.logMenuAction("EDIT_CS");
            system.editCS();
            break;
        case 6:
            system.logMenuAction("DELETE_PIPE");
            system.deletePipe();
            break;
        case 7:
            system.logMenuAction("DELETE_CS");
            system.deleteCS();
            break;
        case 8:
            system.logMenuAction("SEARCH_PIPES_MENU");
            system.searchPipesMenu();
            break;
        case 9:
            system.logMenuAction("SEARCH_CS_MENU");
            system.searchCSMenu();
            break;
        case 10: {
            system.logMenuAction("BATCH_EDIT_PIPES");
            string name;
            cout << "Enter pipe name for batch editing: ";
            getline(cin >> ws, name);
            unordered_set<int> results = system.findPipesByName(name);
            system.batchEditPipes(results);
            break;
        }
        case 11: {
            system.logMenuAction("SAVE_DATA_TO_FILE");
            string filename;
            cout << "Enter filename to save data: ";
            getline(cin >> ws, filename);
            system.saveToFile(filename);
            break;
        }
        case 12: {
            system.logMenuAction("LOAD_DATA_FROM_FILE");
            string filename;
            cout << "Enter filename to load data: ";
            getline(cin >> ws, filename);
            system.loadFromFile(filename);
            break;
        }
        case 13: {
            system.logMenuAction("SAVE_ACTIONS_TO_FILE");
            string filename;
            cout << "Enter filename to save actions: ";
            getline(cin >> ws, filename);

            ifstream source("actions.log");
            ofstream dest(filename);
            if (source && dest) {
                dest << source.rdbuf();
                cout << "Actions saved to " << filename << " successfully!\n\n";
            }
            else {
                cout << "Error saving actions to file.\n\n";
            }
            break;
        }
        case 14: {
            system.logMenuAction("REPLAY_FROM_FILE");
            string filename;
            cout << "Enter actions filename to replay: ";
            getline(cin >> ws, filename);
            system.replayFromFile(filename);
            break;
        }
        }
    }

    return 0;
}