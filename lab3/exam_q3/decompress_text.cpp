#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include "bimap.hpp"
using namespace std;

int main() {

  BiMap* compressed = BiMap_create();
  int count = 0;
  int index;

  cin >> std::hex;

  while(1){

		string tmp;
		cin >> tmp;

		if(cin.fail()){
      cout << endl;
			exit;
		}

    if ( tmp[0]!='@' ) {

      //cerr << "start normal loop" << endl;
      BiMap_insert(compressed, tmp, count);
      cout << tmp << " ";
      tmp.clear();
      count++;

    } else {

      assert(tmp.size()>1);
      tmp.erase(remove(tmp.begin(), tmp.end(), '@'), tmp.end()); //remove '@'
      index = stoi(tmp, 0, 16);
      //stoi (string, pointer(default 0), based of number)

      string found;
      BiMap_lookup(compressed, index, found);
      //cerr << "replaced " << found << endl;
      cout << found << " ";
      found.clear();

    }

  }

	BiMap_destroy(compressed);
}
