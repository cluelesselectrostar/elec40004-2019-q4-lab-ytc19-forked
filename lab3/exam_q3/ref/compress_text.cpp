#include "../bimap.hpp"

#include <iostream>

bool is_hex(const string &x)
{
    for(unsigned i=0; i<x.size(); i++){
        if(!isxdigit(x[i])){
            return false;
        }
    }
    return true;
}

int main()
{
    BiMap *bm = BiMap_create();

    cout << std::hex;

    int next=0;
    while(1){
        string s;

        cin >> s;
        if(cin.fail()){
            break;
        }

        int i=next;
        if(BiMap_insert(bm, s,next)){
            if(s[0]=='@'){
                cout << "@" << s << " ";
            }else{
                cout << s <<" ";
            }
            next++;
        }else{
            BiMap_lookup(bm, s, i);
            cout << "@" << i << " ";
        }
    }

    BiMap_destroy(bm);
}
