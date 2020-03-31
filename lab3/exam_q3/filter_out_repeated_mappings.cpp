#include <iostream>
#include "bimap.hpp"
using namespace std;

int main() {
  BiMap* inputs = BiMap_create();

  string s;
  int i;

  while (cin) {
    cin >> s >> i;
    BiMap_insert(inputs, s, i);
  }

  vector<pair<string,int>> exported = BiMap_export_mappings(inputs);

  for(int i=0; i<exported.size(); i++){
		cout << exported[i].first << " " << exported[i].second << endl;
	}

  BiMap_destroy(inputs);
}
