#include "SOP.hpp"

#include "SOP_helpers.hpp"

SOP SOP_from_string(string equation)
{
    SOP res;
    int pos=0;
    int len=equation.size();
    bool negate=false;
    while(pos < len){
        char curr=equation[pos];
        if(curr==' '){
            // Do nothing, ignore space
            pos=pos+1;
        }else if(curr=='~'){
            // Negate the next variable
            negate=!negate;
            pos=pos+1;
        }else if(curr=='T'){
            assert(!negate);
            // Make sure there is at least a product ...
            if(res.terms.empty()){
                res.terms.push_back({}); // Create a new empty product
            }
            //... and push onto the back of the last product
            res.terms.back().push_back(0);
            pos=pos+1;
        }else if(curr=='i'){
            // Start of a variable
            pos=pos+1; // skip over the 'i' 
            string number; // Build up the digits following the i
            while(pos < len){
                curr=equation[pos];
                if(isdigit(curr)){
                    number.push_back(curr);
                    pos=pos+1;
                }else{
                    break;
                }
            }
            // Extract the actual index
            int index=stoi(number);
            if(negate){
                index=-index;
            }
            // Make sure there is at least a product ...
            if(res.terms.empty()){
                res.terms.push_back({}); // Create a new empty product
            }
            //... and push onto the back of the last product
            res.terms.back().push_back(index);
            // Reset the negation flag
            negate=false;
        }else if(curr=='|'){
            // Create a new empty product
            assert(res.terms.size() > 0);
            res.terms.push_back({});
            pos=pos+1; 
        }else if(curr=='&'){
            // Continue an existing product
            assert(res.terms.back().size() > 0);
            pos=pos+1;
        }
    }
    return res;
}

bool SOP_structural_equals(SOP *a, SOP *b)
{
  return a->terms == b->terms;
}

string SOP_to_string(SOP *equation)
{
  string res;
  for(int i=0; i<equation->terms.size(); i++){
    if(i!=0){
      res=res+"|";
    }
    if(equation->terms[i].empty()){
        res=res+"T";
    }else{
        for(int j=0; j<equation->terms[i].size(); j++){
            if(j!=0){
                res=res+"&";
            }
            int selector = equation->terms[i][j];
            if(selector==0){
                res=res+"T";
            }else{
                if(selector<0){
                res=res+"~";
                }
                res=res+"i"+to_string(abs(selector));
            }
        }
    }
  }
  return res;
}

bool SOP_functional_equals(SOP *a, SOP *b)
{
  int width=max(SOP_largest_input_index(a), SOP_largest_input_index(b));
  assert(width <= 60);

  uint64_t upper = uint64_t(1) << width;
  for(uint64_t input=0; input<upper; input++){
    bool va=SOP_evaluate(a, input);
    bool vb=SOP_evaluate(b, input);
    if(va!=vb){
      return false;
    }
  }
  return true;
}