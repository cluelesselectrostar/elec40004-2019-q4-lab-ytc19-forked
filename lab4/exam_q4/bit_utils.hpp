#ifndef bit_utils_hpp
#define bit_utils_hpp

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int total_bit_flips_in_word(uint64_t x, uint64_t y);

vector<int> bit_flip_positions_in_vector(const vector<bool> &a, const vector<bool> &b);

vector<bool> read_bit_vector(istream &src);

void write_bits_in_word(uint64_t x, int w, ostream &dst);

#endif
