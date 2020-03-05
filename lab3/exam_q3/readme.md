Overview
========

The context here is to maintain and manipulate a set of bidirectional
mappings between strings and numbers, such that given a string we
can find the number (if any) associated with it, or given a number
we can find the string (if any) associated with it. This type of
mapping frequently occurs in data management tasks, such as:

- Mapping logins to numerical user ids; for example, your
  college login and CID are both unique.

- Anonymising data-sets: mapping personally identifiable information
  such as a name to an anonymised number.

- Mapping human readable strings to compact machine forms; for
  example mapping web-site domain names to server IP addresses
  (though in reality DNS is more like a bidirectional multi-map).

- Compressing large textual data-sets by encoding words as vectors
  of numbers.

Definition of a BiMap
---------------------

If we consider a bidirectional map as a set of pairs $(s,i)$, where
$s$ is a string and $i$ is a non-negative integer, then the main operations are:

- Adding a mapping $(s,i)$ to the set, though only if neither $s$
  nor $i$ appear in the map already.

- Finding the value of $i$ corresponding to a given $s$ (if any)

- Finding the value or $s$ corresponding to a given $i$ (if any)

This data-structure is represented here using the API given in
`bimap.hpp`, with the documentation on each function describing
the operations of the data-structure.

A reference implementation of the `BiMap` type and functions is
given in `bimap_naive.cpp`, which gives a correct but slow
implementation. Internally it uses a plain vector to store
mappings, so the time cost of all operations is proportional to 
the number of mappings.

Efficiency
----------

In an "efficient" implementation of BiMap the lookup and insert operations
should not take substantially more time as the number of mappings grows.

One approach is to view the bidirectional map as two pairs of uni-directional maps:

- A mapping from strings to integers

- A mapping from integers to strings

These two maps can then be implemented efficiently using the map containers
from the C++ standard libraries. These containers using more optimised
data structures, making some methods much faster. For example, `map`
is usually implemented in terms of binary sorted trees, which provide
`insert` and `find` methods which take time proportional to the logarithm
of the total number of elements.

Representing mappings in files
------------------------------

A textual format for input/output of mappings is:

- Each mapping will appear on separate line;
- Each line consists of a string and integer seperated by white-space.
- The string of a mapping will not contain any white-space or non-printable characters.
- Integers will always be non-negative base-10 integers.
- All integers will be representable as an `int`.

For example, if we had the following input:
```
a 4
fff 6
b 4
g 10
b 3
fff 5
xt 5
```
then the output would be:
```
a 4
fff 6
g 10
b 3
xt 5
```

Text Compression
----------------

Our target application is simple text compression. We will view
an incoming text stream as a sequence of white-space seperated
words. In order to compress the text, we will substitute previously
seen words with smaller hexadecimal indices. The index assigned
to each word is given by the order in which each word is encountered:
the first word encountered is index 0, the next previously
un-seen word is index 1, and so on.

For example, if we take this text:
```
nice to see you. to see you nice.
```
it would build the following word/index mapping:
```
nice 0
to 1
see 2
you. 3
you 4
nice. 5
```
Note that the word splitting is only by white-space, so that it is compatible
with reading a string using `src >> var`, where `src` is an `istream`, and
`var` is a `string`. This means that `you` and `you.` are seen as distinct words.

The compressed text is then:
```
nice to see you. @1 @2 you nice.
```

When decompressing the text, any word not beginning with `@` will
be added as a new entry, while those beginning with `@` are hexadecimal
indices.

So the overall compression process in pseudo-code is:
```
next_index=0
loop
    string s = read_word()
    if read_failed()
        break
    if bm.lookup(s, &i)
        print("@"+to_hex(i)+" ")
    else
        i=next_index
        bm.add(s,i)
        next_index += 1
        print(s+" ")
```

Reference compressors and decompressor binary programs are included
as `compress_text_ref` and `decompress_text_ref`.

Tasks
=====

A - Correctness and Implementation (40%)
----------------------------------------

### A1 - Correctness testing

Create a program called `test_bimap.cpp` which will test
the main functions of `bimap`. Your program should consider
ways in which the following functions could fail:

- `BiMap_insert`

- `BiMap_lookup`: string overload

- `BiMap_lookup`: int overload

You can also test other functions, but these are the ones
that will be assessed. For assessment purposes you can
assume that only one function will be broken at a time,
and it will be broken in a way that is:

- Repeatable and deterministic

- Occurs for simple test-cases

- Is detectable using other functions

The program should compile and link using the command:
```
$ g++ test_bimap.cpp bimap_IMPL.cpp
```
where `bimap_IMPL.cpp` is a source file containing a bimap implementation.

### A2 - Implement lookup by integer in naive BiMap
---------------------------------------------------

One of the overloads of `BiMap_lookup` in `bimap_naive.cpp` is not
implemented. Implement it so that it functions correctly.

### A3 - Efficient BiMap implementation
---------------------------------------

The naive implementation of `BiMap` is very slow. Create a
source file called `bimap_efficient.cpp` which provides an
efficient version of bimap.

Your implementation should provide the same API and functions
as the original, but provide efficient insertion and lookup
operations.

An implementation is considered "efficient" if it is able to 
perfom all of the following within 120 seconds:

- insert 10M unique mappings into a bimap.
- perfom 10M successful lookups by string.
- perfom 10M successful lookups by integer.

_For calibration_: on a very cheap laptop, a simple efficient implementation
using two `map`s is able to perform all three tasks within 30 seconds
(no compiler optimisation flags - plain compile), while the naive version
(with compiler optimisation flags off) takes around 120 seconds for
just 200K mappings, and takes around 40 minutes for 1M mappings.

You may copy any parts of `bimap_naive.cpp` that are useful.

B - Filtering out duplicate mappings (20%)
------------------------------------------

Create a program called `filter_out_repeated_mappings.cpp` which
reads a stream of mappings from `cin`, and prints the mappings
back out to `cout` _without_ any repeated mappings. A repeated
mapping `(s,i)` is a mapping where either the `s` or `i` has 
been used in an earlier mapping in the stream.

Include a script `build_filter_out_repeated_mappings.sh` which
will compile it into a binary called `filter_out_repeated_mappings`.

You may choose to use `BiMap` (your own
version or the naive version), or use any other data-structure
or approach that you preferr.

C - Text Compression (40%)
--------------------------

In this section you may choose to use `BiMap` (your own
version or the naive version), or use any other data-structure
or approach that you prefer.

### C1 - Implement text compression

Create a program `compress_text.cpp` which reads a text stream
and produces a compressed text stream in the format given.

Include a script `build_compress_text.sh` which will compile
the file into an executable called `compress_text`.

### C2 - Implement text decompression

Create a program `decompress_text.cpp` which reads a text stream
and produces a compressed text stream in the format given.

Include a script `build_decompress_text.sh` which will compile
the file into an executable called `decompress_text`.
