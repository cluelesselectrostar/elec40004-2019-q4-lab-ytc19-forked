#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

g++ calculate_matrix_inverse.cpp \
    row_set.cpp row_set_factory.cpp row_echelon_form.cpp \
    -o calculate_matrix_inverse