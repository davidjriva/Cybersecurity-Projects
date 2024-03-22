#!/bin/bash

touch tmp.txt

./cipher B ./PA1_Test/E/B/2/input2.txt tmp.txt ./PA1_Test/E/B/2/key2.txt E

if diff_output=$(diff tmp.txt ./PA1_Test/E/B/2/bout22.txt); then
    echo "No differences found."
else
    echo "Differences found:"
    echo "$diff_output"
fi

