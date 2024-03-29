#!/bin/bash

for number in {1..2}
do
    ./cipher S ./Test-Cases/Stream-Cipher/"$number"/sc-encrypted-output-tc-"$number".txt ./Text-Files/tmp.txt ./Test-Cases/Stream-Cipher/"$number"/sc-key-tc-"$number".txt D

    if diff_output=$(diff ./Text-Files/tmp.txt ./Test-Cases/Stream-Cipher/"$number"/sc-decrypted-output-tc-"$number".txt); then
        echo "Stream Decryption test $number: No differences found."
    else
        echo "Stream Decryption test $number: Differences found:"
        echo "$diff_output"
    fi
done