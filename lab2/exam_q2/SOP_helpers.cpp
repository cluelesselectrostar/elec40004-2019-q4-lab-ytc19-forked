#include "SOP.hpp"
#include "SOP_helpers.hpp"
using namespace std;

//returns the max_input_index of an SOP, i.e. the maximum number of inputs involved.

int SOP_largest_input_index(SOP *a) {
  int max_index = 0;

  for (int i=0; i<a->terms.size(); i++) {
    for (int j=0; j<a->terms[i].size(); j++) {
      max_index = max(max_index, a->terms[i][j]);
    }
  }

  return max_index;
}
