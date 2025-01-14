#include <string>

using namespace std;

#define SIZE 32

class Baby{
    private: 
        int store[SIZE][SIZE];
        string accumulator;
        string ci;
        string pi;

    public:
        void printStore();
        void addInstructionToStore(int lineNumber, string instruction);
        int getOpcode();
        int getOperand();
        void incrementCI();
        int continueRun();
        int fetch(char choice);
        string getLineFromStore(int operand);
        string negateBinary(const string& binaryValue);
        int decode();
        

        int SUB();
        void JRP();
        void STO();
        void LDN();
        void CMP();
        void JMP();

        Baby();
        ~Baby();
};