using namespace std;
#include "Baby.h"
#include <iostream>
#include <string>

int main()
{


    //string binary = "110";
    //int decimal = baby->binaryToDecimal(binary);
    //cout << decimal << endl;


    Baby* baby = new Baby(); // Assuming you've properly allocated memory for the Baby object

    // Initial value of currentCmd
    cout << "Initial Address: " << baby->getCurrentCmdAddress() << endl;

    // Increment and print multiple times
    for (int i = 0; i < 3; ++i) {
        baby->incrementCurrentCmd();
        cout << "After Increment " << i + 1 << ": " << baby->getCurrentCmdAddress() << endl;
    }

    delete baby; // Don't forget to free the allocated memory


    // delete baby;
    return 0;
}
