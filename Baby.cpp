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

Baby::~Baby()
{
}

void Baby::incrementCI()
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

int Baby::fetch()
{
    int lineNumber = binaryToDecimal(ci);
    pi = getLineFromStore(lineNumber);

	int opcode = getOpcode();

    if (opcode == 0)
    {
        cout << "INSTRUCTION: JMP" << endl;
        if (runOrTerminate() == 1) {
            JMP();
            return 1;
        } else {
            return 0;
        }
    };
    if (opcode == 1)
    {
        cout << "INSTRUCTION: JRP" << endl;
        if (runOrTerminate() == 1) {
            JRP();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 2)
    {
        cout << "INSTRUCTION: LDN" << endl;
        if (runOrTerminate() == 1) {
            LDN();
            return 1;
        } else {
            return 0;
        }
    };
    if (opcode == 3)
    {
        cout << "INSTRUCTION: STO" << endl;
        if (runOrTerminate() == 1) {
            STO();
            return 1;
        } else {
            return 0;
        }
    };
    if (opcode ==4)
    {
        cout << "INSTRUCTION: SUB" << endl;
        if (runOrTerminate() == 1) {
            SUB();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 5)
    {
        cout << "INSTRUCTION: SUB" << endl;
        if (runOrTerminate() == 1) {
            SUB();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 6)
    {
        cout << "INSTRUCTION: CMP" << endl;
        if (runOrTerminate() == 1) {
            CMP();
            return 1;
        } else {
            return 0;
        }
    }
    if (opcode == 7)
    {
        return 0;
    }
}

int runOrTerminate()
{
    char choice;
    
    cout << endl;
    cout << "Press 'e' to continue executing the program or any other key to terminate this run." << endl;
    cin >> choice;

    if (choice == 'e')
    {
        return 1;
    } else {
        return 0;
    }
    
    return 0;
}

void Baby::printState()
{
    for (int i=0;i<storeSize;i++)
    {
        cout << (i+1);
        i < 9 ? cout << "    " : cout << "   ";
        for (int j=0;j<storeSize;j++) 
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

    for (int i=0;i<5;i++)
    {
        operand += pi[i];
    }

    return binaryToDecimal(operand);
}


string Baby::getLineFromStore(int lineNumber) 
{
    string instruction = "";

    for (int i=0;i<32;i++)
    {
        instruction += to_string(store[lineNumber][i]);
    }

    return instruction;
}

void Baby::JMP()
{
    int operand = getOperand();
    ci = getLineFromStore(operand);
}  

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