#include <iostream>
#include "binary.h"
#include <string>
#include <cmath>
#include <bitset>
#include <sstream>
#include "baby.h"
#include <stdlib.h>

const std::string RED_TEXT = "\033[31m";
const std::string GREEN_TEXT = "\033[32m";
const std::string RESET_COLOR = "\033[0m";

// constructor
Baby::Baby()
{
    for (int i=0;i<SIZE;i++)
    {
        accumulator += "0";
        ci += "0";
        pi += "0";
        for (int j=0;j<SIZE;j++)
        {
            store[i][j] = 0;
        }
    }
}

// deconstructor
Baby::~Baby()
{
}

// function to incriement control instruction
void Baby::incrementCI()
{
    bool carry = true;
    // increase binary number by one
    for (int i = 0; i < ci.length() && carry; i++)
    {
        if (ci[i] == '0')
        {
            ci[i] = '1';
            carry = false;
        }
        else
        {
            ci[i] = '0';
        }
    }
}

// function to fetch decode and executre
int Baby::fetch(char choice)
{
    // fetch
    int lineNumber = binaryToDecimal(ci);
    pi = getLineFromStore(lineNumber);

    // decode
	int opcode = getOpcode();

    // execute
    // if statements for each possible opcode
    if (opcode == 0)
    {
        cout << "INSTRUCTION: JMP" << endl;
        if (choice == 'y')
        {
            JMP();
            return 1;
        } else {
            if (continueRun() == 1) {
                JMP();
                return 1;
            } else {
                return 0;
            }
        }
    };
    if (opcode == 1)
    {
        cout << "INSTRUCTION: JRP" << endl;
        if (choice == 'y')
        {
            JRP();
            return 1;
        } else {
            if (continueRun() == 1) {
                JRP();
                return 1;
            } else {
                return 0;
            }
        }
        
    }
    if (opcode == 2)
    {
        cout << "INSTRUCTION: LDN" << endl;
        if (choice == 'y')
        {
            LDN();
            return 1;
        } else {
            if (continueRun() == 1) {
                LDN();
                return 1;
            } else {
                return 0;
            }    
        }
    };
    if (opcode == 3)
    {
        cout << "INSTRUCTION: STO" << endl;
         if (choice == 'y'){
            STO();
            return 1;
        } else {
            if (continueRun() == 1) {
                STO();
                return 1;
            } else {
                return 0;
            }
        }
    };
    if (opcode ==4)
    {
        cout << "INSTRUCTION: SUB" << endl;
        if (choice == 'y')
        {
            SUB();
            return 1;
        } else {
            if (continueRun() == 1) {
                SUB();
                return 1;
            } else {
                return 0;
            }
        }
    }

    if (opcode == 5)
    {
        cout << "INSTRUCTION: SUB" << endl;
        if (choice == 'y')
        {
            SUB();
            return 1;
        } else {
            if (continueRun() == 1) {
                SUB();
                return 1;
            } else {
                return 0;
            }
        }
    }
    if (opcode == 6)
    {
        cout << "INSTRUCTION: CMP" << endl;
        
        if (choice == 'y')
        {
            CMP();
            return 1;
        } else {
            if (continueRun() == 1) {
                CMP();
                return 1;
            } else {
                return 0;
            }
        }
    }
    
    // if 7 stop
    if (opcode == 7)
    {
        return 0;
    }
}

// function that gets user input to keep program running or end it
int Baby::continueRun()
{
    char choice;
    
    cout << endl;
    cout << "Press 'c' to continue executing the program. Press 'x' to stop the run." << endl;
    cin >> choice;

    do {
        if (choice != 'c' && choice != 'x')
        {
            cout << "Invalid key. Please try again." << endl;
            cin >> choice; 
        }
        if (choice == 'c') {
            return 1;
        }
    } while (choice != 'x');
    
    return 0;
}

// function to print state of store and other variables
void Baby::printStore()
{
    for (int i=0;i<SIZE;i++)
    {
        cout << (i+1);
        i < 9 ? cout << "    " : cout << "   ";
        for (int j=0;j<SIZE;j++) 
        {
            cout << store[i][j];
        }
        cout << endl;
	}

    int opcode = getOpcode();
    int operand = getOperand();
    
    cout << endl;
    opcode == 7 ? cout << "STOP LIGHT: " << GREEN_TEXT << "ON" << RESET_COLOR << endl :
    cout << "STOP LIGHT: " << RED_TEXT << "OFF" << RESET_COLOR << endl;
    cout << endl;
	cout << "ACCUMULATOR: " << accumulator << " | " << binaryToDecimal(accumulator) << endl;
    cout << "OPERAND: " << operand << endl;
	cout << "OPCODE: " << opcode << endl;
    opcode == 7 ? cout << endl << "Exiting the program..." << endl : cout << "";
}

// function to add instruction to store
void Baby::addInstructionToStore(int lineNumber, string instruction)
{
    for(int i=0;i<32;i++)
    {
        instruction[i] == '0' ? store[lineNumber][i] = 0 : store[lineNumber][i] = 1;
    }
}

// function to get opcode
int Baby::getOpcode()
{
    string opCode = "";

    for (int i=13;i<16;i++)
    {
        opCode += pi[i];
    }

    return binaryToDecimal(opCode);
}

int Baby::getOperand()
{
    string operand = "";

    // recieve the binary value of the first 5 digits of the pi
    for (int i=0;i<5;i++)
    {
        operand += pi[i];
    }

    // conver this binary value to a decimal value
    return binaryToDecimal(operand);
}

// function to get line from store
string Baby::getLineFromStore(int lineNumber) 
{
    bitset<32> lineBits;
    for (int i = 0; i < 32; i++)
    {
        lineBits[31 - i] = store[lineNumber][i];
    }
    stringstream ss;
    ss << lineBits;
    return ss.str();
}

// CMP incremt CI if accumulator value is negative, otherwise do nothing
void Baby::CMP()
{
    if (accumulator[31] == '1')
    {
        bool carry = true;
        for (int i = 0; i < ci.length() && carry; i++) {
            if (ci[i] == '0') {
                ci[i] = '1';
                carry = false;
            } else {
                ci[i] = '0';
            }
        }
    }
}

// JRP add content of store location to CI
void Baby::JRP() {
    int operand = getOperand(), ciValue = binaryToDecimal(ci);
    ciValue += operand;
    ci = decimalToBinary(ciValue);
    ci = string(32 - ci.length(), '0') + ci;
}

// LDN load accumulator with negative form of store content
void Baby::LDN()
{
	int lineNumber = getOperand();
	string binaryValue = getLineFromStore(lineNumber);

	int negativeDecimalValue = -binaryToDecimal(binaryValue);
	
	string negativeBinary = decimalToBinary(negativeDecimalValue);

	for (int i=0; i<negativeBinary.length(); i++)
	{
        negativeBinary[i] == '0' ? accumulator[31 - i] = '0' : accumulator[31 - i] = '1';
	}
}

// JMP set CI to content of store location
void Baby::JMP()
{
    int operand = getOperand();
    ci = getLineFromStore(operand);
}  

// SUB subrtract content of store location from accumulator
int Baby::SUB()
{
	int lineNumber = getOperand();
	string binaryValue = getLineFromStore(lineNumber);
	int result = binaryToDecimal(accumulator) - binaryToDecimal(binaryValue);

	string binary = decimalToBinary(result);

	for (int i=0; i<binary.length(); i++)
	{
        binary[i] == '0' ? accumulator[31 - i] = '0' : accumulator[31 - i] = '1';
	}

	return 1;
}

// STO copy accumulator to store location
void Baby::STO()
{
    int line = getOperand();
    
    for (int i = 0; i < SIZE; i++)
    {
        store[line][i] = (accumulator[i] == '0') ? 0 : 1;
    }
}

