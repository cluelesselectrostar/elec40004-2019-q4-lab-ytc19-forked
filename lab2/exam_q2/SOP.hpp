#ifndef sum_of_products_hpp
#define sum_of_products_hpp

#include <vector>
#include <iostream>
#include <cassert>

// Gives us the type uint64_t : An unsigned integer with 64 bits
#include <cstdint>

/* Note: it is bad practise to put `using namespace std` into a header,
  but we having covered namespaces yet.
*/
using namespace std;

/*  This type represents a boolean equation in Sum of Products (SOP)
    form. The equation consists of a vector of terms, and
    each term is is a vector of integers representing the product
    of one or more equation inputs.
*/
struct SOP
{
    vector<vector<int>> terms;
};


/*  Converts a string in human readable form to an equation.
    The primitive components supported are:
    - "iN" : Inputs of the form "i0","i1","i2",... representing inputs
    - "T" : Represents the constant "True", which is represented by a zero index.
    - "~" : Negation of the next input.
    - "&" : Adds an input (negated or not) to the current term
    - "|" : Starts a new empty term.
    - " " : Whitespace is automatically skipped

    Examples of input strings and their meaning are
*/
SOP SOP_from_string(string equation);


/* This should return true if the two equations are _structurally_ equivalent,
    i.e. if the equations have exactly the same structure, so
    there are exactly the same number of terms, and each term
    consists of identical products.
*/
bool SOP_structural_equals(SOP *a, SOP *b);

/*! This function should print an equation out into a form 
    that can be read back in using SOP_from_string

    It should be the case that for a given SOP x the following should hold:
      SOP_structural_equals(x, SOP_from_string(SOP_to_string(x)) )
*/
string SOP_to_string(SOP *equation);

/*! Given a sum_of_product equation and a vector of inputs, evaluate
    the equation given those specific input values.

    Note that the equations use 1-based indices for the inputs (to allow for
    negated inputs), while the inputs use 0-based indices.
    So a use of input index `1` in the equation refers to the least significant
    bit of the inputs (`inputs&1`), while input `2` refers to the the next bit along
    (`(inputs>>1)&1`).

    Negative inputs represent negated inputs, so an index "-1" represents the negated
    input "~i1", and is the value `!(inputs&1)`, while the index "-7" is the negated
    index "~i7", and the value !((inputs >> 6)&1).
*/
bool SOP_evaluate(SOP *equation, uint64_t inputs);

/* This should return true if the two equations are _functionally_ equivalent,
    so they represent exactly the same truth-table.

    Note that this is a stronger guarantee than structural equivalence:
    - SOP_structural_equals(a,b) implies SOP_functional_equals(a,b)
    - SOP_functional_equals(a,b) does not imply SOP_structural_equals(a,b)

    A straightforward way of testing this is:
    - Calculate the largest input index $i_max$ used by either equation.
    - Calculate the width of the truth-table input: $w=i_max+1$
    - For each binary input pattern p in [0..2^w):
       - Check if evaluate(a,p) == evaluate(b,p)
*/
bool SOP_functional_equals(SOP *a, SOP *b);


#endif
