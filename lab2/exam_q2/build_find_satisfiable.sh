#!/bin/bash

set -e

g++ find_satisfiable.cpp SOP.cpp SOP_evaluate.cpp SOP_helpers.cpp -o find_satisfiable;
