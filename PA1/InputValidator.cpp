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
    doesFileExist(inputFileName);
    doesFileExist(outputFileName);
    doesFileExist(keyFileName);

    isKeyFileValid(keyFileName);

    // Validate the mode of operation
    //TODO: Is this correct?
    validateModeOfOperation(modeOfOperation);
}

void InputValidator::validateCipherType(const string &cipherType) {
    // Validate types are 'B' (block) or 'S' (stream)
    if (!(cipherType == "B" || cipherType == "S")) {
        cerr << "inputValidator.cpp: the input cipher type " << cipherType << " is invalid.\n";
        exit(1);
    }
}


void InputValidator::validateModeOfOperation(const string &modeOfOperation) {
    if (!(modeOfOperation == "E" || modeOfOperation == "D")) {
        cerr << "inputValidator.cpp: the mode of operation " << modeOfOperation << " is invalid.\n";
        exit(1);
    }
}

void InputValidator::doesFileExist(const string &fileName) {
    ifstream file(fileName);

    if (!file.good()) {
        cerr << "inputValidator.cpp: the file name " << fileName << " was not found.\n";
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