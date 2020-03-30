Overview
========

Power consumption in a digital circuit can roughly be split
into static power and dynamic power:

- Static power: the power needed simply to keep the circuit
  turned on and to maintain its state. This is often called
  leakage power, due to the slow leakage of energy across
  transistors.

- Dynamic power: the additional power needed to allow the
  internal signals to transition from 0 to 1 and back as
  the internal signals change.

Static power can often be calculated just by looking
at the circuit and counting transistors, but dynamic power
depends heavily on what the inputs to the circuit are.
A useful proxy for dynamic power consumption is to estimate
the number of signals (wires) which flip within each cycle.
So whenever a logic gate's output flips, we assume it consumes
some fixed amount of joules.

A more accurate approximation is to work out how often
each signal flips and to weight it by the energy cost of
that signal. For example, a signal with high "fanout" is
connected to many inputs, which means the capacitative
load of that signal is higher, and flipping it will cost
more energy.

Trace files
-----------

Trace files are used to estimate power consumption based
on simulation results, and record the switching activity
observed over multiple clock cycles. For our purposes,
we will assume that trace files are simply text files
containing rows of `0` and `1` characters. Each column
represents the value of a particular signal, while each
row is the end of a simulated clock cycle. It is required
that all lines have the same number of columns, and
no whitespace is allowed except for line-breaks.

For example, this trace file represents four signals
over three clock cycles:
```
0001
0101
0010
```
Over the three clock cycles, there are two chances for
each bit to flip. If we move from the left to the right
column, the first signal does not flip, the second flips
twice, and the third and fourth flip once.

If trace bit-vectors are treated as integers, then the
least-significant bit comes first. For example, the above
trace would be represented by the decimal numbers:
```
8
10
4
```


Power estimation
----------------

### Simple power estimation

Using a simple power estimation which treats all signals equally, we
could estimate the power used in this trace as:
```
P = ( flips * energy_per_flip ) / ( cycles / clock_rate )
```
If we were to choose `energy_per_flip` of 1 fJ (femto-Joule) and `clock_rate` of 100MHz,
and use the above trace file, this would result in an estimated power of:
```
P = ( 4 flips * 1 fJ/flip ) / ( 3 cycles / 100 MCycles/sec)
  = ( 4  * 1e-15 ) / ( 3 / 100e6 )
  = 4e-15 J / 3e-8 s
  = 4e-7 W
  = 1.333333 μW
```

The output of a simple power estimation consists of four lines, each containing one number:

- Number of signals : an integer giving the number of input signals
- Cycle count : an integer giving the number of cycles in the trace.
- Total flips : an integer giving the number of flips found across all signals and cycles.
- Power : the estimated power, given in Watts. This should be accurate to at least four
  significant figures.

If we were to perform power estimation on the above trace, with energy per
flip of 10^-15 J and clock rate of 10^8 Hz, the output could be:
```
4
3
4
1.3333333e-7
```
There is some freedom in the formatted of the fourth line, as long as it is
accurate to four significant figures. Any comparison program will need to
actually read the numbers as floating-point to check whether they are correct.

### Weighted power estimation

In a weighted power estimation we give each of the $i = 1..k$ signals an energy cost $e(i)$,
and then estimate power as:
```
P = sum( flips_for(i) * e(i), i=1..k ) / ( cycles / clock_rate )
```
In addition we are interested in the per-signal power:
```
P_i = flips_for(i) * e(i) / (cycles / clock_rate)
```

The per-bit energies for a weighted estimation are given as a text-file,
containing one number per signal. The first column in the trace corresponds
to the first number in the energies text file.

If we use our example trace, a possible energy file would be:
```
1e-15
2e-15
3e-15
4e-15
```

If we assume the clock rate remains at 100MHz, the per-flip powers are then:

- Bit 1 : 0 flips, P_1 = 0
- Bit 2 : 2 flips, P_2 = 2 * 2e-15 / (3 / 1e8) = 1.333333e-7
- Bit 3 : 1 flip, P_3 = 1 * 3e-15 / (3 / 1e8) = 1e-7
- Bit 4 : 1 flip, P_4 = 1 * 4e-15 / (3 / 1e8) = 1.333333e-7

So the total power is 3.666666e-7 Watts.

The output of power estimation could then be:
```
4
3
4
3.66666667e-7
0
1.333333e-7
1.000000e-7
1.333333e-7
```

Note that the number representation of the power could change, as long as it
is correct to four significant figures.

Task
====

A - Bit manipulation functions (30%)
------------------------------------

The declarations for these functions already exists in `bit_utils.hpp`.
You should place definitions in `bit_utils.cpp`.

### A1 - Write a total_bit_flips_in_word function

Write a function `total_bit_flips_in_word` which takes two input values
of `uint64_t` type, and returns the number of bits where they are different.

### A2 - Write a bit_flip_positions_in_vector function

Write a function `bit_flip_positions_in_vector` which takes as input two `const`
references to `vector<bool>, and returns a `vector<int>` containing
the indices where the two vectors are different. 

Indices are zero-based, so index 0 means the two vectors differ in their
first elements.

Indices should appear in the vector in ascending order.

You can assume that the vectors are the same size.

### A3 - Write a read_bit_vector function

Write a function `read_bit_vector` which takes a reference to an `istream`,
reads a single stimulus line, and then returns the bit-vector as
a `vector<bool>`.

The first column in the stimulus file should correspond to index zero in the
vector, and all other bits follow in the same order.

If there are no more stimulus lines, the function should return an empty
vector.

### A4 - Write a write_bits_in_word function

Write a function `write_bits_in_word` which takes:

- a single `uint64_t` $x$;
- a parameter $n$ specifying how many bits are in $w$; and
- an `ostream` to print on

It should then print the equivalent binary string for $x$ to
the specified `ostream`.

The ordering of bits follows the convention for trace-files
when considered as integers.

Exactly $w$ characters should be printed to the output string. All characters
are either `0` or `1`. No whitespace or line endings should be printed.

You can assume that $x$ is always in the range $[0,2^w)$.


B - Power estimation (45%)
--------------------

### B1 - Write a program `simple_power_estimator.cpp`

Write a program `simple_power_estimator.cpp` which reads a trace
file from `stdin`, and estimates the energy using the simple
power estimation method.

The program should take two **optional** command line parameters:

- `clock_rate` : Given in Hz. If not present, assume a default of 100 MHz.
- `energy_per_flip` : Given in Joules. If not present, assume a default of 1 pJ. 

### B2 - Weighted power estimation

Write a progam `weighted_power_estimator.cpp` which reads a trace
file from `stdin` and estimates power using a weighted estimate.

The program should take two **required** command line parameters:

- `clock_rate` : Given in Hz.
- `per_signal_energy` : The name of a file containing the energy per flip for each of the
   signals.

The output of the program should include the four lines for the simple estimator,
followed by a per-signal power estimate in Watts (see the output format description
earlier).

C - Test trace generation (25%)
-------------------------------

### C1 - Counter test trace generation

Write a program `generate_counter_trace.cpp` which generates a
trace corresponding to the output of an $n$ bit binary counter.

Include a script `build_generate_counter_trace.sh` which produces
a binary program called `generate_counter_trace`.

The program will receive the parameter $n$ as a required input
parameter. The input $n$ will always be in the range $0 \leq n \leq 64$.

The output should consist of a trace with $n+1$ rows, and should
be equivalent to the numbers $0,1,2,3,...,2^n-2,2^n-1,0$.

For example, for $n=3$ the output should be:
```
000
100
010
110
001
101
011
111
000
```

### C2 - Counter reference output creation

Create three outputs containing the expected outputs for the simple
power estimation program when applied to the output of a counter trace.

The specific values should be for $n=4$, 8, and 48, and should have
the following file names:

- `counter_reference_output_n4.txt`
- `counter_reference_output_n8.txt`
- `counter_reference_output_n48.txt`

