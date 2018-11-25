#include <iostream>
#include <sstream>
#include <map>
#include <regex>
#include <fstream>
#include "memories.h"

using namespace std;
/*
 * TODO:
 *
 */

typedef void (*programCommand)(istream& in, memories &numberMemory, bool &hasSaved);

enum FILE_TYPES {SCRIPT, COMPLEX};

struct programData {
  string scriptFilename;
  bool recordEnabled = false;
  bool executeEnabled = false;
  bool hasSaved = true;
};

void setUpFileIO(ifstream &inputFile, ofstream &outputFile, programData settings);
void setUpCommandMap(map<string, programCommand> &commandMap);
void processCommands(istream& in, memories &numberMemory, ofstream& outputFile, programData settings, map<string, programCommand> &commandMap);
void processCommandLineParameters(int argc, char** argv, programData settings, memories &numberMemory);
void parseExpression(istream &in, memories &numberMemory, char symbol);
void trig(complexNumber &complex);
void printHelp();
void let(istream& in, memories &numberMemory, bool &hasSaved);
void print(istream& in, memories &numberMemory, bool &hasSaved);
void save(istream& in, memories &numberMemory, bool &hasSaved);
void load(istream& in, memories &numberMemory, bool &hasSaved);
void exit(istream& in, memories &numberMemory, bool &hasSaved);
void wexit(istream& in, memories &numberMemory, bool &hasSaved);
void readFileIntoExpressionList(const string &filename, memories &numberMemory);
void addFileExtensionIfNotThereAlready(string &filename, FILE_TYPES type);
void fillExpressionList(memories &numberMemory);
bool fileExists(const string &filename);
bool getConfirmation();
bool confirmFileOverwrite(const string &filename);

int main(int argc, char** argv)
{
  memories complexNumberMemory;

  programData settings;
  processCommandLineParameters(argc, argv, settings, complexNumberMemory);

  ifstream inputFile;
  ofstream outputFile;
  setUpFileIO(inputFile, outputFile, settings);

  map<string, programCommand> commandMap;
  setUpCommandMap(commandMap);

  if(settings.executeEnabled) {
    processCommands(inputFile, complexNumberMemory, outputFile, settings, commandMap);
    inputFile.close();
  }
  processCommands(cin, complexNumberMemory, outputFile, settings, commandMap);

  outputFile.close();
  return 0;
}

void setUpFileIO(ifstream& inputFile, ofstream& outputFile, programData settings) {
  if(settings.recordEnabled) {
    if(fileExists(settings.scriptFilename)) {
      if(confirmFileOverwrite(settings.scriptFilename)) {
        outputFile.open(settings.scriptFilename, ios_base::out);
      } else {
        settings.recordEnabled = false;
      }
    }
  } else if(settings.executeEnabled) {
    inputFile.open(settings.scriptFilename, ios_base::in);
    if(!inputFile.is_open()) {
      cout << "ERROR: Script file not found: " << settings.scriptFilename << endl;
      cout << "       Continuing with console input..." << endl;
      settings.executeEnabled = false;
    }
  }
}

void setUpCommandMap(map<string, programCommand> &commandMap) {
  commandMap["LET"] = &let;
  commandMap["PRINT"] = &print;
  commandMap["SAVE"] = &save;
  commandMap["LOAD"] = &load;
  commandMap["EXIT"] = &exit;
  commandMap["WEXIT"] = &wexit;
}

void processCommands(istream& in, memories &numberMemory, ofstream& outputFile, programData settings, map<string, programCommand> &commandMap) {
  while(true) {
    cout << "COMMAND: ";
    string line;
    getline(in, line);

    if(&in != &cin) {
      cout << line << endl;
    }

    if(line.empty()) {
      return;
    }

    if(settings.recordEnabled) {
      outputFile << line << endl;
    }

    stringstream ss;
    ss << line;
    string command;
    ss >> command;

    if(command.length() == 1) {
      char symbol = command.at(0);
      parseExpression(ss, numberMemory, symbol);
    } else {
      try {
        commandMap.at(command)(in, numberMemory, settings.hasSaved);
      } catch (const out_of_range& oor) {
        cout << "ERROR: Invalid command: " << command << endl;
      }
    }

  }
}

void parseExpression(istream &in, memories &numberMemory, char symbol) {
  char rightSymbol1, rightSymbol2, operation, equalsTrash;
  string tempOperation;
  in >> equalsTrash;
  getline(in, tempOperation);

  if(regex_match(tempOperation, regex("^Trig\\([A-Z]\\)$"))) {
    trig(numberMemory.get(symbol));
  } else {
    stringstream ss;
    ss << tempOperation;
    ss >> rightSymbol1;
    bool operationSuccessful = true;
    if(rightSymbol1 == '~') {
      numberMemory.get(symbol) = numberMemory.get(symbol).getConjugate();
    } else {
      ss >> operation >> rightSymbol2;
      switch(operation) {
      case '+':
        numberMemory.get(symbol) = numberMemory.get(rightSymbol1) + numberMemory.get(rightSymbol2);
        break;
      case '-':
        numberMemory.get(symbol) = numberMemory.get(rightSymbol1) - numberMemory.get(rightSymbol2);
        break;
      case '*':
        numberMemory.get(symbol) = numberMemory.get(rightSymbol1) * numberMemory.get(rightSymbol2);
        break;
      case '/':
        numberMemory.get(symbol) = numberMemory.get(rightSymbol1) / numberMemory.get(rightSymbol2);
        break;
      default:
        cout << "ERROR: Unknown operation: " << operation << endl;
        operationSuccessful = false;
      }
    }
    if(operationSuccessful) {
      numberMemory.printSymbolToStream(cout, symbol);
    }
  }
}

void let(istream& in, memories &numberMemory, bool &hasSaved) {
  char symbol;
  complexNumber complex;
  if(in >> symbol >> complex) {
    try {
      numberMemory.get(symbol) = complex;
    } catch (memories::ERRORS error) {
      if(error == memories::SYMBOL_OUT_OF_RANGE) {
        cout << "ERROR: Invalid symbol: " << symbol << endl;
      }
    }
  } else {
    cout << "ERROR: Could not interpret expression." << endl;
  }
  hasSaved = false;
}

void print(istream& in, memories &numberMemory, bool &hasSaved) {
  char symbol;
  in >> symbol;
  try {
    numberMemory.printSymbolToStream(cout, symbol);
  } catch (memories::ERRORS e) {
    if(e == memories::SYMBOL_OUT_OF_RANGE) {
      cout << "ERROR: Invalid symbol: " << symbol << endl;
    }
  }
}

void save(istream& in, memories &numberMemory, bool &hasSaved) {
  string filename;
  in >> filename;
  addFileExtensionIfNotThereAlready(filename, COMPLEX);

  if(fileExists(filename) == false || confirmFileOverwrite(filename)) {
    numberMemory.saveToFile(filename);
  }
  hasSaved = true;
}

void load(istream& in, memories &numberMemory, bool &hasSaved) {
  string filename;
  in >> filename;
  addFileExtensionIfNotThereAlready(filename, COMPLEX);

  if(fileExists(filename)) {
    if(hasSaved == false) {
      cout << "WARNING: You have not saved your current expression list." << endl;
      cout << "         Loading from a file will overwrite your current list." << endl;
      cout << "         Proceed? (Y/N) ";
      if(getConfirmation() == false) {
        return;
      }
    }
    numberMemory.loadFromFile(filename);
  } else {
    cout << "ERROR: File " << filename << " not found." << endl;
  }
}

void exit(istream& in, memories &numberMemory, bool &hasSaved) {
  if(hasSaved == false) {
    cout << "WARNING: You have not saved your current expression list." << endl;
    cout << "         Do you wish to save your expressions? (Y/N)";
    if(getConfirmation()) {
      cout << "Filename to save to: ";
      save(in, numberMemory, hasSaved);
    }
  }
  exit(EXIT_SUCCESS);
}

void wexit(istream& in, memories &numberMemory, bool &hasSaved) {
  save(in, numberMemory, hasSaved);
  exit(EXIT_SUCCESS);
}

void processCommandLineParameters(int argc, char** argv, programData settings, memories &numberMemory) {
  if(argc == 2) {
    if(argv[1][0] == '/' && (argv[1][1] == 'h' || argv[1][1] == '?')) {
      printHelp();
      exit(EXIT_SUCCESS);
    } else {
      stringstream ss;
      ss << argv[1];
      load(ss, numberMemory, settings.hasSaved);
    }
  } else if(argc == 3) {
    string command = argv[1];
    if(command == "EXECUTE") {
      settings.executeEnabled = true;
      settings.scriptFilename = argv[2];
      addFileExtensionIfNotThereAlready(settings.scriptFilename, SCRIPT);
    } else if(command == "RECORD") {
      settings.recordEnabled = true;
      settings.scriptFilename = argv[2];
      addFileExtensionIfNotThereAlready(settings.scriptFilename, SCRIPT);
    } else {
      cout << "ERROR: Unknown command: " << argv[1] << endl;
      exit(EXIT_FAILURE);
    }
  } else if(argc > 3) {
    cout << "ERROR: Too many arguments given." << endl;
    exit(EXIT_FAILURE);
  }
}

void addFileExtensionIfNotThereAlready(string &filename, FILE_TYPES type) {
  if(type == SCRIPT) {
    if(filename.length() <= 4 || filename.substr(filename.length() - 4) != ".spt") {
      filename.append(".spt");
    }
  } else if(type == COMPLEX) {
    if(filename.length() <= 8 || filename.substr(filename.length() - 8) == ".complex") {
      filename.append(".complex");
    }
  }
}

void printHelp() {
  cout << "USAGE:" << endl
       << "  complexCalculate.exe                      Runs the program" << endl
       << "  complexCalculate.exe /h or /?             Displays this message" << endl
       << "  complexCalculate.exe <file.exp>           Loads an exponent file" << endl
       << "  complexCalculate.exe [COMMAND] <file.spt> Executes a command with script file" << endl
       << endl
       << "COMMANDS:" << endl
       << "  EXECUTE   Executes a script file" << endl
       << "  RECORD    Records user input to a script file" << endl;
}

bool fileExists(const string &filename) {
  ifstream file(filename);
  return file.good();
}

bool getConfirmation() {
  string response;
  getline(cin, response);

  if(response.at(0) == 'Y' || response.at(0) == 'y') {
    return true;
  }
  return false;
}

bool confirmFileOverwrite(const string &filename) {
  cout << "WARNING: File " << filename << " already exists." << endl;
  cout << "         Do you want to override the file? (Y/N)";
  if(getConfirmation()) {
    return true;
  } else {
    return false;
  }
}

void trig(complexNumber &complex) {
  cout << "(" << complex.getMagnitude() << ", " << complex.getDirection() << ")" << endl;
}


