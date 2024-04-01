#!/bin/bash

for number in {1..2}
do
    ./cipher S ../Test-Cases/Stream-Cipher/"$number"/sc-input-tc-"$number".txt ./Text-Files/tmp.txt ../Test-Cases/Stream-Cipher/"$number"/sc-key-tc-"$number".txt E

    hexdump -C ./Text-Files/tmp.txt > ./Text-Files/tmp2.txt
    if diff_output=$(diff ./Text-Files/tmp2.txt ../Test-Cases/Stream-Cipher/"$number"/sc-encrypted-output-hexdump-tc-"$number".txt); then
        echo "Stream Encryption test $number: No differences found."
    else
        echo "Stream Encryption test $number: Differences found:"
        echo "$diff_output"
    fi
done
