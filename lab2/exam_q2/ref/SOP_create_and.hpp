#ifndef SOP_create_and_hpp
#define SOP_create_and_hpp

#include "SOP.hpp"

/*  Sets dst to the SOP representation of an and gate with `N` inputs.
    The inputs chosen should be the first n inputs, i.e. `i1`, `i2`, ... `iN`.
*/
void SOP_create_and(SOP *dst, int N)
{
    dst->terms.clear();
    dst->terms.resize(N);
    for(int i=0; i<N; i++){
        dst->terms[i]=i+1;
    }
}

#endif