#!/bin/bash

set -e

g++ fcw_hub.cpp histogram.cpp lower_case.cpp sentence_reader.cpp -o fcw_hub_test

echo "compiled, now testing with war"

bunzip2 -c war_and_peace.txt.bz2  | ./fcw_hub_test war
