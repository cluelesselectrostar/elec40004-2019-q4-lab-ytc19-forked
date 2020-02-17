This is a sample ELEC40004 exam question. It represents one
question out of an "answer two out of three" assessment,
and is intended to take two people a little under 4 hours.

This has not been through the standard second-marking scheme
for exams (a multi-state process involving 2nd markers and
external examiners), and so may include accidental errors or
ambiguities.

Overall task: Find words closely related to a given word
========================================================

(Reading: 30 mins)

Imagine you are beginning a data analysis project where you are trying to
discover correlations within natural language. Your working hypothesis is that
you can discover "interesting" words related to a target word using the following
process:

1.  Take the input text and split it into sentences. A sentence is any
    sequence of one or more words terminated by a full-stop (`.`) or question mark (`?`).
    A word is any contiguous sequence of alphabetic characters (`a`-`z` and `A`-`Z`).
    Any other characters are treated as white-space and will separate words.
    All words should be converted to lower-case before further processing.

2.  Identify those sentences in which the target word $t$ appears. We will call these
    the "close" sentences.

3. For each word $w$ that appears in the input, excluding $t$:

    1.  Calculate $a_w$, the number of times the word $w$ appears (across all sentences).

    2.  Calculate $c_{t,w}$, the number of times the word $w$ appears in just the close sentences for word $t$.

    3.  Calculate $s_{t,w}=c_{t,w} / (a_w^0.5)$ (`c_tw / sqrt(a_w)`), which is a metric intended
        to favour globally uncommmon words which frequently appear locally alongside the target word.

4.  Rank all words by their values of $s_{t,w}$, from highest to lowest value, and print the
    first 10 words along with the value of $s_{t,w}$. If there are fewer than 10 close words, then print as many as exist.
    Each printed word should appear on one line, with the following components seperated by spaces
    
    1.  The word $w$
    2.  $s_{t,w}$ at the default precision for `cout`.
    3.  $a_{w}
    4.  $c_{t,w}

    If two words have the same value of $s_{t,w}$ then the word that compares as smallest (according to `string::operator<`)
    should be ranked higher. 

Our goal is to be able to apply this process to very large amounts of text, such as books
(100KB-1MB), or ideally all of wikipedia (~60GB).

The program `find_close_words_ref` provides a reference implementation of
this behaviour, though it is artificially limited to relatively small inputs.

Deliverables
============

The assessment occurs in terms of the required files and behaviours
state here.

Files and functions other than the ones mentioned here may be included
in the repo, such as source files used to test functions, scripts used
to build things, documentation, and so on. However, you should usually
avoid including binary programs, in order to avoid the repo getting
too large. 

A : Utility functions (20%)
---------------------

(Reading: 5 mins; Implementation: 15 mins; Testing: 5 mins; Total: 25 mins)

### A1 - Implement `lower_case`

The file `lower_case.hpp` provides a declaration for a function which
should convert a string to lower case using the function `tolower` from `<cctype>`.

Define this function in the file `lower_case.cpp`. 

### A2 - Implement `histogram_add` for a vector

The file `histogram.hpp` provides a declaration for a function `histogram_add`
which updates a histogram represented as a vector. Add a definition
of `histogram_add` to the file `histogram.cpp`.

### A3 - Add `histogram_add` for a map

Add a function overload declaration to `histogram.hpp` which uses a histogram
of type `map<string,int>`, and add a corresponding definition to `histogram.cpp`.


B : Sentence splitting (35%)
----------------------------

(Reading: 10 mins; Implementation: 40 mins; Testing: 10 mins; Total: 60 mins)


### B1 - Implementation of `SentenceReader`

The file `SentenceReader.hpp` declares a class which will read
sentences from a given stream.

Provide an implementation of `SentenceReader.cpp` that adheres
to the given definition of sentences.

### B2 - Creating a canonical sentence printer

The "canonical form" for a text stream consists of one sentence per
line, with all words converted to lower-case, exactly one space between each word,
and a single full-stop at the end of each line.

Create a program `canonical_sentences.cpp` which uses `SentenceReader.cpp`
to convert a stream of text on `cin` into canonical form sentences which
are written to `cout`.

You should include a script called `build_canonical_sentences.sh` which
will compile the program into a binary called `canonical_sentences`.

### B3 - Testing `SentenceReader`

Create a script `test_canonical_sentences.sh`, which will test the implementation
of `canonical_sentences`.  The script should use at least one test input to check whether
the program works.


C : Implementing the program (45%)
----------------------------------

(Reading: 15 mins; Implementation: 60 mins; Testing: 25 mins; Total: 100 mins)


You are not required to use any of the functions/classes from the
preceding section to implement this program, though they
may be useful.

### C1 : Create a program `find_close_words` for small inputs

Create a program `find_close_words.cpp` which implements the defined
behaviour. The program should take one command line parameter which specifies
the target word.

This program only needs to handle inputs containing up to 10000 words.

You should include a script called `build_find_close_words.sh` which
will compile the program into a binary called `find_close_words`.

### C2 : Create a test script for `find_close_words`

Create a test-script `test_find_close_words.sh` which will:
- compile `find_close_words.cpp` into a program `find_close_words`; and
- test it on at least two inputs.

Any inputs/outputs should either be embedded in the script, or committed into source control.

_Hint_ : even if you don't have a working implementation of `find_close_words`,
you should still be able to develop this script. You may even wish to develop
it in parallel, or first.

### C3 : Create a program `find_close_words_large` for large inputs

Create a program `find_close_words_large.cpp` which implements the same
functionality as `find_close_words.cpp`, but is able to handle
input files containing millions to billions of words. The number of distinct (unique)
words will not exceeed 100000.

Example inputs
--------------

We might have the following input (from `input.txt`):
```
I am a little teapot. Why must I be a teapot? What
is a little teapot such as I (or even a big one) to do? Well,
there is always... time for a cup of tea. sigh
``` 

This contains exactly five sentences according to our definition,
which in canonical form are:
```
i am a little teapot.
why must i be a teapot.
what is a little teapot such as i or even a big one to do.
well there is always.
time for a cup of tea.
```

If we choose the target word `teapot`, then the "close" words are:
```
$ ./find_close_words_ref teapot < input.txt
a 1.78885 5 4
i 1.73205 3 3
little 1.41421 2 2
am 1 1 1
as 1 1 1
be 1 1 1
big 1 1 1
do 1 1 1
even 1 1 1
must 1 1 1
```

The file `alice.txt` contains the contents of Alice in Wonderland (26K words), and
looking for associations with the word `cat`, we get:
```
$ ./find_close_words_ref cat < alice.txt
cheshire 1.88982 7 5
grin 1.63299 6 4
the 1.57989 1641 64
vanished 1.5 4 3
removed 1.41421 2 2
dinah 1.33631 14 5
dog 1.1547 3 2
paw 1.1547 3 2
a 1.15356 632 29
said 1.07006 462 23
```
As we might hope, it has worked out that the cat in Alice in Wonderland
is something to do with Cheshire, and it both grins and vanishes. However,
it is not sophisticated enough to remove high occuring generic words
like "the" (there are much better metrics for this type of scoring).

The file `war_and_peace.txt.bz2` contains War and Peace (560K words),
compressed using the `bzip` method. The text can be decompression
using the `bunzip2` command:
```
$ bunzip2 -c war_and_peace.txt.bz2
```
(use ctrl-c to stop it printing).

If we look for associations with the word `war`, we get:
```
$ bunzip2 -c war_and_peace.txt.bz2  | ./find_close_words_ref war
the 4.24482 34549 789
of 3.66332 14889 447
minister 2.66053 51 19
and 2.58215 22231 385
council 2.57143 49 18
to 2.31547 16675 299
that 2.07738 8190 188
in 1.89958 8979 180
pfuel 1.89624 47 13
antichrist 1.78885 5 4
```
So one assumes that there is some kind of minister for war,
and war is somehow related to the antichrist.
