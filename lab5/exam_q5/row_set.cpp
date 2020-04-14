#include "row_set.hpp"

#include "row_echelon_form.hpp"

// B = B - A[r,c] = -(-B + A(r,c))
void RowSet::SubBuffer(int r, int c)
{
  NegBuffer();
  AddBuffer(r,c);
  NegBuffer();
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

// Prints the given row to `dst`. The row should all be on one
// line, with one space between entries. No end-of-line character
// should be added.
void RowSet::WriteRow(int row, ostream &dst)
{
    for (int i=0; i<ColCount(); i++) {
      LoadBuffer(row, i);
      if (i== ColCount()-1) {
        WriteBuffer(dst);
      }
      WriteBuffer(dst);
      dst << " ";
    }
}

void RowSet::WriteMatrix(ostream &dst)
{
    for(int r=1;r<=RowCount(); r++){
        WriteRow(r, dst);
        dst<<endl;
    }
}
