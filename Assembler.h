
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
            map<string, string> instructions;

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
            map<string, string> symbols;

            // bool to check if symbol exists
            bool contains(const string& symbol) const {
                return symbols.find(symbol) != symbols.end();
            }

            // Get address of corressponding symbol
            string getAddress(const string& symbol) const {
                if (contains(symbol)) {
                    return symbols.at(symbol);
                } else {
                    throw invalid_argument("Symbol not found");
                }
            }

            // Remove symbol from symbol table
            void removeSymbol(const string& symbol) {
                if (contains(symbol)) {
                    symbols.erase(symbol);
                } else {
                    throw invalid_argument("Symbol not found");
                }
            }

            // Add  all symbols to symbol table
            vector<string> getSymbols() const {
                vector<string> symbolList;
                for (const auto& symbol : symbols) {
                    symbolList.push_back(symbol.first); 
                }
                return symbolList;
            }
        };
        
        //Structure to store variables and their addresses
        struct VariableMap {
            map<string, string> variables;

            void addVariable(const string& variable, const string& address) {
                if (all_of(address.begin(), address.end(), ::isdigit)) {
                    // int addr = stoi(address);
                    // bitset<32> binaryAddress(addr);
                    // variables[variable] = binaryAddress.to_string();
                    if(variables[variable].length()<32){
                      variables[variable] = string(32-variables[variable].length(),'0') + variables[variable];
                    }
                } else {
                    throw invalid_argument("Address must be an integer");
                }
            }

            // Get binary address of variable
            string getBinary(const string& variable) const {
                auto it = variables.find(variable);
                if (it != variables.end()) {
                    return it->second;
                }
                return "";
            }
        // Update address of variable
        void updateVariable(const string& variable, const string& newAddress) {
            auto it = variables.find(variable);
            if (it != variables.end()) {
                it->second = bitset<32>(stoi(newAddress)).to_string();
            }
        }

        //Remove variable from variable map
        void removeVariable(const string& variable) {
            auto it = variables.find(variable);
            if (it != variables.end()) {
                variables.erase(it);
            }
        }

        bool contains(const string& variable) const {
            return variables.find(variable) != variables.end();
        }
        };

        //Function to read file and store in vector
        void newFile(const string& fileName, vector<string>& fileContent) {
            ifstream file("./input/" +fileName);

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    size_t found = line.find(';');
                    if (found != string::npos) {
                        line.erase(found);
                    }
                    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

                    if (!line.empty()) {
                        fileContent.push_back(line);
                    }
                }
                file.close();
            } else {
                throw runtime_error("Error: File not found");
            }
        }

        // Extention Function to report progress during Assembly
        void reportProgress(const string& message){
            cout<<"Progress:" << message << endl;
        }

        void saveMachineCodeToFile(const vector<string>& saveMachineLines){
        ofstream outputFile("output.txt");
        if(outputFile.is_open()){
            for (const auto& line : saveMachineLines){
                outputFile << line << endl;
            }
            outputFile.close();
            cout << "Machine code saved to output.txt" << endl;
        } else {
            throw runtime_error ("Error: Unable to save machine code to file");
        }
    }


    //Function to convert assembly to machine code
        void convertAssembly(const vector<string>& fileContent, SymbolTable& symbolTable, VariableMap& variableMap, map<string, string>& instructionSet){
            string currentAddress = "$0000";
            int lineCount = 0;

            vector<string> machineCodeLines;

            for (const string& line : fileContent) {
                istringstream iss(line);
                string cleanLine;
                getline(iss, cleanLine, ';'); 

                cleanLine.erase(remove_if(cleanLine.begin(), cleanLine.end(), ::isspace), cleanLine.end());

                if (cleanLine.empty()) {
                    continue;
                }

                size_t found = cleanLine.find(':');
                if (found != string::npos) {
                    string label = cleanLine.substr(0, found);
                    if (symbolTable.contains(label)) {
                        symbolTable.symbols[label] = currentAddress.substr(1);
                        cleanLine = cleanLine.substr(found + 1);
                }
                }

                found = cleanLine.find("VAR");
                if(found != string::npos){
                    string variableDeclaration = cleanLine.substr(found + 3);
                    istringstream variableStream(variableDeclaration);
                    string variableName;
                    string value;

                    //Adding variable to Variable map
                    variableStream >> variableName >> value;
                    variableMap.addVariable(variableName, value);
                    continue;
                }
                found = cleanLine.find_first_not_of('\t');
                if (found != string::npos) {
                    string instruction = cleanLine.substr(found, 3);
                    string operand = cleanLine.substr(found + 3);

                    string machineCode;
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
                        
                        machineCode += "00000";
                    }

                    cout << machineCode << endl;

                    machineCodeLines.push_back(machineCode);

                    int addressValue = stoi(currentAddress.substr(1), nullptr, 32);
                    addressValue++;
                    stringstream stream;
                    stream << uppercase << setw(3) << setfill('0') << hex << addressValue;
                    currentAddress = "$" + stream.str();
                    
                    lineCount++;

                    reportProgress("Processd Line"+to_string(lineCount)+ "/"+to_string(fileContent.size()));
                }
            }
            reportProgress("Assembly complete");

            try {
                saveMachineCodeToFile(machineCodeLines);
            } catch (const exception& e) {
                cout << "Error converting string to integer: " << e.what() << endl;
            }

        }


    // Function to output machine code to file
    void codeBufferOutput(const string& machineCode) {
            cout << machineCode << endl;
        }
    // Main function
    // int main() {
        // vector<string> fileContent{};
        // SymbolTable symbolTable;
        // VariableMap variableMap;
        // map<string, string> instructionSet;

        // InstructionSet instructions;
        // instructionSet=instructions.instructions;

        // string fileName;
        // cout << "Enter file name: ";
        // cin >> fileName;

        // try {
        //     newFile(fileName, fileContent);
        //     convertAssembly(fileContent, symbolTable, variableMap, instructionSet);
        // } catch (const exception& e) {
        //     cout <<"Error occurred: "<< e.what() << endl;
        // }


        // return 0;
    // }