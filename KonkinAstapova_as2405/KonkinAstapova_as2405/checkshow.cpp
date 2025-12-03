#include "checkshow.h"
#include <fstream>
using namespace std;

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