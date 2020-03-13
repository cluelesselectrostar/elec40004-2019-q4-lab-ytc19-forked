#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

g++ test_field.cpp \
    row_set.cpp row_set_factory.cpp row_echelon_form.cpp \
    -o test_field