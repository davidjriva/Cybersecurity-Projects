#!/bin/bash

for number in {1..3}
do
    ./cipher B ./Test-Cases/Block-Cipher/"$number"/bc-input-tc-"$number".txt ./Text-Files/tmp.txt ./Test-Cases/Block-Cipher/"$number"/bc-key-tc-"$number".txt E

    hexdump -C ./Text-Files/tmp.txt > ./Text-Files/tmp2.txt
    if diff_output=$(diff ./Text-Files/tmp2.txt ./Test-Cases/Block-Cipher/"$number"/bc-encrypted-output-hexdump-tc-"$number".txt); then
        echo "Block Encryption test $number: No differences found."
    else
        echo "Block Encryption test $number: Differences found:"
        echo "$diff_output"
    fi
done
