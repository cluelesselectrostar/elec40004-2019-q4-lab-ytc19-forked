#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cinttypes>
#include "SOP.hpp"

using namespace std;

int main() {

string input;
cin >> input;

SOP equation = SOP_from_string(input);
SOP *point_equation = &equation;

if (equation.terms.size()<1) {
  return 1;
}

/* PREPROCESSING */

// Removing impossible terms and repeated terms.
int current;
vector<int> inner;
for (int i=0; i<equation.terms.size(); i++) {
  bool processed = false;
  for (int j=0; j<equation.terms[i].size(); j++) {
    current = equation.terms[i][j];
    inner.push_back(current);
    for (int k=0; k<inner.size(); k++) {
      if (current == -inner[k]) {
        equation.terms[i].clear();
        processed = true;
        break;
      }
      if (current == inner[k]) {
        equation.terms[i][j] = 0;
        processed = true;
      }
    }
    if (processed == true) {
      break;
    }
  }
}

//CERR the processed SOP.
string processed_SOP = SOP_to_string(point_equation);
cerr << "processed SOP is " << processed_SOP << endl;

// Determining the largest number of inputs.
int input_no = 0;
int max_current;
for (int i=0; i<equation.terms.size(); i++) {
  for (int j=0; j<equation.terms[i].size(); j++) {
    current = equation.terms[i][j];
    if (max_current > input_no) {
      input_no = max_current;
    }
  }
}
cerr << "largest input is " << input_no << endl;

uint64_t inputs = 0;
uint64_t max = pow(2, input_no);

for (uint64_t inputs = 0; inputs< max ; inputs++) {
  if(SOP_evaluate(point_equation, inputs) == 1){
    cout << inputs << endl;
  }
}

return 0;

}
