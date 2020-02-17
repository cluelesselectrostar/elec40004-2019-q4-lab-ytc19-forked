#include "sentence_reader.hpp"

#include "lower_case.hpp"

#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{

    SentenceReader reader(cin);

    vector<string> sentence;
    while(1){
        sentence=reader.next();
        if(sentence.empty()){
            break;
        }

        for(int i=0; i<sentence.size(); i++){
            if(i!=0){
                cout <<" ";
            }
            cout << sentence[i];
        }
        cout<<"."<<endl;
    }
}
