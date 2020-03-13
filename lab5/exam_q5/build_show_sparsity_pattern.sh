#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

g++ show_sparsity_pattern.cpp \
     row_set.cpp row_set_factory.cpp row_echelon_form.cpp \
    -o show_sparsity_pattern