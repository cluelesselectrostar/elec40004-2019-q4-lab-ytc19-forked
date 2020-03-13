#ifndef to_lower_echelon_form_generic_hpp
#define to_lower_echelon_form_generic_hpp

#include "row_set.hpp"
#include "row_set_factory.hpp"

#include <cassert>


void to_reduced_row_echelon_form_generic(RowSet &A)
{
    int r=A.RowCount();
    int c=A.ColCount();

    cerr<<"Input matrix\n";
    write_row_set(&A, cerr);

    int h = 1; /* Initialization of the pivot row */
    int k = 1; /* Initialization of the pivot column */

    while( h <= r && k <= c){
        /* Find the k-th pivot: */
        //i_max := argmax (i = h ... m, abs(A[i, k]))
        int i_max = h;
        A.ZeroBuffer();
        for(int i=h; i<=r; i++){
            if(A.MaxAbsBuffer(i,k)){
                i_max=i;
            }
        }

        if( A.IsZero(i_max,k)){
            /* No pivot in this column, pass to next column */
            cerr<<"col "<<k<<" : no pivot.\n";
            k = k+1;
        }else{
            cerr<<"col "<<k<<" : pivot = "<<i_max<<"\n";

            A.SwapRows(h, i_max);

            cerr<<"Swapped: "<<endl;
            write_row_set(&A, cerr);


            assert(!A.IsZero(h,k));
            A.LoadBuffer(h,k);
            A.InvBuffer();
            A.MultiplyRow(h);

            // Set to exactly 1
            A.UnitBuffer();
            A.StoreBuffer(h,k);

            /* Do for all rows except pivot: */
            for(int i = 1 ; i<=r ; i++){
                if( i!= h && !A.IsZero(i,k)){
                    // float f = m_A[i][k] / m_A[h][k];
                    assert(!A.IsZero(h,k));
                    A.LoadBuffer(h,k);
                    A.InvBuffer();
                    A.MulBuffer(i,k);
                    A.NegBuffer();
                    cerr<<" row "<<i<<", s=";
                    A.WriteBuffer(cerr)<<endl;

                    A.AddMultipleOfRow(i, h);

                    // To keep things clean, force to exactly zero
                    A.ZeroBuffer();
                    A.StoreBuffer(i,k);
                }
            }

            /* Increase pivot row and column */
            h = h + 1;
            k = k + 1;

            write_row_set(&A, cerr);
        }
    }
}


#endif