#ifndef BABY_H_
#define BABY_H_

#include <string>
#include <bitset>

class Baby
{
private:
    bool store[32][32] = {{false}};
    int storageCapacity = 32;
    std::string acc;
    std::string currentCmd;
    std::string presentCmd;
    std::string regFour;

public:
    Baby();
};

#endif