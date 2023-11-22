#pragma once
#ifndef BABY_H_
#define BABY_H_

#include <string>
#include <bitset>

using namespace std;

class Baby
{
private:
    bool store[32][32] = { {false} };
    int storeCapacity = 32;
    string acc;
    string currentCmd;
    string nextCmd;
    string regFour;

public:
    int binaryToDecimal(string binary);
    int getCurrentCmdAddress();
    void incrementCurrentCmd();
    void fetch();
    int getOperand(int ln);
    int getOpCode(int ln);
    void printStore();

    Baby();
    ~Baby();
};

#endif
