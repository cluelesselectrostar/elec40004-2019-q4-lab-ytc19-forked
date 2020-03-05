#include "../bimap.hpp"

#include <iostream>
#include <string>

int main()
{
    BiMap *bm = BiMap_create();

    cin >> std::hex;

    int next=0;
    while(1){
        string si;

        cin >> si;
        if(cin.fail()){
            break;
        }

        string s;
        if(si[0]=='@'){
            if(si.size()>1 && si[1]!='@'){
                BiMap_lookup(bm, stoi(si.substr(1), 0, 16), s);
            }else{
                s=si.substr(1);
                BiMap_insert(bm, s, next);
                next++;    
            }
        }else{
            s=si;
            BiMap_insert(bm, si, next);
            next++;
        }

        cout << s << " ";
    }

    BiMap_destroy(bm);
}
