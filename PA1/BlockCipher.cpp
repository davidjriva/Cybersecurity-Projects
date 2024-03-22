# include "BlockCipher.h"

using std::cout;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::streamsize;
using std::swap;

void BlockCipher::createBlockCipher(const string &inputFileName, const string &outputFileName, const string &keyFileName, const string &modeOfOperation) {
    if(modeOfOperation == "E"){
        encrypt(inputFileName, outputFileName, keyFileName);
    } else if (modeOfOperation == "D"){
        decrypt(inputFileName, outputFileName, keyFileName);
    } else {
        cerr << "BlockCipher.cpp: Given mode of operation " << modeOfOperation << " is invalid.\n";
        exit(1);
    }
}

// pad (if required) --> encrypt (using XOR) --> swap bytes
void BlockCipher::encrypt(const string &inputFileName, const string &outputFileName, const string &keyFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    ifstream keyFile(keyFileName);

    if (!inputFile || !outputFile || !keyFile) {
        cerr << "Blockcipher.cpp: Error opening files.\n";
        exit(1);
    }   

    // Check key size
    keyFile.seekg(0, keyFile.end);
    size_t keySize = keyFile.tellg();
    keyFile.seekg(0, keyFile.beg);

    if (keySize != BLOCK_SIZE) {
        cerr << "Blockcipher.cpp: Key size should be " << BLOCK_SIZE << " bytes.\n";
        exit(1);
    }

    char block[BLOCK_SIZE];

    while (inputFile.good()) {
        // Read a block
        readBlock(inputFile, block);

        // If a block only has padding then break out of the loop.
        // This occurs when the message read in the previous round 
        // is exactly the BLOCK_SIZE meaning that no EOF bit is set
        if (isPadding(block, BLOCK_SIZE)) {
            break;
        }

        // Encrypt using XOR
        xorWithKey(block, keyFile);

        // Reset keyFile stream state due to alterations in reverseSwapBytes()
        keyFile.clear();
        keyFile.seekg(0, ios::beg);

        // Swap bytes
        swapBytes(block, keyFile);

        // Reset keyFile stream state due to alterations in reverseSwapBytes()
        keyFile.clear();
        keyFile.seekg(0, ios::beg);

        // Write to the output file
        outputFile.write(block, BLOCK_SIZE);
    }

    // Close files
    inputFile.close();
    outputFile.close();
    keyFile.close();
}

void BlockCipher::decrypt(const string &inputFileName, const string &outputFileName, const string &keyFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    ifstream keyFile(keyFileName);

    if (!inputFile || !outputFile || !keyFile) {
        cerr << "Blockcipher.cpp: Error opening files.\n";
        exit(1);
    }   

    // Check key size
    keyFile.seekg(0, keyFile.end);
    size_t keySize = keyFile.tellg();
    keyFile.seekg(0, keyFile.beg);

    if (keySize != BLOCK_SIZE) {
        cerr << "Blockcipher.cpp: Key size should be " << BLOCK_SIZE << " bytes.\n";
        exit(1);
    }

    char block[BLOCK_SIZE];

    while (inputFile.good()) {
        // Read a block
        readBlock(inputFile, block);

        // If a block only has padding then break out of the loop.
        // This occurs when the message read in the previous round 
        // is exactly the BLOCK_SIZE meaning that no EOF bit is set
        if (isPadding(block, BLOCK_SIZE)) {
            break;
        }

        // Reverse swap bytes
        swapBytes(block, keyFile);

        // Reset keyFile stream state due to alterations in reverseSwapBytes()
        keyFile.clear();
        keyFile.seekg(0, ios::beg);

        xorWithKey(block, keyFile);

        // Reset keyFile stream state due to alterations in reverseSwapBytes()
        keyFile.clear();
        keyFile.seekg(0, ios::beg);

        int paddingCount = removePadding(block);

        outputFile.write(block, BLOCK_SIZE - paddingCount);
    }

    inputFile.close();
    outputFile.close();
    keyFile.close();
}

bool BlockCipher::isPadding(const char *block, size_t blockSize) {
    for (size_t i = 0; i < blockSize; ++i) {
        int ascii = static_cast<int>(static_cast<unsigned char>(block[i]));

        if (ascii != 0x81) {
            return false;  // Block contains a non-padding character
        }
    }
    return true;  // Block contains only padding
}

int BlockCipher::removePadding(char *block) {
    int paddingCount = 0;
    // Start from the end of the block
    for (int i = BLOCK_SIZE - 1; i >= 0; --i) {
        int ascii = static_cast<int>(static_cast<unsigned char>(block[i]));
        if (ascii == 0x81) {
            block[i] = 0x00;
            paddingCount++;
        } else {
            // Stop when a non-padding byte is encountered
            break;
        }
    }

    return paddingCount;
}

void BlockCipher::printBlockHex(const char *block, size_t blockSize) {
    std::cout << "Block as Hex: ";
    
    for (size_t i = 0; i < blockSize; ++i) {
        std::cout << "0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(block[i])) << " ";
    }

    std::cout << "\n";
}

void BlockCipher::readBlock(ifstream &inputFile, char *block) {
    // Read a block size of 128 bits (16 bytes)
    inputFile.read(block, BLOCK_SIZE);

    // Check number of characters extracted
    streamsize bytesRead = inputFile.gcount();
    
    // If the bytes read is less than a full block, then add padding
    if (bytesRead < BLOCK_SIZE) {
        padBlock(block, bytesRead);
    }
}

void BlockCipher::padBlock(char *block, streamsize bytesRead) {
    // Pad with 0x81
    for (streamsize i = bytesRead; i < BLOCK_SIZE; i++) {
        block[i] += char(128);
    }
}

void BlockCipher::xorWithKey(char *block, ifstream &keyFile) {
    char keyBlock[BLOCK_SIZE];
    keyFile.read(keyBlock, BLOCK_SIZE);

    // XOR operation
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= keyBlock[i];
    }
}

void BlockCipher::swapBytes(char *block, ifstream &keyFile) {
    char keyChar;
    keyFile.get(keyChar);

    
    // Establish start & end pointers
    int start = 0;
    int end = BLOCK_SIZE - 1;

    while (start < end) {
        cout << "keyChar= " << keyChar << std::endl;
        // Check if ASCII val of the key char is even or odd
        bool shouldSwap = (static_cast<int>(keyChar) % 2 == 1);

        if (shouldSwap) {
            // Swap bytes
            char placeHolder = block[end];
            block[end] = block[start];
            block[start] = placeHolder;
            
            // Only move the end pointer on a swap
            --end;
        }

        // Move the start pointer
        ++start;

        // Read the next key character
        keyFile.get(keyChar);

        // Restart from the first byte of the keyfile if it has been exhausted
        if (keyFile.eof()) {
            cout << "END OF KEY FILE!" << std::endl;
            // Clear the EOF flag and reset to the beginning
            keyFile.clear();
            keyFile.seekg(0, std::ios::beg);
        }
    }
}