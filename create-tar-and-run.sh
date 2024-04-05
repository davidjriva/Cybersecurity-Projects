#!/bin/bash
rm -rf ./PA1/riva-david.tar.gz

tar -cvzf riva-david.tar.gz ./PA1
mv riva-david.tar.gz ./PA1

./PA1/submission-grader.sh ./PA1/riva-david.tar.gz
