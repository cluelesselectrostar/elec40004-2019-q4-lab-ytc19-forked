#include "histogram_add.cpp"

int histogram_get_count(const vector<pair<string,int>> &counts, const string &word)
{
    for(unsigned i=0; i<counts.size(); i++){
        if(counts[i].first == word){
            return counts[i].second;
        }
    }
    return 0; // Word never appeared
}
