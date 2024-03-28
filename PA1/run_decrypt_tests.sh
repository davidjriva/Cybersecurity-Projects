#!/bin/bash

for number in {1..3}
do
    touch tmp.txt

    ./cipher B ./Test-Cases/Block-Cipher/"$number"/bc-encrypted-output-tc-"$number".txt tmp.txt ./Test-Cases/Block-Cipher/"$number"/bc-key-tc-"$number".txt D

    if diff_output=$(diff tmp.txt ./Test-Cases/Block-Cipher/"$number"/bc-decrypted-output-tc-"$number".txt); then
        echo "Decryption test $number: No differences found."
    else
        echo "Decryption test $number: Differences found:"
        echo "$diff_output"
    fi
done