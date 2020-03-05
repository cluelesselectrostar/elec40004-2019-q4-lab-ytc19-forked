#include "SOP.hpp"
#include "SOP_helpers.hpp"

/*  Sets dst to the SOP representation of an and gate with `N` inputs.
    The inputs chosen should be the first n inputs, i.e. `i1`, `i2`, ... `iN`.
*/

//SOP and_gate = { { {1,2} } };

void SOP_create_and(SOP *dst, int N) {
  vector<int> inner;
  for (int i=1; i<=N; i++) {
    inside.push_back(i);
  }

  vector<vector<int>> outer;
  outer.pushback(inner);

  dst->terms = outer;
};
