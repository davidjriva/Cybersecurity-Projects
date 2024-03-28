#ifndef BLOCK_CIPHER_H
# define BLOCK_CIPHER_H

#include <iostream>
#include <string>   
#include <fstream>
#include <iomanip>
#include <vector>

class BlockCipher {
public: 
    static const size_t BLOCK_SIZE = 16; // defines the size of a block as 16 bytes

    void createBlockCipher(const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName, const std::string &modeOfOperation);
    void encrypt(const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName);
    void decrypt(const std::string &inputFileName, const std::string &outputFileName, const std::string &keyFileName);
    void printFileContents(const std::string &fileName);
    void xorWithKey(char *block, const std::string &key);
    void swapBytes(char *block, const std::string &key);
    void reverseSwapBytes(char *block, std::ifstream &keyFile);
    void readBlock(std::ifstream &inputFile, char *block);
    void padBlock(char *block, std::streamsize bytesRead);
    int removePadding(char *block);
    void printBlockHex(const char *block, size_t blockSize);
    bool isPadding(const char *block, size_t blockSize);
};

#endif