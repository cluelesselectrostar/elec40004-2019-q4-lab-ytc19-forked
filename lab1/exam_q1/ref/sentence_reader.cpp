#include "sentence_reader.hpp"

SentenceReader::SentenceReader(istream &_src)
    : src(_src)
{
    // If you wish you can add things here
}

vector<string> SentenceReader::next()
{
    vector<string> sentence;

    string word;
    while(1){
        char tmp=src.get();
        
        // End of stream. Not a full sentence unless it finished with . or ?
        if(src.fail()){
            //cerr<<"End of stream."<<endl;
            sentence.clear();
            return sentence;
        }

        if(tmp=='.' || tmp=='?'){
            if(!word.empty()){
                //cerr<<"Word : "<<word<<endl;
                sentence.push_back(word);
                word.clear();
            }

            if(sentence.size()>0){
                // End of non-empty sentence
                return sentence;
            }
        }

        if(isalpha(tmp)){
            word.push_back(tolower(tmp));
        }else{
            if(!word.empty()){
                //cerr<<"Word : "<<word<<endl;
                sentence.push_back(word);
                word.clear();
            }
        }
    }
}