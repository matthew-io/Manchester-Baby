#include "baby.h"
#include <cmath>
#include <iostream>

using namespace std;

Baby::Baby()
{
    storeCapacity = 32;
    acc = "00000000000000000000000000000000";
    currentCmd = "00000000000000000000000000000000";
    nextCmd = "00000000000000000000000000000000";
    regFour = "00000000000000000000000000000000";

    for (int i =0;i<storeCapacity;i++) {
        for (int j=0;j<32;j++) {
            store[i][j] = 0;
        }
    }

}

Baby::~Baby()
{
    for (int i=0;i<storeCapacity;i++)
    {
        for(int j=0;j<32;j++) {
            store[i][j] = 0;
        }
    }

    storeCapacity = 0;
    acc = "";
    currentCmd = "";
    nextCmd = "";
    regFour = "";

}

int binaryToDecimal(string binary)
{
    int decimal = 0;

    for (int i=binary.length() - 1;i>=0;i--) {
        if (binary[i] == '1') {
            decimal += pow(2, i);
        }
    }

    return decimal;
}

void Baby::printStore()
{
    for (int i =0;i<storeCapacity;i++) {
        for (int j=0;j<storeCapacity;j++) {
            cout << store[i][j];
        }
        cout << endl;
    }
}

int getCurrentCmdAddress() 
{
}

void incrementCurrentCmd() 
{
}

void fetch() 
{
}

int getOperand() 
{
}

int getOpCode() 
{
}