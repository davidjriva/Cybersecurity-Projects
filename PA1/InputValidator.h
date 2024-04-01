#ifndef INPUT_VALIDATOR_H
# define INPUT_VALIDATOR_H

#include <iostream>
#include <string>   
#include <fstream>

class InputValidator {
public: 
    void validateAllInputs(const std::string &cipherType, const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName, const std::string &modeOfOperation);
    void validateCipherType(const std::string &cipherType);
    void doesFileExist(const std::string &fileName, const std::string &errorMessage);
    bool containsNewLine(const std::string &str);
    void isKeyFileValid(const std::string &keyFileName);
    void validateModeOfOperation(const std::string &modeOfOperation);
};

#endif