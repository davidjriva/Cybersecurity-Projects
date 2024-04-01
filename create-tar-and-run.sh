#!/bin/bash

rm -rf riva-david.tar.gz

tar -cvzf riva-david.tar.gz ./PA1

./submission-grader.sh riva-david.tar.gz