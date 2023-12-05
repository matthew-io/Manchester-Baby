/*

AC21009 : Computer Systems 2A: Architecture Fundamentals and Unix
Manchester Baby Assignment

Matthew McConnachie
Jessio Rodrigues
Drew Webster

*/

using namespace std;
#include "baby.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>
#include <bitset>
#include <vector>
#include "Assembler.h"

// function to display menu options
void displayMenu()
{
    cout << "Choose an option:" << endl;
    cout << "[1] Load a text file containing instructions" << endl;
    cout << "[2] Load assembly file" << endl;
    cout << "[3] Quit" << endl;
}

void assembler();

int main()
{
    // initialise vairable
    char input = 'a';

    while (input != '1')
    {
        displayMenu();   

        cin >> input;

        // repeat until valid input is recieved
        while (input != '1' && input != '2' && input != '3')
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

        // if input is 2 run assembler
        if (input == '2')
        {
            assembler();
        }

        // if input is 3 quit
        if (input == '3')
        {
            return 0;
        }
    }

    // if input is 1 load a text file containing instructions
    Baby *baby = new Baby();

    string file_name;
    fstream test_data;

    cout << "Enter the name of the file you would like to load: " << endl;
    while (true) {
        cin >> file_name;

        test_data.open("./input/" + file_name, ios::in);

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
    char choice;

    cout << "Enter 'y' to have all instructions executed immediately, or 'n' to run them one at a time." << endl;
    cin >> choice;

    do {
        if (choice != 'y' && choice != 'n') {
            cout << "Invalid key, please try again." << endl;
            cin >> choice;
        }
    } while (choice != 'y' && choice != 'n');

    

    do {
        baby->incrementCI();
        baby->printStore();
        int code = baby->fetch(choice);

        if (code == 0)
        {
            baby->printStore();
            quit = true;
        }
    } while (quit == false);

    delete baby;
    return 0;
}

void assembler() {
    
        vector<string> fileContent{};
        SymbolTable symbolTable;
        VariableMap variableMap;
        map<string, string> instructionSet;
        InstructionSet instructions;
        instructionSet=instructions.instructions;
        string fileName;

        cout << "Enter file name: ";

        cin >> fileName;

        try {

            newFile(fileName, fileContent);

            convertAssembly(fileContent, symbolTable, variableMap, instructionSet);

        } catch (const exception& e) {

            cout <<"Error occurred: "<< e.what() << endl;

        }
 }