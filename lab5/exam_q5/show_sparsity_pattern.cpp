#include "row_set.hpp"
#include "row_set_factory.hpp"

int main()
{
    RowSet *A=read_row_set(cin);

    A->ShowSparsity(cout);

    delete A;
}