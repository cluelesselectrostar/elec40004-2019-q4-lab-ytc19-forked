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

if (equation.terms.size()<1) {
  return 1;
}

int input_no = 0;
int current;
for (int i=0; i<equation.terms.size(); i++) {
  for (int j=0; j<equation.terms[i].size(); j++) {
    current = equation.terms[i][j];
    if (current > input_no) {
      input_no = current;
    }
  }
}

cerr << "largest input is " << input_no << endl;

uint64_t inputs = 0;
uint64_t max = pow(2,input_no);
SOP *point_equation = &equation;

for (uint64_t inputs = 0; inputs< max ; inputs++) {
  if(SOP_evaluate(point_equation, inputs) == 1){
    cout << inputs << endl;
  }
}

}
