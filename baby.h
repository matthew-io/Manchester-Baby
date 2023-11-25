<<<<<<< HEAD
=======
#pragma once
#ifndef BABY_H_
#define BABY_H_

>>>>>>> 8f0054484bef2b19d4ef37fdc8c89fde42c23a5d
#include <string>

using namespace std;

<<<<<<< HEAD
#define SIZE 32

class Baby{
    private: 
    
        int storeSize;
        string accumulator;
        bool store[SIZE][SIZE];
        string ci;
        string pi;
=======
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
>>>>>>> 8f0054484bef2b19d4ef37fdc8c89fde42c23a5d

    public:

<<<<<<< HEAD
        void printState();
        void addInstructionToStore(int lineNumber, string instruction);
        int getOpcode();
        int getOperand();
        void incrementCI();
        int fetch();
        string getLineFromStore(int operand);
        string negateBinary(const string& binaryValue);
        int decode();

        void JMP();
        void JRP();
        void LDN();
        void STO();
        int SUB();
        void CMP();

        Baby();
        ~Baby();
};
=======
#endif
>>>>>>> 8f0054484bef2b19d4ef37fdc8c89fde42c23a5d
