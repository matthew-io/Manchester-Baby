#include <iostream>
#include "binary.h"
#include <string>
#include <cmath>
#include <bitset>
#include "baby.h"
#include <stdlib.h>

const std::string RED_TEXT = "\033[31m";
const std::string GREEN_TEXT = "\033[32m";
const std::string RESET_COLOR = "\033[0m";

// constructor
Baby::Baby()
{
    storeSize = SIZE;
    accumulator = "00000000000000000000000000000000";
    ci = "00000000000000000000000000000000";
    pi = "00000000000000000000000000000000";

    for (int i=0;i<storeSize;i++)
    {
        for (int j=0;j<storeSize;j++)
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
int Baby::fetch()
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
        if (continueRun == 1) {
            JMP();
            return 1;
        } else {
            return 0;
        }
    };
    if (opcode == 1)
    {
        cout << "INSTRUCTION: JRP" << endl;
        if (continueRun == 1) {
            JRP();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 2)
    {
        cout << "INSTRUCTION: LDN" << endl;
        if (continueRun() == 1) {
            LDN();
            return 1;
        } else {
            return 0;
        }
    };
    if (opcode == 3)
    {
        cout << "INSTRUCTION: STO" << endl;
        if (continueRun() == 1) {
            STO();
            return 1;
        } else {
            return 0;
        }
    };
    if (opcode ==4)
    {
        cout << "INSTRUCTION: SUB" << endl;
        if (continueRun() == 1) {
            SUB();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 5)
    {
        cout << "INSTRUCTION: SUB" << endl;
        if (continueRun() == 1) {
            SUB();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 6)
    {
        cout << "INSTRUCTION: CMP" << endl;
        if (continueRun() == 1) {
            CMP();
            return 1;
        } else {
            return 0;
        }
    }
    
    // if 7 stop
    if (opcode == 7)
    {
        return 0;
    }
}

// function that gets user input to keep program running or end it
int continueRun()
{
    char choice;
    
    cout << endl;
    cout << "Press 'e' to continue executing the program. Press any other key to stop the run" << endl;
    cin >> choice;

    if (choice == 'e')
    {
        return 1;
    } else {
        return 0;
    }
    
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
        if (instruction[i] == '0') 
        {
            store[lineNumber][i] = 0;
        } else {
            store[lineNumber][i] = 1;
        }
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
    string instruction = "";

    for (int i=0;i<32;i++)
    {
        instruction += to_string(store[lineNumber][i]);
    }

    return instruction;
}

// JMP set CI to content of store location
void Baby::JMP()
{
    int operand = getOperand();
    ci = getLineFromStore(operand);
}  

// JRP add content of store location to CI
void Baby::JRP() {
  int operand = getOperand();
  int ciValue = binaryToDecimal(ci);
  int result = ciValue + operand;

  for (int i = 31; i >= 0; i--) {
    if (result & (1 << i)) {
      ci[i] = '1';
    } else {
      ci[i] = '0';
    }
  }
}

// LDN load accumulator with negative form of store content
void Baby::LDN()
{
	int lineNumber = getOperand();
	string binaryValue = getLineFromStore(lineNumber);

	int negativeDecimalValue = binaryToDecimal(binaryValue) *-1;
	
	string negativeBinary = decimalToBinary(negativeDecimalValue);

	for (unsigned int i=0; i<negativeBinary.length(); i++)
	{
		if (negativeBinary[i] == '0')
		{
			accumulator[31 - i] = '0';
		}
		else
		{
			accumulator[31 - i] = '1';
		}
	}
}

// STO copy accumulator to store location
void Baby::STO()
{
	int lineNumber = getOperand();
	
	for (int i=0;i<SIZE;i++)
	{
		if (accumulator[i] == '0') 
		{
			store[lineNumber][i] = 0;
		} else {
			store[lineNumber][i] = 1;
		}
	}
}

// SUB subrtract content of store location from accumulator
int Baby::SUB()
{
	int lineNumber = getOperand();
	string binaryValue = getLineFromStore(lineNumber);
	int result = binaryToDecimal(accumulator) - binaryToDecimal(binaryValue);

	if (result > MAX_NUM || result < MIN_NUM)
	{
		return 0;
	}

	string binary = decimalToBinary(result);

	for (unsigned int i=0; i<binary.length(); i++)
	{
		if (binary[i] == '0')
		{
			accumulator[31 - i] = '0';
		}
		else
		{
			accumulator[31 - i] = '1';
		}
	}

	return 1;
}

// CMP incremt CI if accumulator value is negative, otherwise do nothing
void Baby::CMP()
{
    if (accumulator[31] == '1')
    {
        bool carry = true;
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
}
