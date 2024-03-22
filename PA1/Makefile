# Files
INPUT_FILE = nasa.txt
INTERMEDIATE_FILE = intermediate.txt
BLOCK_KEY_FILE = key.txt
STREAM_KEY_FILE = streamkey.txt
OUTPUT_FILE = outputFinal.txt

# Make Commands
output: main.o InputValidator.o BlockCipher.o StreamCipher.o
	g++ $^ -o cipher

main.o: main.cpp InputValidator.h BlockCipher.h StreamCipher.h
	g++ -c main.cpp

InputValidator.o: InputValidator.cpp InputValidator.h
	g++ -c InputValidator.cpp

BlockCipher.o: BlockCipher.cpp BlockCipher.h
	g++ -c BlockCipher.cpp

StreamCipher.o: StreamCipher.cpp StreamCipher.h
	g++ -c StreamCipher.cpp

block_encrypt_ex: cipher
	./cipher B $(INPUT_FILE) $(INTERMEDIATE_FILE) $(BLOCK_KEY_FILE) E

block_decrypt_ex: cipher
	./cipher B $(INTERMEDIATE_FILE) $(OUTPUT_FILE) $(BLOCK_KEY_FILE) D

stream_encrypt_ex: cipher
	./cipher S $(INPUT_FILE) $(INTERMEDIATE_FILE) $(STREAM_KEY_FILE) E

stream_decrypt_ex: cipher
	./cipher S $(INTERMEDIATE_FILE) $(OUTPUT_FILE) $(STREAM_KEY_FILE) D

clean:
	rm -f *.o cipher
