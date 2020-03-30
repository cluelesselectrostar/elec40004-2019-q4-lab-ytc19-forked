#ifndef row_set_hpp
#define row_set_hpp

#include <iostream>

using namespace std;

/*
    A class to represent a matrix "A" over some field of
    numbers. Mathematically, a field is something like the
    reals, the rationals, complex numbers, bits, or integers
    modulo a prime.

    Each matrix A consists of an ordered collection of rows.
    From a notation point of view we have:
    - A : The entire matrix of NumRows() x NumCols() elements
    - A[r] : Row r of the matrix, where 1<=r<=NumRows()
    - A[r,c] : Element r,c of the matrix, where 1<=r<=NumRows() and 1<=c<=NumCols()

    To allow algorithms to be independent of the number field,
    there is no way to get or set values from the field. To
    allow for scalar calculations, there is a scalar internal member
    called the buffer (or B), which holds a single value, and
    allows for maths to be performed.
*/
class RowSet
{
public:
    virtual ~RowSet()
    {}

    // Returns a name describing the field, e.g. "float", "complex<double>"
    virtual std::string FieldName() const=0;

    // Return number of rows in A
    virtual int RowCount() const =0;

    // Return the number of columns in A
    virtual int ColCount() const =0;

    // Change the dimensions of the matrix.
    // Any additional entries are set to zero
    virtual void Resize(int rows, int cols) =0;

    //////////////////////////////////////////
    // Row and element operations

    // Return true if A[r,c]==1
    virtual bool IsUnit(int r, int c) const=0;
    
    // Return true if A[r,c]==0
    virtual bool IsZero(int r, int c) const=0;

    // Temp=A[r1];
    // A[r1]=A[r2];
    // A[r2]=Temp;
    virtual void SwapRows(int r1, int r2) =0;

    // A[row] *= B
    virtual void MultiplyRow(int row) =0;

    // A[row] += A[src_row] * B
    virtual void AddMultipleOfRow(int row, int src_row) =0;

    
    ////////////////////////////////////////
    // Buffer operations

    // B = 0
    virtual void ZeroBuffer() =0;

    // B = 1
    virtual void UnitBuffer() =0;

    // B = A[r,c]
    virtual void LoadBuffer(int r, int c) =0;

    // A[r,c] = B
    virtual void StoreBuffer(int r, int c) =0;

    // swap( B , A[r,c] )
    virtual void SwapBuffer(int r, int c) =0;

    // B = B * A[r,c]
    virtual void MulBuffer(int r, int c) =0;

    // B = B * A[r,c]
    virtual void AddBuffer(int r, int c) =0;

    // B = - B
    virtual void NegBuffer() =0;

    // B = 1 / B
    // Note that this is only defined if B is not zero
    virtual void InvBuffer() =0;

    // B = max(|B|,|A[r,c]|)
    // Returns true if B was modified
    virtual bool MaxAbsBuffer(int r, int c) =0;

    // Reads a single element from the stream
    // The exact format is unknown, but it is guaranteed that
    // it will not contain spaces.
    virtual istream &ReadBuffer(istream &dst) =0;

    // Prints the contents of the buffer to the destination
    // The exact format is unknown, but it is guaranteed that
    // it will not contain spaces.
    virtual ostream &WriteBuffer(ostream &dst) const =0;

    ///////////////////////////////
    // Non-virtual buffer functions

    // B = B - A[r,c]
    void SubBuffer(int r, int c);

    // B = B / A[r,c]
    void DivBuffer(int r, int c);


    /////////////////////////////////////////////
    // Overall matrix operations. Derived classes may provide
    // more efficient versions of these operations

    // Convert the matrix to reduced row echelon form
    // RowSet provides a generic but slow implementation.
    virtual void ToReducedRowEchelonForm();

    /////////////////////////////////////////////
    // Non-virtual helpers

    // Print a textual representation of the matrix, with one line per row
    // and one character per column.
    // For a given value x, the value should be:
    // ' ' - Zero entry.
    // '1' - One entry. 
    // 'X' - Anything else.
    void ShowSparsity(ostream &dst);

    // Prints the given row to `dst`. The row should all be on one
    // line, with one space between entries. No end-of-line character
    // should be added.
    void WriteRow(int row, ostream &dst);

    // Prints the matrix to `dst`.
    void WriteMatrix(ostream &dst);
};

#endif
