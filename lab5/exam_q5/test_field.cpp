#include "row_set.hpp"
#include "row_set_factory.hpp"

#include <cassert>

int main(int argc, char *argv[])
{
    string field="float";

    if(argc>1){
        field=argv[1];
    }

    RowSet *A = create_row_set(field);
    
    // We need at least one element to perform the tests,
    // in addition to the buffer
    A->Resize(1,1);

    /////////////////////////////////////////
    // Insert tests here

    // TODO - Additive identity: `add(0,1) == `1` : 

    // TODO - Multiplicative identity: `mul(1,1) == `1`

    // TODO - Double negate is an identity: `neg(neg(1)) == 1`

    // TODO - Unit is it's own inverse: ` inv(1) == 1`


}