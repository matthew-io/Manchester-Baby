using namespace std;
#include "baby.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    char input;
    int inputSize = 32;

    while (input != '1')
    {
        cout << "Choose an option:" << endl;
        cout << "[1] Load a text file containing instructions" << endl;
        cout << "[2] Quit" << endl;

        cin >> input;

        while (input != '1' && input != '2')
        {
            cout << "Invalid input, please enter a valid option" << endl;

            if (!cin)
            {
                cin.clear();
                cin.ignore();
            }

            cin >> input;
        }

        cin.clear();
        cin.ignore();

        if (input == '2')
        {
            return 0;
        }
    }

    Baby *baby = new Baby();

    // baby->addInstruction(2, "11100000000000100000000000000000");
    // baby->printStore();

    fstream test_data;
    test_data.open("testcode.txt", ios::in);
    if (test_data.is_open()) {
        string data;
        int lineNumber = 0;
        while (getline(test_data, data)) {
            baby->addInstructionToStore(lineNumber, data);
            lineNumber++;
        }
        test_data.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    bool stop = false;

    do {
        baby->incrementCI();
        int code = baby->fetch();

        baby->printState();

        if (code == 0)
        {
            stop = true;
        }
    } while (stop == false);

    delete baby;
    return 0;
}