#include "pipecsfunctions.h"
#include "checkshow.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
    ifstream input_file;
    streambuf* original_cin = nullptr;
    ofstream logfile;
    redirect_output_wrapper cerr_out(cerr);

    if (argc > 1) {
        REPLAY_MODE = true;
        input_file.open(argv[1]);
        if (!input_file.is_open()) {
            cerr << "Error: Cannot open log file: " << argv[1] << endl;
            return 1;
        }
        original_cin = cin.rdbuf();
        cin.rdbuf(input_file.rdbuf());
    }
    else {
        REPLAY_MODE = false;
        string time = std::format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now());
        string log_filename = "log_" + time + ".txt";

        logfile.open(log_filename);
        if (logfile.is_open()) {
            cerr_out.redirect(logfile);
        }
    }

    PipelineSystem system;

    while (true) {
        showMenu();

        int action;
        cout << "Select action (0-12): ";
        action = GetCorrectNumber<int>(0, 12);

        try {
            switch (action) {
            case 0:
                cout << "Exiting program..." << endl;
                if (original_cin) {
                    cin.rdbuf(original_cin);
                }
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
                INPUT_LINE(cin, name);
                unordered_set<int> results = system.findPipesByName(name);
                system.batchEditPipes(results);
                break;
            }

            case 11: {
                string filename;
                cout << "Enter filename to save DATA: ";
                INPUT_LINE(cin, filename);
                system.saveToFile(filename);
                break;
            }

            case 12: {
                string filename;
                cout << "Enter filename to load DATA: ";
                INPUT_LINE(cin, filename);
                system.loadFromFile(filename);
                break;
            }

            default:
                cout << "Invalid action. Please try again.\n\n";
                break;
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n\n";
        }
    }

    return 0;
}