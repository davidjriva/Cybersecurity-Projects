# include <iostream>
# include "InputValidator.h"
# include "BlockCipher.h"
# include "StreamCipher.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check for five arguments (first arg is the program name)
    if (argc != 6) {
        cerr << "main.cpp: Please input five and only five arguments.\n";
        return 1;
    }

    string cipherType = argv[1];
    string inputFileName = argv[2];
    string outputFileName = argv[3];
    string keyFileName = argv[4];
    string modeOfOperation = argv[5];
    
    // Determine if inputs are valid for each of the args
    InputValidator validator;
    validator.validateAllInputs(cipherType, inputFileName, outputFileName, keyFileName, modeOfOperation);

    if (cipherType == "B") {
        BlockCipher blockCipher;
        blockCipher.createBlockCipher(inputFileName, outputFileName, keyFileName, modeOfOperation);
    } else if (cipherType == "S") {
        StreamCipher streamCipher;
        streamCipher.createStreamCipher(inputFileName, outputFileName, keyFileName, modeOfOperation);
    } else {
        cerr << "Invalid Function Type";
        return 1;
    }

    return 0;
}