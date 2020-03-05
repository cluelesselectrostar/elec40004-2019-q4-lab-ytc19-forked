#include "repeating_mapping_source.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    int n=10;
    if(argc>1){
        n=stoi(argv[1]);
    }

    RepeatingMappingSource source(1);

    for(int i=0; i<n; i++){
        pair<string,int> mapping=source.next_mapping();
        cout << mapping.first<<" "<<mapping.second<< endl;
    }
}