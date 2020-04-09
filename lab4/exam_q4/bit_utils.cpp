#include "bit_utils.hpp"
#include <algorithm>
#include <cassert>

int total_bit_flips_in_word(uint64_t x, uint64_t y)
{
  int count=0;
  bool x_sel, y_sel;
  for (int i=0; i<64; i++) {
    x_sel = (x >> i) & 1;
    y_sel = (y >> i) & 1;
    if ( x_sel != y_sel ) {
      count++;
    }
    continue;
  }
  return count;
}

vector<int> bit_flip_positions_in_vector(const vector<bool> &a, const vector<bool> &b)
{
  vector<int> pos;
  assert (a.size() == b.size());
  for (int i=0; i<a.size(); i++) {
    if (a[i] != b[i]) {
      pos.push_back(i);
    }
    continue;
  }
  return pos;
}

vector<bool> read_bit_vector(istream &src)
{
    
}

void write_bits_in_word(uint64_t x, int w, ostream &dst)
{
    // TODO
}
