# include "InputValidator.h"

using std::string;
using std::cerr;
using std::ifstream;
using std::istreambuf_iterator;

void InputValidator::validateAllInputs(const string &cipherType, const string &inputFileName, const string &outputFileName, const string &keyFileName, const string &modeOfOperation){
    // Check if cipherType matches the expected type
    validateCipherType(cipherType);

    // Check if files exists
    //TODO: How should error checking work for outputFileName & keyFile?
    doesFileExist(inputFileName, "Input File Does Not Exist");
    doesFileExist(keyFileName, "Key File Does Not Exist");

    isKeyFileValid(keyFileName);

    // Validate the mode of operation
    //TODO: Is this correct?
    validateModeOfOperation(modeOfOperation);
}

void InputValidator::validateCipherType(const string &cipherType) {
    // Validate types are 'B' (block) or 'S' (stream)
    if (!(cipherType == "B" || cipherType == "S")) {
        cerr << "Invalid Function Type";
        exit(1);
    }
}


void InputValidator::validateModeOfOperation(const string &modeOfOperation) {
    if (!(modeOfOperation == "E" || modeOfOperation == "D")) {
        cerr << "Invalid Mode Type";
        exit(1);
    }
}

void InputValidator::doesFileExist(const string &fileName, const string &errorMessage) {
    ifstream file(fileName);

    if (!file.good()) {
        cerr << errorMessage;
        exit(1);
    }
}

void InputValidator::isKeyFileValid(const string &keyFileName) {
    ifstream keyFile(keyFileName);

    string keyFileContent((std::istreambuf_iterator<char>(keyFile)), istreambuf_iterator<char>());
    keyFile.close();

    if (containsNewLine(keyFileContent)) {
        cerr << "inputValidator.cpp: the key file " << keyFileName << " contains a newline character.\n";
        exit(1);
    }
}

bool InputValidator::containsNewLine(const string &str) {
    for (char ch : str) {
        if (ch == '\n') {
            return true;
        }
    }

    return false;
}