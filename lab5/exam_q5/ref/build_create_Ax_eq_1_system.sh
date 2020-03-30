#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

g++ -I.. \
    ../create_Ax_eq_1_system.cpp \
    row_set.cpp row_set_factory.cpp row_echelon_form.cpp \
    -o create_Ax_eq_1_system