#include "SOP.hpp"

bool SOP_evaluate(SOP *equation, uint64_t inputs)
{
  bool sum=false;
  for(int i=0; i < equation->terms.size() ; i++){
    bool product=true;
    for(int j=0; j<equation->terms[i].size(); j++){
        int selector=equation->terms[i][j];
        if(selector==0){
          // Represents true; do nothing
        }else{
          bool negate = selector < 0;
          int index = abs(selector)-1;
          assert(index<64);
          bool bit = (inputs>>index) & 1;
          if(negate){
              bit = !bit;
          }

          product = product && bit;
        }
    }
    sum = sum || product;
  }
  return sum;
}
