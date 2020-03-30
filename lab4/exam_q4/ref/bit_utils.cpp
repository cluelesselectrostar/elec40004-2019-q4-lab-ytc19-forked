#include "../bit_utils.hpp"

#include <cassert>

int total_bit_flips_in_word(uint64_t x, uint64_t y)
{
    int differences=0;
    for(int i=0; i<64; i++){
        if( (x%2) != (y%2) ){
            differences += 1;
        }
        x=x/2;
        y=y/2;
    }
    return differences;
}

vector<int> bit_flip_positions_in_vector(const vector<bool> &a, const vector<bool> &b)
{
    assert(a.size()==b.size());
    vector<int> res;
    for(int i=0; i<a.size(); i++){
        if(a[i]!=b[i]){
            res.push_back(i);
        }
    }
    return res;
}

vector<bool> read_bit_vector(istream &src)
{
    vector<bool> res;
    string line;
    getline(src, line);
    if(src.fail()){
        return res; // Return empty vector
    }
    //std::cerr<<"Line = '"<<line<<"'"<<endl;
    for(int i=0; i<line.size(); i++){
        if(line[i]=='0'){
            res.push_back(false);
        }else if(line[i]=='1'){
            res.push_back(true);
        }else{
            assert(false);
        }
    }
    return res;
}

void write_bits_in_word(uint64_t x, int w, ostream &dst)
{
    for(int i=0; i<w; i++){
        if(x&1){
            dst << "1";
        }else{
            dst << "0";
        }
        x=x/2;
    }
}
