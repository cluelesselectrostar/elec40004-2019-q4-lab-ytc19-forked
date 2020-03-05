#!/bin/bash

set -e

g++ find_close_words_large.cpp histogram.cpp lower_case.cpp sentence_reader.cpp -o fcwl
g++ find_close_words_large.cpp histogram.cpp lower_case.cpp sentence_reader.cpp -o find_close_words_large

echo "compiled, now testing with teapot"
