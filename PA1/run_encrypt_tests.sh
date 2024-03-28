#!/bin/bash

for number in {1..3}
do
    touch tmp.txt

    ./cipher B ./Test-Cases/Block-Cipher/"$number"/bc-input-tc-"$number".txt tmp.txt ./Test-Cases/Block-Cipher/"$number"/bc-key-tc-"$number".txt E

    hexdump -C tmp.txt > tmp2.txt
    if diff_output=$(diff tmp2.txt ./Test-Cases/Block-Cipher/"$number"/bc-encrypted-output-hexdump-tc-"$number".txt); then
        echo "Encryption test $number: No differences found."
    else
        echo "Encryption test $number: Differences found:"
        echo "$diff_output"
    fi
done
