#include "row_set.hpp"

#include "row_echelon_form.hpp"

void RowSet::SubBuffer(int r, int c)
{
    // B = B - A[r,c]
    //   = - (-B + A[r,c])

    NegBuffer();
    AddBuffer(r,c);
    NegBuffer();
}

void RowSet::DivBuffer(int r, int c)
{
    // B = B / A[r,c]
    //   = 1 / ( 1/B * A[r,c] )

    SwapBuffer(r,c);
    bool isZero=IsZero(r,c);
    SwapBuffer(r,c);

    if(isZero){
        // do nothing, leave as zero
    }else{
        InvBuffer(); 
        MulBuffer(r,c);
        InvBuffer();
    }
}

void RowSet::ToReducedRowEchelonForm()
{
    to_reduced_row_echelon_form_generic(*this);
}

void RowSet::ShowSparsity(ostream &dst)
{
    for(int r=1; r<=RowCount(); r++){
        dst<<"|";
        for(int c=1; c<=ColCount(); c++){
            if(IsZero(r,c)){
                dst<<" ";
            }else if(IsUnit(r,c)){
                dst<<"1";
            }else{
                dst<<"X";
            }
        }
        dst<<"|"<<endl;
    }
}

void RowSet::WriteRow(int row, ostream &dst)
{
    for(int c=1; c<=ColCount(); c++){
        if(c!=1){
            dst<<" ";
        }
        LoadBuffer(row,c);
        WriteBuffer(dst);
    }
}

void RowSet::WriteMatrix(ostream &dst)
{
    for(int r=1;r<=RowCount(); r++){
        WriteRow(r, dst);
        dst<<endl;
    }
}