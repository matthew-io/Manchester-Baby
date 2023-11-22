#include "baby.h"
#include <cmath>
#include  <string.h>
#include <iostream>

using namespace std;

Baby::Baby()
{
    storeCapacity = 32;
    acc = "00000000000000000000000000000000";
    currentCmd = "00000000000000000000000000000000";
    nextCmd = "00000000000000000000000000000000";
    regFour = "00000000000000000000000000000000";

    for (int i = 0; i < storeCapacity; i++) {
        for (int j = 0; j < 32; j++) {
            store[i][j] = 0;
        }
    }

}

Baby::~Baby()
{
    for (int i = 0; i < storeCapacity; i++)
    {
        for (int j = 0; j < 32; j++) {
            store[i][j] = 0;
        }
    }

    storeCapacity = 0;
    acc = "";
    currentCmd = "";
    nextCmd = "";
    regFour = "";

}

void Baby::printStore()
{
    for (int i = 0; i < storeCapacity; i++) {
        for (int j = 0; j < storeCapacity; j++) {
            cout << store[i][j];
        }
        cout << endl;
    }
}

int Baby::getCurrentCmdAddress()
{
    unsigned int decimal = 0;

    for (size_t i = currentCmd.length() - 1; i != SIZE_MAX; --i) {
        if (currentCmd[i] == '1') {
            decimal += static_cast<unsigned int>(pow(2, currentCmd.length() - 1 - i));
        }
    }

    return decimal;
}

void Baby::incrementCurrentCmd()
{
    int carry = 1; // Start with a carry of 1

    for (int i = currentCmd.size() - 1; i >= 0 && carry > 0; --i) {
        int sum = (currentCmd[i] - '0') + carry;
        currentCmd[i] = (sum % 2) + '0'; // Update the current bit
        carry = sum / 2; // Update the carry
    }

    // If there's still a carry after the loop, add a new leftmost bit
    if (carry > 0) {
        currentCmd = '1' + currentCmd;
    }
}


void Baby::fetch()
{
    bool halt = false;
    while (!halt)
    {
        // increment command
        incrementCurrentCmd();

        // fetch
        int lineNumber = getCurrentCmdAddress();

        // decode

        int oC = getOpCode(lineNumber);
        int op = getOperand(lineNumber);


        // execute
        switch (oC) {
        case 0: // set CI to content of Store location
            std::cout << "You chose option 1.\n";
            break;

        case 1: // add content of Store location to CI
            std::cout << "You chose option 1.\n";
            break;

        case 2: // load Accumulator with negative form of Store content
            std::cout << "You chose option 2.\n";
            break;

        case 3: // copy Accumlulator to Store location
            for (int i = 0; i < 32; i++)
            {
                store[op][i] = acc[i] - '0';
            }
            break;
        case 4: // subtract content of Store location from Accumulator
            std::cout << "You chose option 3.\n";
            break;

        case 5: // as for 4
            std::cout << "You chose option 3.\n";
            break;

        case 6: // if A<0 then CI = CI + 1 (increment CI if Acc = neg, otherwise nothing)
            std::cout << "You chose option 3.\n";
            break;

        case 7: // set Stop lamp and halt machine
            halt = true;
            break;

        default:
            std::cout << "Invalid choice.\n";
        }

        // display everything
        printStore();
    }
}

int Baby::getOperand(int lineNumber)
{
    string operand = "";

    for (int i = 0; i < 5; i++)
    {
        operand += to_string(store[lineNumber][i]);
    }

    int op = binaryToDecimal(operand);

    return op;;
}

int Baby::binaryToDecimal(string binary)
{
    int decimal = 0;

    for (int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2, i);
        }
    }

    return decimal;
}

int Baby::getOpCode(int lineNumber)
{
    string opCode = "";

    for (int i = 13; i < 16; i++)
    {
        opCode += to_string(store[lineNumber][i]);
    }

    int oC = binaryToDecimal(opCode);

    return oC;
}
