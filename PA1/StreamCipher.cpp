# include "StreamCipher.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cerr;
using std::bitset;
using std::string;

void StreamCipher::createStreamCipher(const string &inputFileName, const string &outputFileName, const string &keyFileName, const string &modeOfOperation) {
    if(modeOfOperation == "E"){
        encrypt(inputFileName, outputFileName, keyFileName);
    } else {
        decrypt(inputFileName, outputFileName, keyFileName);
    }
}

void StreamCipher::encrypt(const string &inputFileName, const string &outputFileName, const string &keyFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    ifstream keyFile(keyFileName);

    char inputChar, keyChar, outputChar;
    bitset<8> inputBit, keyBit, outputBit;

    while (inputFile.get(inputChar)) {
        // read a bit from the key 
        if (!keyFile.get(keyChar)) {
            keyFile.clear();
            keyFile.seekg(0, std::ios::beg);
            keyFile.get(keyChar);
        }

        // XOR each input char bits of the input byte with the corresponding bits of the key byte
        inputBit = inputChar;
        keyBit = keyChar;
        outputBit = inputBit ^ keyBit;

        outputChar = static_cast<char>(outputBit.to_ulong());
        outputFile.put(outputChar);
    }

    // Close all the files
    inputFile.close();
    outputFile.close();
    keyFile.close();
}

void StreamCipher::decrypt(const string &inputFileName, const string &outputFileName, const string &keyFileName) {
    // Decryption is the same as encryption in this stream cipher
    encrypt(inputFileName, outputFileName, keyFileName);
}