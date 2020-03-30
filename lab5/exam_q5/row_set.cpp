#include "row_set.hpp"

#include "row_echelon_form.hpp"

void RowSet::SubBuffer(int r, int c)
{
    // TODO
}

void RowSet::DivBuffer(int r, int c)
{
    // TODO
}

void RowSet::ToReducedRowEchelonForm()
{
    to_reduced_row_echelon_form_generic(*this);
}

void RowSet::ShowSparsity(ostream &dst)
{
    // TODO
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