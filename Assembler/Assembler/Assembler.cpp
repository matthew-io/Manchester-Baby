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

// Global Variables
int lineEnd = 0;
int startEnd = 0;

struct Symbol {
    std::string name;
    int address;
    std::string value;
};

std::map<std::string, std::string> instructionSet;
std::vector<Symbol> symbolTable;

// Initialization of instruction set
void initializeInstructionSet() {
    instructionSet["JMP"] = "0000";
    instructionSet["JRP"] = "0001";
    instructionSet["LDN"] = "0010";
    instructionSet["STO"] = "0011";
    instructionSet["SUB"] = "0100";
    instructionSet["CMP"] = "0101";
    instructionSet["STP"] = "0110";
}

// Label function check (Start, End, Bin 0)
bool checkStart(const std::vector<std::vector<std::string>>& codeLines) {
    std::cout << "Searching for Assembly code start" << std::endl;
    for (size_t i = 0; i < codeLines.size(); i++) {
        for (size_t j = 0; j < codeLines[i].size(); j++) {
            if (codeLines[i][j] == "Start:") {
                std::cout << "Assembly code start has been found " << i << std::endl;
                startEnd = i;
                return true;
            }
        }
    }
    std::cout << "Assembly code start has not been found" << std::endl;
    return false;
}

bool checkEnd(const std::vector<std::vector<std::string>>& codeLines, int& lineEnd) {
    std::cout << "Searching for Assembly code end" << std::endl;
    for (size_t i = 0; i < codeLines.size(); i++) {
        for (size_t j = 0; j < codeLines[i].size(); j++) {
            if (codeLines[i][j] == "End:") {
                std::cout << "Assembly code end has been found " << i << std::endl;
                lineEnd = i;
                return true;
            }
        }
    }
    std::cout << "Assembly code end has not been found" << std::endl;
    return false;
}

bool checkBinZero(const std::vector<std::vector<std::string>>& codeLines, int startEnd) {
    std::cout << "Searching for Assembly code (Bin 0)" << std::endl;
    if (startEnd != 0 && startEnd - 1 >= 0 && startEnd - 1 < codeLines.size()) {
        const std::vector<std::string>& previousLine = codeLines[startEnd - 1];
        for (size_t l = 0; l < previousLine.size(); ++l) {
            if (previousLine[l] == "Bin" && l != 0 && previousLine[l - 1] == "0") {
                std::cout << "Bin 0 has been found " << std::endl;
                return true;
            }
        }
        std::cout << "Bin 0 has not been found" << std::endl;
        return false;
    }
    std::cout << "Invalid startEnd value or out of bounds" << std::endl;
    return false;
}

std::vector<std::string> readLinesFromFile(const std::string& fileName) {
    std::vector<std::string> lines;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cout << "Error: File could not be opened " << fileName << std::endl;
    }
    return lines;
}

std::vector<std::vector<std::string>> processLines(const std::vector<std::string>& lines) {
    std::vector<std::vector<std::string>> tokens;

    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::vector<std::string> lineTokens;
        std::string token;

        while (iss >> token) {
            if (token[0] == ';') {
                break;
            }
            lineTokens.push_back(token);
        }
        tokens.push_back(lineTokens);
    }
    return tokens;
}

void addLabelToSymbolTable(const std::string& label, int address) {
    Symbol newLabel;
    newLabel.name = label;
    newLabel.address = address;
    newLabel.value = "";
    symbolTable.push_back(newLabel);
}

void addVariableToSymbolTable(const std::string& variableName, int address, const std::string& variableValue) {
    Symbol newVariable;
    newVariable.name = variableName;
    newVariable.address = address;
    newVariable.value = variableValue;
    symbolTable.push_back(newVariable);
}

void symbolTableManagement(const std::vector<std::vector<std::string>>& inputs) {
    int currentAddress = 0;

    for (const auto& line : inputs) {
        if (!line.empty()) {
            std::string firstToken = line[0];

            bool isLabel = (firstToken.back() == ':');

            if (isLabel) {
                Symbol label;
                label.name = firstToken.substr(0, firstToken.size() - 1);
                label.address = currentAddress;
                label.value = "";
                symbolTable.push_back(label);
            } else if (firstToken == "VAR") {
                if (line.size() >= 3) {
                    Symbol variable;
                    variable.name = line[1];
                    variable.address = currentAddress;
                    variable.value = line[2];
                    symbolTable.push_back(variable);
                }
            } else {
                std::cout << "Error: Invalid Assembly code format" << std::endl;
            }
        }
        currentAddress++;
    }
}

// Function to convert instruction code to binary
std::string instructionToBinary(const std::string& instruction, const std::unordered_map<std::string, std::string>& instructionSet) {
    auto it = instructionSet.find(instruction);
    if (it != instructionSet.end()) {
        return it->second;
    } else {
        std::cout << "Error: Instruction not found, Terminating Compiler" << std::endl;
        return "error";
    }
}

std::string decimalToBinary(const std::string& dec, int bitSize) {
    int intDec = std::stoi(dec);
    std::string returnString;

    while (intDec != 0) {
        returnString = (intDec % 2 == 0 ? "0" : "1") + returnString;
        intDec /= 2;
    }

    while (returnString.size() < bitSize) {
        returnString = "0" + returnString;
    }
    return returnString;
}

void processFile(const std::string& fileName) {
    std::vector<std::string> lines;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cout << "Error: File could not be opened " << fileName << std::endl;
    }
}

// Function to create and process file
void newFile(const std::vector<std::vector<std::string>>& vect, const std::vector<std::string>& commandLine){
    int vectSize = vect.size();
    std::string finalString;
    std::string binary;

    if (commandLine.size() > 2){
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
        }else if(i == vectSize - 1){
            std::cout<<"Error: Wrong Assembly code inputted"<<std::endl;
            return;
        }
    }
}

std::string convertLineToMachineCode(const std::vector<std::string>& line){

    std::string operation = line[0];
    std::string operand1= line[1];
    std::string operand2 = line[2];

    std::string machineCode;

    if (instructionSet.find(operation)==instructionSet.end()){
        std::string opcode = instructionSet[operation];
        
        if(validateOperands(operation, operand1, operand2)){
           std:: string operand1Binary = decimalToBinary(operand1, 5);
           std:: string operand2Binary = decimalToBinary(operand2,5);
       
           machineCode = opcode + operand1Binary + operand2Binary;
        }else{
           std::cout<<"Error: Invalid Operands for the"<<operation<< "instruction"<<std::endl;
           machineCode = "error";
        }
     }else {
        std::cout<<"Error: Unsupported instruction or operands"<<std::endl;
        machineCode = "error";
     }
      return machineCode;
}

void assemblyConversion(const std::vector<std::vector<std::string>>& inputs){
    std::cout <<" Assembly language conversion to machine code from .txt file" << endl;
    std::cout <<"==============="<<std::endl;
    for (const auto& line: inputs){
        for (const auto& token:line){
            std::cout <<token<<"";
        }
        std::cout std::<<endl;
    }
    std::cout<<"==============="<<std::endl;
}
bool validateOperands(const std::string& operation, const std::string& operand1, const std::string& operand2){
    if (isNumeric(operand1) && isNumeric(operand2)){
        return true;
        }
        return false;
}

bool isNumeric(const std::string& str){
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void convertSymbols(const std::string& fileName){
    std::vector<std::vector<std::string>> inputs = symbolConvert(fileName);
    if(inputs.empty()){
        std::cout<<"Error:: Empty or inaccessible file"<<std::endl;
        return;
    }

    manageSymbolTable(inputs);

    assemblyConversion(inputs);
    if(machineCode(inputs)){
        std::cout<< "Assembly compiled successfully. Machine code has been created"<<std::endl;
    }else{ 
        std::cout<<"Error: Machine code could not be created"<<std::endl;
    }
}

std::vector<std::vector<std::string>> symbolConvert(const std::string& fileName){
    std::ifstream file(fileName);
    if(!file.is_open()){
       std::cout << "Error: File could not be opened" <<std::endl;
        return {};
    }

    std::vector<std::vector<std::string>> inputs;
    std::string line;
    while(getline(file, line)){
        inputs.push_back(convertLine(line));
    }
    file.close();
    return inputs;
}

std::vector<std::string> convertLine(const std::string& line ){
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while(iss>>token){
        if (token[0] == ';'){
            break;
        }
        tokens.push_back(token);
    }
    return tokens;
}

bool machineCode(const std::vector<std::vector<std::string>>& inputs){
    std::ofstream outFile("Assembler/MachineCode.txt");
    if(!outFile.is_open()){
        std::cout << "Error: File could not be opened" <<std::endl;
        return false;
    }
    if(!checkLabels(inputs,lineEnd)){
        std::cout << "Error: Labels could not be found" << std::endl;
        outFile.close();
        return false;
    }
    outFile<<"000000000000000000"<<std::endl;
    
    for (size_t i=1; i <lineEnd +1;i++){
        std::string tempString = convertLineToMachineCode(inputs[i]);
        if(tempString == "error"){
           std::cout<< "Error: Machine code could not be created" <<std::endl;
           outFile.close();
           return false;
        }
        outFile << tempString <<std::endl;
    }
    
    for(size_t n= lineEnd +1; n<inputs.size(); ++n){
        if(inputs[n].size()<2|| inputs[n][1]!="VAR"){
           std::cout << "Error: Machine code could not be createdm; due to incorrect format of assembly file" << endl;
           outFile.close();
           return false;
    }
    outFile << "tempString2" << std::endl;
}
std::cout<<endl<< "No errors detected, Machine code has been created" <<std::endl;
std::cout<<"========================================"<<std::endl;
std::cout<<"Full Complication of Assembly code has been completed"<<std::endl;
std::cout<<"========================================"<<std::endl;
outFile.close();
return true;
}




int main() {
    std::string assemblyFileName = "Assembler/AssemblyCode.txt";

    processFile(assemblyFileName);

    std::vector<std::vector<std::string>> lines = processLines(readLinesFromFile(assemblyFileName));

    initializeInstructionSet();

    bool startFound = checkStart(lines);
    if (!startFound) {
        std::cout << "Error: Assembly code start not found." << std::endl;
        return 1;
    }

    bool endFound = checkEnd(lines, lineEnd);
    if (!endFound) {
        std::cout << "Error: Assembly code end not found." << std::endl;
        return 1;
    }
    return 0;
}


