#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

dos2unix *.sh ../*.sh

for b in build_*.sh ; do
    ./${b}
done

rm -f ../examples/*.txt
for r in examples/*.txt ; do
    b="$(basename $r .txt)"
    
    cp examples/${b}.txt ../examples/${b}.txt
    < examples/${b}.txt ./create_Ax_eq_1_system | ./convert_to_reduced_row_echelon_form  > ../examples/${b}.Ax_eq_1.reduced.txt
    ./calculate_matrix_inverse < examples/${b}.txt > ../examples/${b}.inverse.txt
    
done

dos2unix ../examples/*.txt