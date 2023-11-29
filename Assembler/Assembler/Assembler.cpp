/*
Manchester Baby
Assembler
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <iomanip>
#include <unordered_map>


using namespace std;

// Global Variables 
int lineEnd = 0;
int startEnd=0;

map<string, string> instructionSet;

// Label function check ( Start, End, Bin 0)
bool checkLabels(vector<vector<string>> vect, int checkLine){
 if (checkLine==1){
    cout<< endl;
    cout<<"Search for start"<<endl;
    int inputSize = vect.size();
    for( int i =0; i <inputSize; i++){
        int line = vect[i].size();
        for (int j = 0; j<line; j++){
            if (vect[i][j] == "Start:"){
                cout << "Assembly code start has been found " << i << endl;
                startEnd = i;
            return true;
            }
        }
    }
    cout<<"Assembly code start has not been found"<<endl;
    return false;
 } else if (checkLine==2){
    cout <<endl;
    cout << "Searching for Assembly code end" << endl;
    int inputSize = vect.size();
    for (int i =0; i<inputSize; i++){
        int line = vect[i].size();
        for(int j = 0; j<line; j++){
            if (vect[i][j] == "End:"){
                cout << "Assembly code end has been found " << i << endl;
                lineEnd = i;
            return true;
            }
        }
    } cout<< "Assembly code end has not been found" << endl;
    return false;
 }
 else if (checkLine ==3){
    cout << endl;
    cout << "Assembly code searching for (Bin 0)" << endl;
    if (startEnd != 0){
        int lineSize = vect[startEnd-1].size();
        for (int l =0; l<lineSize; l++){
            if (vect[startEnd-1][l] == "Bin"){
                if(l !=0){
                       if(vect[startEnd-1][l-1] == "0"){
                            cout<< "Bin 0 has been found " << endl;
                            return true;
                       }
                }else {
                    cout << "0 has not been found" << endl;
                    return false;
                }
            }
    
       }
    }   
 }
 cout<< "0 has not been found" << endl;
 return false;
}

// Initalisation of instruction set
void instructionSetInit(std::unordered_map<std::string,std::string>& instructionSet) {
    instructionSet["JMP"] = "0000";
    instructionSet["JRP"] = "0001";
    instructionSet["LDN"] = "0010";
    instructionSet["STO"] = "0011";
    instructionSet["SUB"] = "0100";
    instructionSet["CMP"] = "0101";
}
// Function to convert instruction code to binary
std::string instructionToBinary(const std:: string& instruction, const std::unordered_map<std::string,std::string>& instructionSet){
     auto it = instructionSet.find(instruction);
        if (it != instructionSet.end()){
            return it->second;
        }
        else{
            std::cout <<"Error: Instruction not found, Terminitating Complier"<<std::endl;
            return "error";
        }

    }
// Function to convert decimal to binary
std::string decimalToBinary(const std::string&dec, int bitSize) {
    int intDec = std::stoi(dec);
    std::string returnString;

    while (intDec !=0){
        returnString = (intDec % 2== 0 ? "0": "1") + returnString;
        intDec /= 2;
    }

    while (returnString.size()< bitSize){
        returnString = returnString.size();
    }
    std::cout <<returnString<<std::endl;
}

// Function to create and process file
void newFile(const std::vector<std::vector<std::string>>& vect, const std::vector<std::string>& commandLine){
    int vectSize = vect.size();
    std::string finalString;
    std::string binary;

    if (commandLine.size()>2){
        if(commandLine[2]!="Start:"){
            std::cout<<"Error wrong Assembly code inputted(Instructions exceeded"<<std::endl;
            return;
        }
    }

    for (int i = lineEnd +1; i <vectSize; i++){
        size_t pos = vect[i][2].find(commandLine[0]);
        if (pos != std::string::npos){
            std::string temp = commandLine[0]+":";
            if (vect[i][2]== temp){
                std::cout<<"Processing Memory allocation needed for first variable."<<std::endl;
                finalString = decimalToBinary(std::to_string(i), 5);
                break;
            }else{
                std::cout<<"Error: Wrong Assembly code format inputted"<<std::endl;
                return;
            }
        }else if (commandLine[0]  =="STP"){
            std::cout<<"Dectected STP instruction, Instruction set has complied(Inital Pass complete)"<<std::endl;
            std::cout<<"Binary code outputted to file"<<std::endl;
            return;
        }else if(i == vectSize-1){
            std::cout<<"Error: Wrong Assembly code inputted"<<std::endl;
            return;
        }
    }
}

std::string convertLineToMachineCode(const std::vector<std::string>& line){
std::string machineCode;


if(line.size()>=3){


std::string operation = line[0];
std::string operand1= line[1];
std::string operand2 = line[2];



if (instructionSet.find(operation)==instructionSet.end()){
    std::string opcode = instructionSet[operation];

    std:: string operand1Binary = decimalToBinary(operand1Binary, 5);
    std:: string operand2Binary = decimalToBinary(operand2Binary,5);

    machineCode = opcode + operand1Binary + operand2Binary;
}else{
    std::cout<<"Error: Operation not found"<<std::endl;
    machineCode = "error";
 } 
}else{
    std::cout<<"Error:Invalid line size"<<std::endl;
    machineCode = "error";
}
return machineCode;
}

vector<vector<string>> symbolConvert(const string& fileName){
    ifstream file(fileName);
    if(!file.is_open()){
        cout << "Error: File could not be opened" << endl;
        return {};
    }

    vector<vector<string>> inputs;
    string line;
    while(getline(file, line)){
        inputs.push_back(convertLine(line));
    }
    file.close();
    return inputs;
}

vector<string> convertLine(const string&line ){
    vector<string> tokens;
    istringstream iss(line);
    string token;
    while(iss>>token){
        if (token[0] == ';'){
            break;
        }
        tokens.push_back(token);
    }
    return tokens;
}



void assemblyConversion(const vector<vector<string>>& inputs){
    cout <<" Assembly language conversion to machine code from .txt file" << endl;
    cout <<"==============="<<endl;
    for (const auto& line: inputs){
        for (const auto&token:line){
            cout <<token<<"";
        }
        cout <<endl;
    }
    cout <<"==============="<<endl;
}

bool machineCode(const vector<vector<string>>& inputs){
    ofstream outFile("Assembler/MachineCode.txt");
    if(!outFile.is_open()){
        cout << "Error: File could not be opened" << endl;
        return false;
    }
    if(!checkLabels(inputs,lineEnd)){
        cout << "Error: Labels could not be found" << endl;
        outFile.close();
        return false;
    }
    outFile<<"000000000000000000"<<endl;
    
    for (size_t i=1; i <lineEnd +1;i++){
        string tempString = convertLineToMachineCode(inputs[i]);
        if(tempString == "error"){
           cout<< "Error: Machine code could not be created" << endl;
           outFile.close();
           return false;
        }
        outFile << tempString << endl;
    }
    
for(size_t n= lineEnd +1; n<inputs.size(); ++n){
    if(inputs[n].size()<2|| inputs[n][1]!="VAR"){
        cout << "Error: Machine code could not be createdm; due to incorrect format of assembly file" << endl;
        outFile.close();
        return false;
    }
    outFile << "tempString2" << endl;
}
cout<<endl<< "No errors detected, Machine code has been created" << endl;
cout<<"========================================"<<endl;
cout<<"Full Complication of Assembly code has been completed"<<endl;
cout<<"========================================"<<endl;
outFile.close();
return true;
}


void convertSymbols(const string& fileName){
    vector<vector<string>> inputs = symbolConvert(fileName);
    if(inputs.empty()){
        return;
    }

    assemblyConversion(inputs);
    if(machineCode(inputs)){
        // Code to execute if machineCode returns true
    }else{
        // Code to execute if machineCode returns false
    }
}

int main(){
    std::string assemblyFileName = "Assembler/AssemblyCode.txt";
    convertSymbols(assemblyFileName);
    return 0;
}


