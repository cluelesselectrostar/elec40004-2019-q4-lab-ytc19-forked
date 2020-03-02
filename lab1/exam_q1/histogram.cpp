#include "histogram.hpp"

int histogram_get_count(const vector<pair<string,int>> &counts, const string &word)
{
    for(unsigned i=0; i<counts.size(); i++){
        if(counts[i].first == word){
            return counts[i].second;
        }
    }
    return 0; // Word never appeared
}

void histogram_add(vector<pair<string,int>> &counts, const string &word)
{
	if(counts.empty()){
		counts.push_back(pair<string, int> (word, 1));
	}


		for(int i=0; i<counts.size(); i++)
		{
			if(counts[i].first == word){
				counts[i].second += 1;
				return;
			}
			else{
				counts.push_back(pair<string, int> (word, 1));
			}
		}
	
}
/*
{
    for(int i=0; i<counts.size(); i++){
        if(counts[i].first==word){
            counts[i].second += 1;
            return;
        }
    }

    counts.push_back( { word, 1 } );
}
*/


void histogram_add(map<string,int> &counts, const string &word)
{
	if(counts.empty()){
		counts[word] = 1;
	}

		if(counts[word] >= 1){
			counts[word] += 1;
		}
		else{
			counts[word] = 1;
		}
	
}
