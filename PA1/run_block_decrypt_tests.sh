#!/bin/bash

for number in {1..3}
do
    ./cipher B ../Test-Cases/Block-Cipher/"$number"/bc-encrypted-output-tc-"$number".txt ./Text-Files/tmp.txt ../Test-Cases/Block-Cipher/"$number"/bc-key-tc-"$number".txt D

    if diff_output=$(diff ./Text-Files/tmp.txt ../Test-Cases/Block-Cipher/"$number"/bc-decrypted-output-tc-"$number".txt); then
        echo "Block Decryption test $number: No differences found."
    else
        echo "Block Decryption test $number: Differences found:"
        echo "$diff_output"
    fi
done