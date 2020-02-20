#ifndef histogram_hpp
#define histogram_hpp

#include <vector>
#include <string>
#include <utility>

using namespace std;

/*
    If an entry for the given word exists in the counts vector, then increment the count.
    Otherwise, add a new entry with a count of 1.
*/
void histogram_add(vector<pair<string,int>> &counts, const string &word);

/*
    Find an entry for the given word, and return the count.
    If word does not exist, return a count of 0.
*/
int histogram_get_count(const vector<pair<string,int>> &counts, const string &word);

#endif