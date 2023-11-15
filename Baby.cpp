#include "baby.h"

using namespace std;

Baby::Baby()
{

    storeCapacity = 32;
    acc = "00000000000000000000000000000000";
    currentCmd = "00000000000000000000000000000000";
    presentCmd = "00000000000000000000000000000000";
    regFour = "00000000000000000000000000000000";

    for (int i =0;i<memorySize;i++) {
        for (int j=0;i<32;j++) {
            store[i][j] = 0;
        }
    }

}

Baby::~Baby()
{
    for (int i=0;i<memorySize;i++)
    {
        for(int j=0;j<32;j++) {
            store[i][j] = 0;
        }
    }

    storageCapacity = 0;
    acc = "";
    currentCmd = "";
    nextCmd = "";
    regFour = "";

    cout << "";
}

int binaryToDecimal(string binary)
{
    int decimal = 0;

    for (int i = 0; i < (binary.length()) - 1; i++) {
        if (binary[i] == '1') {
            decimal += pow(2, i);
        }
    } 

    return decimal;
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