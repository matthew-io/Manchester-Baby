using namespace std;
#include "baby.h"
#include <iostream>
#include <string>

int main()
{
    string binary = "0001";
    int decimal = binaryToDecimal(binary);
    cout << decimal;
    Baby *baby = new Baby();
    baby->printStore();

    // delete baby;
    return 0;
}