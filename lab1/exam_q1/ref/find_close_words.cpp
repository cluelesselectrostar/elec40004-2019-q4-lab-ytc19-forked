#include "sentence_reader.hpp"

#include "lower_case.hpp"

#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

void increment_count(vector<pair<string,int>> &counts, const string &word)
{
    for(int i=0; i<counts.size(); i++){
        if(counts[i].first==word){
            counts[i].second += 1;
            return;
        }
    }

    counts.push_back( { word, 1 } );
}

int get_count( const vector<pair<string,int>> &counts, const string &word)
{
    for(int i=0; i<counts.size(); i++){
        if( counts[i].first == word){
            return counts[i].second;
        }
    }
    assert(0);
}

int main(int argc, char **argv)
{
    if(argc<1){
        cerr<<"No target word specified."<<endl;
        exit(1);
    }

    string target=lower_case(argv[1]);

    SentenceReader reader(cin);

    vector<pair<string,int>> total_count;
    vector<pair<string,int>> close_count;

    ////////////////////////////////////////////
    // Read input sentences and collect counts

    vector<string> sentence;
    while(1){
        sentence=reader.next();
        if(sentence.empty()){
            break;
        }

        bool is_close=false;
        for(unsigned i=0; i<sentence.size(); i++){
            if(sentence[i]==target){
                is_close=true;
                break;
            }
        }

        for(unsigned i=0; i<sentence.size(); i++){
            increment_count( total_count,  sentence[i] );
            if(is_close && sentence[i]!=target){
                increment_count( close_count, sentence[i] );
            }
        }
    }

    /////////////////////////////////////////////
    // Calculate output metrics

    // Vector of (1/s_{t,w},word)
    vector<pair<double,string>> close_word_weights;
    for(int i=0; i<close_count.size(); i++){
        string word=close_count[i].first;
        int c_w = close_count[i].second;
        int a_w = get_count(total_count, word);
        double s_w = c_w / sqrt(a_w);

        //cerr << "Word : " << word <<" c_w = " << c_w << " a_w = " << a_w << " s_w = " << s_w << endl;

        pair<double,string> weighted_word( 1.0 /s_w , word );
        close_word_weights.push_back( weighted_word );
    }

    sort(close_word_weights.begin(), close_word_weights.end());

    int n=10;
    if(close_word_weights.size() < 10){
        n=close_word_weights.size();
    }
    for(int i=0; i<n; i++){
        string word=close_word_weights[i].second;
        cout << word << " " << 1/close_word_weights[i].first << " " << get_count(total_count, word) << " " << get_count(close_count, word) << endl;
    }
}
