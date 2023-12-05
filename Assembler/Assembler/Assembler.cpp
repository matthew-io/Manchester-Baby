
    // Manchester Baby assembler

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include <algorithm>
    #include <iterator>
    #include <map>
    #include <iomanip>
    #include <bitset>

    using namespace std;

    //Store instruction set structure
    struct InstructionSet {
        std::map<std::string, std::string> instructions;

        //constructor to initialise instruction set with opcodes
        InstructionSet() {
            instructions["JMP"] = "0000";
            instructions["JRP"] = "0001";
            instructions["LDN"] = "0010";
            instructions["STO"] = "0011";
            instructions["SUB"] = "0100";
            instructions["CMP"] = "0101";
            instructions["STP"] = "0110";
        }
    };

    // Store symbol table structure
    struct SymbolTable {
        std::map<std::string, std::string> symbols;

        // bool to check if symbol exists
        bool contains(const std::string& symbol) const {
            return symbols.find(symbol) != symbols.end();
        }

        // Get address of corressponding symbol
        std::string getAddress(const std::string& symbol) const {
            if (contains(symbol)) {
                return symbols.at(symbol);
            } else {
                throw std::invalid_argument("Symbol not found");
            }
        }

        // Remove symbol from symbol table
        void removeSymbol(const std::string& symbol) {
            if (contains(symbol)) {
                symbols.erase(symbol);
            } else {
                throw std::invalid_argument("Symbol not found");
            }
        }

        // Add  all symbols to symbol table
        std::vector<std::string> getSymbols() const {
            std::vector<std::string> symbolList;
            for (const auto& symbol : symbols) {
                symbolList.push_back(symbol.first); 
            }
            return symbolList;
        }
    };
    
    //Structure to store variables and their addresses
    struct VariableMap {
        std::map<std::string, std::string> variables;

        void addVariable(const std::string& variable, const std::string& address) {
            variables[variable] = std::bitset<32>(std::stoi(address)).to_string();
        }

        // Get binary address of variable
        std::string getBinary(const std::string& variable) const {
            auto it = variables.find(variable);
            if (it != variables.end()) {
                return it->second;
            }
            return "";
        }
    // Update address of variable
    void updateVariable(const std::string& variable, const std::string& newAddress) {
        auto it = variables.find(variable);
        if (it != variables.end()) {
            it->second = std::bitset<32>(std::stoi(newAddress)).to_string();
        }
    }

    //Remove variable from variable map
    void removeVariable(const std::string& variable) {
        auto it = variables.find(variable);
        if (it != variables.end()) {
            variables.erase(it);
        }
    }

    bool contains(const std::string& variable) const {
        return variables.find(variable) != variables.end();
    }
    };

    //Function to read file and store in vector
    void newFile(const std::string& fileName, std::vector<std::string>& fileContent) {
        std::ifstream file(fileName);

        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                size_t found = line.find(';');
                if (found != std::string::npos) {
                    line.erase(found);
                }
                line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

                if (!line.empty()) {
                    fileContent.push_back(line);
                }
            }
            file.close();
        } else {
            throw std::runtime_error("Error: File not found");
        }
    }

    // Extention Function to report progress during Assembly
    void reportProgress(const std::string& message){
        std::cout<<"Progress:" << message << std::endl;
    }

    void saveMachineCodeToFile(const std::vector<std::string>& saveMachineLines){
    std::ofstream outputFile("testcode.txt");
    if(outputFile.is_open()){
        for (const auto& line : saveMachineLines){
            outputFile << line << std::endl;
        }
        outputFile.close();
        std::cout << "Machine code saved to testcode.txt" << std::endl;
    } else {
        throw std::runtime_error ("Error: Unable to save machine code to file");
    }
}


   //Function to convert assembly to machine code
   void convertAssembly(const std::vector<std::string>& fileContent, SymbolTable& symbolTable, VariableMap& variableMap, std::map<std::string, std::string>& instructionSet){
    std::string currentAddress = "$000";
    int lineCount = 0;

    std::vector<std::string> machineCodeLines;

    for (const std::string& line : fileContent) {
        std::istringstream iss(line);
        std::string cleanLine;
        std::getline(iss, cleanLine, ';'); 

        cleanLine.erase(std::remove_if(cleanLine.begin(), cleanLine.end(), ::isspace), cleanLine.end());

        if (cleanLine.empty()) {
            continue;
        }

        size_t found = cleanLine.find(':');
        if (found != std::string::npos) {
            std::string label = cleanLine.substr(0, found);
            if (symbolTable.contains(label)) {
                cleanLine = cleanLine.substr(found + 1);
            }
        }

        found = cleanLine.find_first_not_of('\t');
        if (found != std::string::npos) {
            std::string instruction = cleanLine.substr(found, 3);
            std::string operand = cleanLine.substr(found + 3);

            std::string machineCode;
            if (operand.empty()) {
                machineCode = "00000";
            } else if(variableMap.contains(operand)) {
                machineCode = variableMap.getBinary(operand);
            }else if(symbolTable.contains(operand)){
                machineCode = symbolTable.getAddress(operand);
            } 

            auto it = instructionSet.find(instruction);
            if (it != instructionSet.end()) {
                machineCode += it->second;
            } else {
                
                machineCode += "00000000";
            }

            std::cout << machineCode << std::endl;

            machineCodeLines.push_back(machineCode);

            int addressValue = std::stoi(currentAddress.substr(1), nullptr, 16);
            addressValue++;
            std::stringstream stream;
            stream << std::uppercase << std::setw(3) << std::setfill('0') << std::hex << addressValue;
            currentAddress = "$" + stream.str();
            
            lineCount++;

            reportProgress("Processd Line"+std::to_string(lineCount)+ "/"+std::to_string(fileContent.size()));
        }
    }
    reportProgress("Assembly complete");

    try{
        saveMachineCodeToFile(machineCodeLines);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    
    }
}


// Function to output machine code to file
void codeBufferOutput(const std::string& machineCode) {
        std::cout << machineCode << std::endl;
    }
// Main function
int main() {
    std::vector<std::string> fileContent{};
    SymbolTable symbolTable;
    VariableMap variableMap;
    std::map<std::string, std::string> instructionSet;

    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;

    try {
        newFile(fileName, fileContent);
        convertAssembly(fileContent, symbolTable, variableMap, instructionSet);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
 }