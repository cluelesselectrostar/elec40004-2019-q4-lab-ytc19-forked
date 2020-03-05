#include "bimap.hpp"

#include <iostream>

int main()
{
    BiMap *bm=BiMap_create();

    int repeats=0;
    while(1){
        string s;
        int i;
        
        cin >> s >> i;
        if(cin.fail()){
            break;
        }

        if(!BiMap_insert(bm, s, i)){
            repeats++;
            if(repeats < 16){
                cerr<<"Repeat : "<<s<<" "<<i<<endl;
            }
        }else{
            cout<<s<<" "<<i<<endl;
        }
    }

    BiMap_destroy(bm);
}