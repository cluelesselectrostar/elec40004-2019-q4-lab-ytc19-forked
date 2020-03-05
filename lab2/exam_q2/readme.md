This is a sample ELEC40004 exam question. It represents one
question out of an "answer two out of three" assessment,
and so is intended to take two people a little under 4 hours.

This has not been through the standard second-marking scheme
for exams (a multi-stage process involving 2nd markers and
external examiners), and so may include accidental errors or
ambiguities.

NOTE: on review this question was found to be too
challenging, on the grounds of:
- Time needed to read and understand it
- Relies a bit too much on understanding of digital logic

However, it is a good challenge question, and excellent
preparation for solving unseen problems.

Overview
========

(reading: 40 mins)

The goal of this exercise is to create tools and functions which
can work with boolean expressions in SOP (Sum-of-Products) form.

The SOP data-type
-----------------

The header `SOP.hpp` defines a type which represents a boolean equation
in Sum of Products form. An SOP equation consists of a vector of terms,
and each term is a vector of integers representing the product
of one or more equation inputs.

The equation inputs are represented as indices starting at
one, which for convenience we'll represent as i1,i2,i3,...
in equations. (Usually zero-based indices are used in programming, but we'll see
that it represents a problem when representing negated inputs).

An "and" gate is a single term containing the product of two inputs:
```
i1&i2
```
and could be constructed as:
```
SOP and_gate = { { {1,2} } };
```

While an "or" gate would be:
```
i1 | i2
```
and could be constructed as:
```
SOP or_gate = { { {1}, {2} } };
```

To represent all truth-tables we also need to represent complements of
inputs (i.e. "not" of an input). We'll represent them using negative
indices, and use the C bit-wise not operator `~` when printing them.
So a "not" gate would be:
```
~i1
```   
and could be constructed as:
```
SOP not_gate = { { {-1} } };
```

A "xor" gate would be:
```
~i1&i2 | i1&~i2
```
and could be constructed as:
```
SOP not_gate = { { {-1,2} , {1,-2} } };
```

There are three main edge cases for this circuit representation:

- Empty equation (zero terms): if there are no terms in the equation, then we
    will use the convention for empty sums and consider the result to be 0 (the additive identity).

- Empty products : if a particular product contains zero inputs, then we use the
    convention for empty products, and consider the result to be 1 (the multiplicative identity).

- The zero index : Due to the need to represent negated inputs, our input indices start at one.
    In line with the convention for empty products, we will treat input index 0 as representing
    "True", as it means that adding index 0 to a term has no effect.

There is no way of directly representing "False" in this system, but we can easily
include it using a product like `i1 & ~i1`".

For this type the implementation and structure of the type are part of
the public API, so anyone is allowed to directly modify the data structure.

Notice that it is impossible to create an invalid SOP, as we have handled all possible
edge cases. This means that any of the infinite possible SOP instances has a well defined
meaning, including things like empty vectors and zero indices.

Some examples of standard logic gates in this form are:
- NOT  : `~i1`
- AND  : `i1&i2`
- OR   : `i1 | i2`
- XOR  : `i1&~i2 | ~i1&i2`
- NAND : `~i1&~i2`
- AND3 : `i1&i2&i3`
- OR3  : `i1 | i2 | i3`
- XOR3 : `i1&i2&i3 | ~i1&~i2&i3 | ~i1&i2&~i3 | i1&~i2&~i3`

Instances of the SOP data-type can be created on the stack as local variables,
or on the heap using `new`. In general the SOP functions take a pointer to
SOP instances, so they do not need to know about their scope or lifetime.

Truth-table format
------------------

Here truth-tables are given using the following format:

- Plain text, consisting only of `0`, `1`, `|` and line breaks.

- One line per truth-table entry (i.e. pair of inputs and output)

- Each line consists of:

  - zero or more input values ('0' or '1'), which give the inputs from least significant to most significant bit.

  - a separating pipe `|` character

  - a single output value (`0` or `1`)

- All lines must have exactly the same number of inputs (i.e. columns)

- Empty lines at the end of the file should be discarded.

- Rows can appear in any order, but no input pattern should appear more than once.

- Any input pattern that is omitted is assumed to produce the output `0`.

For example, the following truth-table represents a two-input xor gate:
```
00|0
01|1
10|1
11|0
```
An equivalent truth-table which omits zero outputs and uses a different
ordering is:
```
10|1
01|1
```

Satisfiability
--------------

An SOP equation is `satisfiable` if there exist a set of inputs which
cause the equation to be true. So if we have the truth-table for an SOP,
this is equivalent to finding any row where the output is `1`. Satisfiability
might seem like a trivial problem, but proving satisfiability is heavily
used in industry to solve seemingly intractable problems - if you can create
better methods for proving satisfiability, then fame and money await.

When there are few inputs it is easy to check whether an SOP is
satisfiable, as you can simply enumerate all $2^n$ possible patterns:
```
for i in [0,2^n):
    if evaluate(sop, i) == 1:
        print_row i
        return Satisfiable
return NotSatisfiable
```
However, once $n$ rises above 32 the sheer number of combinations becomes
large, and for $2^64$ patterns it is effectively impossible to enumerate
them all - even if you check 1B inputs per second, it wil still take
560 years check them all.

In those cases there are two main approaches, which are often used together:

- Pre-processing : equations can be optimised to remove redundancy, particularly as the method
  creating the equation might be quite naive. Three basic techniques are:

  - Removing impossible terms: if any product contains both a variable and the negated
    variable, that entire produce is always false, and can be removed. For example, in
    this SOP:
    ```
    i1&i2&~i1 | i2&i3
    ```
    the first product contains both `i1` and `~i1`. As a consequence, we can delete the
    first term and rewrite it as:
    ```
    i2&i3
    ```

  - Removing repeated terms: if the same variable appears twice in a product, then one
    of the occurences can be removed. For example, in the following:
    ```
    i1&i2&i1&i3 | ~i4&~i4
    ```
    we can simplify to:
    ```
    i1&i2&i3 | ~i4
    ```

  - Products of one variable: any product containing a single variable always leads to a satisfiable
    solution, simply by binding that variable to true or false as needed.

- Constraint propagation: naively trying all combinations is the same as
  simultaneously substituting all the variables at once, and seeing if it
  simplifies to "true". We can be more sophisticated by substituting one
  input at a time, and simplifying the results after each substitution.
  For example, if we take the following equation:
  ```
  i1&~i2 | i3&~i1 | i1&i4
  ```
  we could choose to consider the variable i1, and see what happens if we substitute
  true and false for i1:
  ```
  i1=true ->   T&~i2 | i3&F | T&i4  = ~i2 | i4
  i1=false ->  F&~i2 | i3&T | F&i4  = i3
  ```
  These two simplified SOPs can then be considered recursively, by picking one of
  the remaining variables. Note the simplified SOPs have lost dependencies on
  some inputs: one only depends on i2 and i4, while the other only depends on i3,
  so each of the sub-problems has a much smaller space to consider.

  A general approach for constraint propagation is:
  ```
  solve(sop, fixed_inputs):
    if trivially_true(sop):
        print fixed_inputs
        exit(Satisfiable)
    pivot = pick_free_variable(sop,fixed_inputs)
    solve( simplify(substitute(var, true)), fixed_inputs+(var,true) )
    solve( simplify(substitute(var, false)), fixed_inputs+(var,false) )

  ```


Background
==========

Bit-wise operations
-------------------

C++ represents integers using either unsigned (e.g. `unsigned`) or two's-complement integers (e.g. `int`) types.
However, the length of those integers is machine-dependent, so on some machines an `int` might be 4 bytes, while
on others it might be 8 bytes. The system header `<cstdint>` introduces a set of fixed-width integers:

- Unsigned: `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`
- Signed: `int8_t`, `int16_t`, `int32_t`, `int64_t`, 

These types can be used like any other scalar type, but will always have exactly the size requested, so for
example `uint32_t` is guaranteed to be 32-bits (or 4 bytes) long.

It is often useful to represent small vectors of bits using a single integer, as this allows us to efficiently
store and process multiple bits at once. C++ includes a set of bit-wise operators on the integers, which allows
us to manipulate integers at the bit-level. The main bit-wise operators are:

- `~` : Bit-wise negation
- `&` : Bit-wise and
- `|` : Bit-wise or
- `^` : Bit-wise xor
- `<<` : Left shift
- `>>` : Right shift

We can combine these operators to achieve different operations:
```
// Extract the bit at the given index
uint32_t get_bit(uint32_t x, int index)
{
    x = x >> index; // Shift the value x right
    x = x & 1;      // Extract the LSB of shifted value
    return x;
}

// Set the bit at index to zero
uint32_t clear_bit(uint32_t x, int index)
{
    uint32_t mask = 1; // Create a single 1
    mask = mask << index; // We now have a single 1 at the desired index
    mask = ~mask;         // We now have ones everywhere _except_ at the index
    x = x & mask;        // This clears the bit at the given index
    return x;
}

// Set the bit at index to given boolean value
uint32_t update_bit(uint32_t x, int index, bool value)
{
    uint32_t bit = value;   // Convert to integer 1 or 0
    bit = bit << index;     // The value is now at the right position

    uint32_t mask = 1; // Create a single 1
    mask = mask << index; // We now have a single 1 at the desired index
    mask = ~mask;         // We now have ones everywhere _except_ at the index
    
    x = (x & mask) | bit;        // This clears the bit at the given index
    return x;
}
```

Reading from files
------------------

Files can be read in C++ using the `ifstream` class from `<fstream>`. The
class `ifstream` inherits from `istream`, so it can be used in the same
way as `cin`.

Tasks
=====

All files mentioned here are assumed to be in the same directory as
this specification. Additional sub-directories may be created as necessary.

A - Basic functions (15%)
-------------------------

(Reading: 5 mins; Implementation: 15 mins; Testing: 5 mins; Total: 25 mins))

### A1 - Create truth tables for `xor3` and `majority4`
-
Create two files `xor3.txt` and `majority4.txt` which contain truth
tables for the two functions given in `extra_functions.hpp`.

### A2 - Create a function to construct and gates

Create a file called `SOP_create_and.hpp` which defines the following function:
```
/*  Sets dst to the SOP representation of an and gate with `N` inputs.
    The inputs chosen should be the first n inputs, i.e. `i1`, `i2`, ... `iN`.
*/
void SOP_create_and(SOP *dst, int N);
```

B - Implement the function SOP_evaluate (20%)
---------------------------------------------

(Reading: 5 mins; Implementation: 40 mins; Testing: 15 mins; Total: 60 mins))

Implement the function `SOP_evaluate` in `SOP_evaluate.cpp`, following
the documentation given for the function.


C - Create a program for determining truth-table equivalence (25%)
------------------------------------------------------------------

(Reading: 15 mins; Implementation: 45 mins; Testing: 20 mins; Total: 70 mins))


Create a program `are_truth_tables_equivalent.cpp` which:

1. Takes the name of two files as command-line parameters;
2. Reads the files as truth-tables in the form specified earlier;
4. Compares the two truth-tables for equivalence and:

   a. Return exit code 0 if the two truth-tables are equivalent.
   b. Return exit code 1 if the two truth-tables are different, and prints
      to `cout` any input pattern where the two truth-tables differ.

Include a script `build_are_truth_tables_equivalent.sh` which will
compile the program into a program `are_truth_tables_equivalent`.

Usage is:
```
$ ./are_truth_tables_equivalent tt1a.txt tt1a.txt
$ ./are_truth_tables_equivalent tt1a.txt tt1a.txt && echo "Equivalent"
Equivalent
$ ./are_truth_tables_equivalent tt1a.txt tt1b.txt && echo "Equivalent"
Equivalent
$ ./are_truth_tables_equivalent tt1a.txt tt2a.txt && echo "Equivalent"
111
$
```
Note that the program prints nothing if the truth-tables are equivalent.

If two truth-tables have different numbers of input columns, the narrower
table is padded with zeros at the most-significant end to match the wider table:
```
$ ./are_truth_tables_equivalent tt1a.txt tt1c.txt && echo "Equivalent"
Equivalent
$ ./are_truth_tables_equivalent tt1a.txt tt2b.txt && echo "Equivalent"
1110
$ ./are_truth_tables_equivalent tt2a.txt tt2b.txt && echo "Equivalent"
Equivalent
```

Two levels of functionality are recognised for this program:

- Same width and small : the program can handle input truth-tables with the same number of input columns,
    using up to 16 input columns (i.e. input bits).

- Different width and/or large : the program can also handle input truth-tables expressed using different numbers
    of input columns, and any number of input bits.

C - Satisfiability (40%)
------------------------

(Reading: 10 mins; Implementation: 80 mins; Testing: 30 mins; Total: 120 mins))


Create a program called `find_satisfiable.cpp` which checks whether
an SOP equation is satisfiable. The program should read an SOP equation on
`stdin`, determine whether the equation is satisfiable, and then:

- Return exit code 1 if the equation cannot be satisfied; or

- Return exit code 0 if the equation can be satisfied, and print any row of the
  truth-table where the equation is satisfied.

Include a script `build_find_satisfiable.sh` which will
compile the program into a program `find_satisfiable`.


Two levels of functionality are recognised for this program:

- Small : the program can handle SOP equations containing up
    to 16 inputs (up to `i16`) and 1024 uses of those inputs
    in around 1 minute on a typical laptop.

- Large : can also handle equations of up to 256 inputs (up to `i256`)
  and up to 4096 input uses in around 1 minute on a typical
  laptop.

