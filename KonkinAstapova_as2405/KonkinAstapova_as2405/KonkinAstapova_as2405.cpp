#include "pipecsfunctions.h"
#include "logcheckshow.h"
#include <iostream>
using namespace std;

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
            system.searchPipesMenu();
            break;
        case 9:
            system.searchCSMenu();
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