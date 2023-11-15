using namespace std;
#include "baby.h"
#include <iostream>
#include <string>

int main()
{
    string binary = "0001";
    int decimal = binaryToDecimal(binary);
    cout << decimal;

    return 0;
}