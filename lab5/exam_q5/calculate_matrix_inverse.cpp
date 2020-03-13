#include "row_set.hpp"
#include "row_set_factory.hpp"

int main()
{
    RowSet *A=read_row_set(cin);

    if(A->RowCount()!=A->ColCount()){
        cerr<<"Matrix is not square."<<endl;
        exit(1);
    }

    int rows=A->RowCount();
    int cols=A->ColCount();

    // Augment with identity matrix
    A->Resize(rows, 2*cols);
    A->UnitBuffer();
    for(int r=1; r<=rows; r++){
        A->StoreBuffer(r,cols+r);
    }

    // Convert to reduced lower echelon form
    A->ToReducedRowEchelonForm();

    write_row_set(A, cerr);

    // Check that left matrix is the identity matrix
    for(int r=1; r<=rows; r++){
        for(int c=1; c<=cols; c++){
            if( r==c ){
                if(!A->IsUnit(r,c)){
                    cerr<<"Matrix is not invertible at "<<r<<","<<c<<endl;
                    exit(1);
                }
            }else{
                if(!A->IsZero(r,c)){
                    cerr<<"Matrix is not invertible at "<<r<<","<<c<<endl;
                    exit(1);
                }
            }
        }
    }

    // Copy the solution into the left-hand side
    for(int r=1; r<=rows; r++){
        for(int c=1; c<=cols; c++){
            A->LoadBuffer(r,c+cols);
            A->StoreBuffer(r,c);
        }
    }

    // Resize the matrix to get back to a square
    A->Resize(rows,cols);

    write_row_set(A, cout);

    delete A;
}