#ifndef BABY_H_
#define BABY_H_

#include <string>
#include <bitset>

int binaryToDecimal(const std::string binary);
int getCurrentCmdAddress();

class Baby
{
private:
    bool store[32][32] = {{false}};
    int storeCapacity = 32;
    std::string acc;
    std::string currentCmd;
    std::string nextCmd;
    std::string regFour;

public:
    int binaryToDecimal(const std::string binary);
    int getCurrentCmdAddress();
    void incrementCurrentCmd() 
    void fetch() 
    int getOperand() 
    int getOpCode() 

    Baby();
    ~Baby();
};

#endif