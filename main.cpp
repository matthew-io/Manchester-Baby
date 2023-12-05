using namespace std;
#include "baby.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// function to display menu options
void displayMenu()
{
    cout << "Choose an option:" << endl;
    cout << "[1] Load a text file containing instructions" << endl;
    cout << "[2] Quit" << endl;
}


int main()
{
    // initialise vairable
    char input = 'a';

    while (input != '1')
    {
        displayMenu();   

        cin >> input;

        // repeat until valid input is recieved
        while (input != '1' && input != '2')
        {
            cout << "Invalid input, please enter a valid option" << endl;
            displayMenu();

            if (!cin)
            {
                cin.clear();
                cin.ignore();
            }

            cin >> input;
        }

        // if input is 2 quit
        if (input == '2')
        {
            return 0;
        }
    }

    // if input is 1 load a text file containing instructions
    Baby *baby = new Baby();

    string file_name;
    fstream test_data;

    cout << "Enter the name of the file you would like to add: " << endl;
    while (true) {
        cin >> file_name;

        test_data.open("/input/" + file_name, ios::in);

        if (test_data.is_open()) {
            string data;
            int lineNumber = 0;
            while (getline(test_data, data)) {
                baby->addInstructionToStore(lineNumber, data);
                lineNumber++;
            }
            test_data.close();
            break; // if able to open file break from loop
        } else { // else repeat until valid input is recieved
            cout << "Unable to open file. Please try again: " << endl;
            test_data.clear();
        }
    }

    bool quit = false;

    do {
        baby->incrementCI();
        baby->printState();
        int code = baby->fetch();

        if (code == 0)
        {
            baby->printState();
            quit = true;
        }
    } while (quit == false);

    delete baby;
    return 0;
}
