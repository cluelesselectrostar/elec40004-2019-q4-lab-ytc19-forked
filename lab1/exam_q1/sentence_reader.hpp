#ifndef SentenceReader_hpp
#define SentenceReader_hpp

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SentenceReader
{
private:
    istream &src;

    // You may add more private data-members if you want to 
public:
    // Create a new sentence reader using the given input stream
    SentenceReader(istream &src);

    /*! Read the next sentence from the associated stream.

        The vector should contain only the words, and not
        include the terminating . or ?

        An empty vector indicates that there are no more sentences and the 
        stream is finished. Once an empty sentence is returned, the method
        should not be called again.
    */
    vector<string> next();
};

#endif