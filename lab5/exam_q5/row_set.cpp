#include "row_set.hpp"

#include "row_echelon_form.hpp"

void RowSet::SubBuffer(int r, int c)
{
    // TODO
}

void RowSet::DivBuffer(int r, int c)
{
	SwapBuffer(r,c);
	bool bufferzero = IsZero(r,c);
	SwapBuffer(r,c);
	if(bufferzero){
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
		dst << "|";
		for(int c=1; c<=ColCount; c++){
			if(IsZero(r,c)){
				dst << " ";
			}else if(IsUnit(r,c)){
				dst << "1";
			}else{
				dst << "x";
			}
		}
		dst << "|" << endl;
	}
}

void RowSet::WriteRow(int row, ostream &dst)
{
    // TODO
}

void RowSet::WriteMatrix(ostream &dst)
{
    for(int r=1;r<=RowCount(); r++){
        WriteRow(r, dst);
        dst<<endl;
    }
}
