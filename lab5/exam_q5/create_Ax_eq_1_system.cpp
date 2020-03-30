#include "row_set.hpp"
#include "row_set_factory.hpp"

#include <fstream>
#include <cassert>

int main()
{
    RowSet *A=read_row_set(cin);

    int rows=A->RowCount();
    int cols=A->ColCount();
    assert(rows==cols);

    // Create space for 1-vector
    A->Resize(rows, cols+1);

    // Write the 1 column
    A->UnitBuffer();
    for(int i=1; i<=rows; i++){
        A->StoreBuffer(i,cols+1);
    }

    write_row_set(A, cout);   

    delete A;
}