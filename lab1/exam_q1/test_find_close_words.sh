#!/bin/bash

set -e

g++ find_close_words.cpp histogram.cpp lower_case.cpp sentence_reader.cpp -o fcw
g++ find_close_words.cpp histogram.cpp lower_case.cpp sentence_reader.cpp -o find_close_words

echo "compiled, now testing with teapot"

./find_close_words teapot <input.txt
./fcw cat <alice.txt
