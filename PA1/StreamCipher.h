#ifndef STREAM_CIPHER_H
# define STREAM_CIPHER_H

#include <iostream>
#include <string>   
#include <fstream>
#include <iomanip>
#include <bitset>

class StreamCipher {
public: 
    void createStreamCipher(const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName, const std::string &modeOfOperation);
    void encrypt(const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName);
    void decrypt(const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName);
};

#endif