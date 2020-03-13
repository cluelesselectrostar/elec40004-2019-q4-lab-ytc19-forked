#include "row_set.hpp"
#include "row_set_factory.hpp"
#include "row_echelon_form.hpp"

int main(int argc, char **argv)
{
    int use_generic=0;

    if(argc>1){
        use_generic=atoi(argv[1]);
    }

    RowSet *A=read_row_set(cin);

    if(use_generic){
        to_reduced_row_echelon_form_generic(*A);
    }else{
        A->ToReducedRowEchelonForm();
    }

    write_row_set(A, cout);

    delete A;
}