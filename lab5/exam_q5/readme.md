Overview
========

(Reading: 50 minutes)

Linear algebra is used in many engineering applications, where
it is used to solve inverse problems and systems of equations.
While there are many advanced algorithms, basic Gaussian
(or Gauss-Jordan) elimination is still often used to solve
computational problems. This is particularly true when
operating over different number fields, beyond real and
complex numbers.

Our goal here is to create a framework where we can implement
algorithms like Gauss-Jordan, equation solving, and inversion once,
but then have them operate on matrices over any field, even fields
you have never heard of and don't really understand.

_Meta-note:_
_This question is skewed towards understanding a complex API and_
_dealing with abstraction; the code edits for the most part are not too_
_complex, and even the translation in part C is quite straightforward_
_once you understand what is going on. The maths being used here is_
_relatively simple, even if you didn't understand all of the deeper_
_discussion of linear algebra in this years maths. Treated as an *algorithm*,_
_the maths required for solving simultanuous equations is at a secondary_
_school level._

Elementary row operations
-------------------------

We will represent matrices as lists of `R` rows. Each
row has `C` scalar elements.

### Matrix indexing

A given matrix `A` has `R` rows and `C` columns. We will use two types
of indices into a matrix:

- `A[r]` for `1<=r<=R` : Refers to row `r` of the matrix.
- `A[r,c]` for `1<=r<=R,1<=c<=C` : Refers to the element at row `r` and column `c`.

### Row operations

Three row operations are needed for Gauss-Jordan elimination:

1. `swap(A[i],A[j])` : Swaps rows `i` and `j` within matrix A.
2. `A[i] = A[i]*f` : Multiply the given row `i` with a scalar `f`.
3. `A[i] = A[i] + A[j]*f` : Multiply row `j` with a scalar `f` and add it to row `f`.

### Reduced row echelon form

Gauss-Jordan elimination is used to get a matrix in "row echelon form",
or into "reduced row echelon form". Here we will concentrate on the
reduced row echelon form. The term "leading entry" is the first element
in a row which is non-zero, reading from left to right. A matrix is in
row echelon form if:

1. All non-zero rows are above all zero rows.
2. The leading entry of a row is to the right of the leading entry of the row above it.
3. All elements in a column below a leading entry are zero.

When the matrix is square this is the same as the upper triangular
matrix requirements you have seen in maths, .

Extra conditions for **reduced** row echelon form are:

4. The leading-entry of a non-zero row is 1.
5. Each leading entry is the only non-zero entry in its column.

If we consider these matrices:
```
  A         B          C        D          E            F
1 3 1     1 3 1     1 2 0     1 0 0     1 0 0 3     1 0 0 4 5
0 2 1     0 1 0     0 1 0     0 1 0     0 1 0 2     0 1 0 1 0
3 0 2     0 0 2     0 0 1     0 0 1     0 0 1 2     0 0 0 0 1
```
- `A` is not in reduced row form due the entry 3 in the first column.
- `B` is in echelon form, but not reduced echelon form due to 2 in the bottom right.
- `C` is in echelon form, but not reduced echelon form due to the 2 at the top of the second column.
- `D`, `E`, and `F` are in reduced echelon form.

Reduced row echelon form is not very interesting for square matrices,
as it is just the identity matrix. However, we often use Gauss-Jordan
to put an augmented matrix into reduced row echelon form, so that
the answer appears to the right of the identity matrix.

For example, we can invert a square matrix by creating the augumented
matrix `|A|I|`. If we bring it into reduced echelon form, then it will
contain `|I|A^-1|`, so the matrix inverse will be produced. If the
left-hand side is _not_ `I`, then the matrix was not invertible.

Given an $nxn$ matrix A and an $nx1$ matrix b we can solve the equation
`A x = b` by constructing the augmented matrix `|A|b|`. Once in reduced echelon
form this will be `|I|x|`, so the solution can be read out. If the left-hand
side is _not_ `I`, then the system does not have a unique solution, and
we could determine whether it has infinite or zero solutions by looking at
the reduced echelon form.

### Gauss-Jordan elimination

To convert a matrix to reduced row echelon form, we perform a sequence of
row operations. You have already done this process manually in Maths, but
we need a formal algorithm, The following pseudo-code captures this process - it is
based on the (Gaussian elimination pseudo-code from Wikipedia)[https://en.wikipedia.org/wiki/Gaussian_elimination], with the following changes:

- Updated to bring the matrix into full reduced form
- Additions to ensure final entries are exactly 1 or 0, even with floating-point rounding errors.
- Row operations are made explicit, rather than using loops

```
h <- 1
k <- 1
while h <= R and k <= C
    # Find the largest absolute value in column k for rows h..m
    i_max = h
    for i = h..m
        if abs(A[h,k]) > abs(A[i_max,k])
            i_max = i
    
    # Check if we have a non-zero pivot
    if abs(A[i_max,k]) = 0
        # No pivot, move onto next column, but stay in same row
        k = k + 1  
    else
        # Bring the pivot row to the top
        swap(A[h],A[i_max])   # Type 1 row operation

        # Normalise the leading-term pivot row to 1
        s = 1 / A[h,k]
        A[h] = A[h] * s    # Type 2 row operation
        # Make sure column k is _exactly_ 1, even with rounding errors
        A[h,k] = 1         

        # Subtract pivot out of all the other rows
        for i = 1..R
            if i!=h and A[i,k]!=0
                s = - A[i,k] / A[h,k] 
                A[i] = A[i] + s * A[h]   # Type 3 row operation
                # Make sure column j is _exactly_ 1, even with floating-point
                A[i,k] = 0

        # Move onto the next row and column
        h = h + 1
        k = k + 1
```

### Operations over fields

Gaussian elimination can be performed over any "field", which
is any set with operations which allows the set to behaves like numbers.
The main requirements are:

- Subtraction and addition exist, and there is an additive identity `0`.
- Multiplication and division exist, and there is a multiplicative identity unit `1`.
- Addition, multiplication, subtraction, and division are well defined for all
  pairs of numbers, except for division by `0`.
- Addition, multiplication, subtraction, and division are "closed', so they
  produce results in the same set.

Reals, rationals, and complex numbers are all examples of fields. However,
the integers are not a field, because division is not closed - divisions
such as $4/5$ produce results outside the field.

The reals are an example of infinite size fields, but there also exist
finite fields, such as the integers modulo a prime. Finite fields are
widely used in electrical and computer engineering, in areas such as
cryptography, digital modulation and error correction. Once of the
simplest finite fields is the field of booleans (or bits):

- Subtraction and addition are exclusive-or, and the additive identity is `false`.
- Multiplication is logical-and, and the multiplicative identity is `true`.
- Division is only defined for `true`, and produces the result `true`.

A detailed understanding of fields is not necessary beyond "they behave
like the reals", but we _do_ want to write matrix algorithms that can operate
independently from the field the matrix is in.

_Note: You may see `-0` appear in real and complex matrices. This is because floating-point_
_numbers are not reals, and they support the idea of both negative and postive_ zero._
_However, for IEEE floating-point (which we are all using) `-0 == +0`_.

### The RowSet class

To represent matrices over arbitrary fields, a base class `RowSet` has
been defined. An instance of `RowSet` allows us to operate over a
matrix without knowing what type of elements it contains - only the
derived class needs to know how to perfom maths on the elements
in the matrix. Because of this there is no function that allows
us to read the value of an element, though there is the ability
to test whether an element is one of the special values `0` or `1`.

As well as row operations, we sometimes need to perform mathematical
operations on scalars, for example when normalising rows during
Gauss-Jordan elimination. To allow us to perform scalar maths,
the RowSet provides an internal scalar element called the "buffer",
which can be used to perform maths without looking at the values.
The RowSet also knows how to read and write those values from/to
a stream, so we can perform input/output of matrices.

Included in this repository are two implementations of `RowSet`:

- `RowSetFloat` : Provides matrix operations over real numbers
  represented using `float`.

- `RowSetBool` : Provides matrix operations over the finite field
  of truth-values, represented using `bool`.

RowSetFloat provides an override of `ToReducedRowEchelonForm` 
specialised for floats, which gives a reference implementation
only for floats. You will need to implement a generic version
which works for any field.

The `RowSet` API is fixed, and you should assume that other derived
classes exist and your code will be used with them. If your
code adds extra functions to the API, then it will not compile
against existing derived implementations.

### Programs

Included in the repository are a number of programs:

- `create_random_FIELD_matrix R C` : Generates a random R by C matrix
  from the field FIELD, where FIELD is "bool", "real", or "complex".
  This will work without any modifications. Note that they may generate
  non-invertible matrices.

- `create_Ax_eq_1_system` : Reads a square matrix `A` from `A.txt`, and
   augments it to represent the system of equations `A x = 1`. This will
   work for the `real` and `bool` fields, then for `complex` once you
   complete task `B`.

- `convert_to_reduced_row_echelon_form` : Reads a matrix `A` from `cin`,
   converts it to reduced lower echelon form, and prints it back out to
   `cout`. This will only work for the `real` field until you complete
   task C.

- `show_sparsity_pattern` : Reads a matrix `A` from `cin`, and prints
   a minimised version which shows where the 0 and 1 entries are in the
   matrix. This will not work until you complete task A4.

- `calculate_matrix_inverse` : Reads a square matrix `A` from `cin`, and
   prints the inverse matrix `A^-1` to `cout`. This will only work for
   the `real` field until you complete task C.


All of these programs have an associated `build_X.sh` program to build them.
They should all compile, but some of them will not work until functions
are fixed.

### Example files

The files in examples contain examples of input matrices and various output
patterns from a working implementation of the functions and programs.

For a given FIELD, N, and N, the files are:

- `FIELD_matrix_NxN.txt` : An invertible NxN matrix

- `FIELD_matrix_NxN.Ax_eq_1.reduced.txt` : The reduced echelon form of the matrix,
   generated using:
   ```
   < FIELD_matrix_NxN.txt` | ./create_Ax_eq_1_system | ./convert_to_reduced_row_echelon_form
   ```

- `FIELD_matrix_NxN.inverse.txt` : The inverse of the matrix,
   generated using:
   ```
   ./calculate_matrix_inverse < FIELD_matrix_NxN.txt`
   ```

Note that for the `real` and `complex` fields there may be slight
discrepancies due to rounding errors, but these should not be
more than about $10^-6$ for these size matrices. Matrix inversion
should be unique, so you can check against the results of other
programs. The matrix inversion examples over all three fields have
been checked by doing the equivalent calculations using Octave
(an open-source equivalent to matlab).

Tasks
=====

A - Non-virtual extensions to RowSet (30%)
------------------------------------------

(Reading: 5 mins; Implementation: 25 mins; Testing: 5 mins; Total: 35 mins)

All these functions must remain non-virtual methods,
and be implemented entirely in terms of other virtual
methods that derived classes implement.

### A1 - Implement RowSet::SubBuffer

Implement the method `RowSet::SubBuffer`, using only
the existing methods of `RowSet` and your knowledge
of maths.

### A2 - Implement RowSet::DivBuffer

Implement the method `RowSet::DivBuffer`, using only
the existing methods of `RowSet` and your knowledge
of maths.

`x/0` is undefined in any field, so you do not need to handle it.

`0/x` is defined to be zero in any field, except for the case `0/0` which
is undefined.

### A3 - Implement RowSet::WriteRow

Implement the `WriteRow` method for `RowSet`.

### A4 - Implement RowSet::ShowSparsity

Complete the definition of the function `ShowSparsity`. Once
this is complete, the program `show_sparsity_pattern`
should start working.

B - Add a new complex field (35%)
---------------------------------

(Reading: 10 mins; Implementation: 40 mins; Testing: 10 mins; Total: 60 mins)


### B1 - Complete the test-bench `test_field.cpp`

Complete the implementation of `test_field.cpp` so that it 
tests the following properties of a row-set:

- Additive identity: `add(0,1) == `1` : 

- Multiplicative identity: `mul(1,1) == `1`

- Double negate is an identity: `neg(neg(1)) == 1`

- Unit is its own inverse: ` inv(1) == 1`

If any of the properties fails, then the program should
return a failing exit code - for example, you could use `assert`
to check for correct operation.

Do not place any other tests in this particular file, though
you are welcome to create your own test files.

### B2 - Create a new class `RowSetComplex`

Create a new class called `RowSetComplex` which is
derived from `RowSet`. This should provide operations
over elements of type `complex<double>`, and should
use the behaviour of that class for mathematical
operations and for reading and writing elements to
a stream. 

The class should be declared in the header `row_set_complex.hpp`,
and should be header-only - there should **not** be an associated
file `row_set_complex.cpp`.

You are allowed to use any parts of `row_set_float.hpp` as
a starting point for this header.

Note that you are _not_ required to create an
override for `ToReducedRowEchelonForm`, and it is
recommended that you do not.

The function `RowSet::FieldName()` should return the
string `complex`.

_Hint: this is far simpler than it might seem, as long as you start from `RowSetFloat`._

### B3 - Add the class `RowSetComplex` to `create_row_set`

Modify the file `row_set_factory.cpp` so that if a field
string of type `complex` is specified, than a new instance
of `RowSetComplex` is returned.


C - Implement `to_reduced_row_echelon_form_generic` (35%)
---------------------------------------------------------

(Reading: 5 mins; Implementation: 30 mins; Testing: 30 mins; Total: 65 mins)


Complete the definition of `to_reduced_row_echelon_form_generic` in
the file `row_echelon_form.cpp`.

Note that this function can only use the public functions from
`RowSet` - no extra methods should be added to allow for direct
access to elements.

You may use any parts of `RowSetFloat::ToReducedRowEchelonForm`
if they are helpful. However, translating the pseudo-code above
is also a good way to approach it.
