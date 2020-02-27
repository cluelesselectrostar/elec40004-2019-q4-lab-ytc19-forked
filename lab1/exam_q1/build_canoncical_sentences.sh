#!/bin/bash

set -e

g++ canonical_sentences.cpp sentence_reader.cpp -o canonical_sentences
<input.txt ./canonical_sentences >output_actual.txt
diff output_actual.txt output_ref.txt
echo "Success!"
