#include "bit_utils.hpp"
#include <cmath>
#include <iomanip>

int main (int argc, char **argv) {
  int w = stoi(argv[1]);
  uint64_t counter = 0;
  ostream os;

  for (int i=0; i<pow(2,w); i++) {
    write_bits_in_word(counter, w, os);
    counter++;
  }

}
