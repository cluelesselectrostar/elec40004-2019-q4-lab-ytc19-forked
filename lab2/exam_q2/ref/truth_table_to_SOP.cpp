#include "../SOP.hpp"

/*
To print out a truth-table in SOP we just need to observe
that whenever the truth table produces a 1 we add that
as a clause to the SOP.

0101|1 -> ~i1&i2&~i3&i4
*/

struct row
{
    vector<bool> bits;
    bool output;
};

row to_row(const string &s)
{
    row res;
    int p=0;
    while(s[p]!='|'){
        if(isspace(s[p]){
            // nothing
        }else if(s[p]=='0'){
            bits.push_back(false);
        }else if(s[p]=='1'){
            bits.push_back(true);
        }else{
            cerr<<"Invalid input"<<endl;
            exit(1);
        }
        p++;
    }
    assert(s[p]=='|');
    p++;

    while(isspace(s[p])){
        p++;
    }

    if(s[p]=='0'){
        res.output=false;
    }else{
        res.output=true;
    }

    return res;
}


int main()
{
    SOP tt;
    std::string line;
    while(getline(cin, line)){
        row r=to_row(line);
        if(r.output){
            vector<int> terms;
            for(unsigned i=0; i<r.bits.size(); i++){
                if(r.bits[i]){
                    terms.push_back(i+1);
                }else{
                    terms.push_back(-(i+1));
                }
            }
            tt.terms.push_back(terms);
        }
    }

    cout << SOP_to_string(&tt) << endl;
}
