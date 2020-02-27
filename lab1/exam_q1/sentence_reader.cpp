#include "sentence_reader.hpp"
#include <cassert>
#include <algorithm>
#include "lower_case.hpp"

SentenceReader::SentenceReader(istream &_src)
    : src(_src)
{
    // If you wish you can add things here
}

vector<string> SentenceReader::next()
{
  /*! Read the next sentence from the associated stream.

      The vector should contain only the words, and not
      include the terminating . or ?

      An empty vector indicates that there are no more sentences and the
      stream is finished. Once an empty sentence is returned, the method
      should not be called again.
  */

  vector<string> sentence;
  string word;

  while (1) {
    char tmp = src.get();

        if (src.fail()){
          sentence.clear(); //defensive programming: want to return empty sentence.
          //assert(sentence.empty());
          return sentence;
        }

        if (tmp == '?' | tmp == '.') {
          if (!word.empty()) { //this is the last word of the sentence
            sentence.push_back(word);
            word.clear(); //defensive programming.
          } else {
            break;
          }
          //assert (!sentence.empty());
          if (!sentence.empty()){
            return sentence; //this is where the function should end; returning a vector of strings (a sentence)
          } else {
            break;
          }
        }

        if (isalpha(tmp)) {
          word.push_back(tolower(tmp));
        } else { //if the character is empty (space), its the end of the word.
            if (!word.empty()) {
              sentence.push_back(word);
              word.clear();
            }
        }
  }

}
