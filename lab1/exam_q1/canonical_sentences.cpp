#include "sentence_reader.hpp"
#include "lower_case.hpp"
#include <iostream>
#include <cassert>

//The canonical form of a text.: one sentence per line, all words converted to lower_case.

int main() {
  SentenceReader eater(cin);

  while (1){
    vector<string> sentence = eater.next();

    if (cin.fail()){
      break;
    }

    //assert(!sentence.empty());

    for (int i=0; i<sentence.size();i++) {
      if (i!=sentence.size()-1) {
        cout << sentence[i] << " ";
      } else {
        cout << sentence[i] << "." << endl;
      }

    }
  }
}
