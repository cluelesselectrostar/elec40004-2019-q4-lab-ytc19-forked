#include "SOP_helpers.hpp"

int SOP_largest_input_index(SOP *a)
{
  int max_index=0;
  for(int i=0; i<a->terms.size(); i++){
    for(int j=0; j<a->terms[i].size(); j++){
      max_index = max(max_index,abs(a->terms[i][j]));
    }
  }
  return max_index;
}