#include <string>
#include <cmath>

using namespace std;

// function that recieves a decimal value and converts it to a binary value
string decimalToBinary(int decimal)
{
    if (decimal == 0) 
    {
        return "0";
    }

    std::string binary = "";
    bool isNegative = decimal < 0;
    
    // remove '-' sign from number if negative
    if (isNegative)
    {
        decimal = -decimal;
    }

    while (decimal > 0)
    {
        binary = std::to_string(decimal % 2) + binary;
        decimal /= 2;
    }

    while (binary.length() < 32)
    {
        binary = "0" + binary;
    }

    // if decimal value is negative
    if (isNegative)
    {
        for (char &bit : binary)
        {
            bit = (bit == '0') ? '1' : '0';
        }

        bool carry = true;
        for (int i = binary.length() - 1; i >= 0 && carry; --i)
        {
            if (binary[i] == '0')
            {
                binary[i] = '1';
                carry = false;
            }
            else
            {
        binary[i] = '0';
            }
        }
    }

    return binary;
}

int invertAndAddOne(string binary) {
    for (char &bit : binary) {
        bit = (bit == '0') ? '1' : '0';
    }

    int carry = 1;
    for (int i = 0; i < binary.length(); i++) {
        if (binary[i] == '1' && carry == 1) {
            binary[i] = '0';
        } else if (carry == 1) {
            binary[i] = '1';
            carry = 0;
        }
    }

    int decimal = 0;
    for (int i = 0; i < binary.length(); i++) {
        if (binary[i] == '1') {
            decimal += pow(2, i);
        }
    }

    return -decimal;
}

// function that recieves a positive binary value and converts it to a decimal value
int positiveBinaryToDecimal(const string binary) {
    int decimal = 0;
    for (int i = 0; i < binary.length(); i++) {
        if (binary[i] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}


// function that recieves a binary value and converts it to a decimal value
int binaryToDecimal(string binary) {
    if (binary[binary.length() - 1] == '0' || binary.length() < 32) {
        return positiveBinaryToDecimal(binary);
    } else {
        return invertAndAddOne(binary);
    }
}
