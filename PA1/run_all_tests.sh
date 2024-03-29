#!/bin/bash

run_block_encrypt_tests.sh
echo
run_block_decrypt_tests.sh

echo

run_stream_encrypt_tests.sh
echo
run_stream_decrypt_tests.sh
