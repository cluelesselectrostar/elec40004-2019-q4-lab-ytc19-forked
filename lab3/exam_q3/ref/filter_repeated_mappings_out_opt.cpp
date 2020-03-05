
#include <iostream>

#include <unordered_set>

using namespace std;

int main()
{
    std::unordered_set<string> strings;
    std::unordered_set<int> ints;

    int repeats=0;
    while(1){
        string s;
        int i;
        
        cin >> s >> i;
        if(cin.fail()){
            break;
        }

        if( !ints.insert(i).second || strings.insert(s).second ){
            repeats++;
            if(repeats < 16){
                cerr<<"Repeat : "<<s<<" "<<i<<endl;
            }
        }else{
            cout<<s<<" "<<i<<endl;
        }
    }
}