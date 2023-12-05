#include <string>

using namespace std;

#define SIZE 32
#define MAX_NUM 2147483647
#define MIN_NUM -2147483647


class Baby{
    private: 
    
        int storeSize;
        string accumulator;
        bool store[SIZE][SIZE];
        string ci;
        string pi;

    public:
        void printState();
        void addInstructionToStore(int lineNumber, string instruction);
        int getOpcode();
        int getOperand();
        void incrementCI();
        int continueRun();
        int fetch();
        string getLineFromStore(int operand);
        string negateBinary(const string& binaryValue);
        int decode();
        

        void JMP();
        void JRP();
        void LDN();
        void STO();
        int SUB();
        void CMP();

        Baby();
        ~Baby();
};