#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

g++ -I.. \
     ../convert_to_reduced_row_echelon_form.cpp \
     row_set.cpp row_set_factory.cpp row_echelon_form.cpp \
    -o convert_to_reduced_row_echelon_form
