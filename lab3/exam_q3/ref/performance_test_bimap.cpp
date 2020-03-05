#include "bimap.hpp"
#include "clock.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    int n=1000000;
    if(argc>1){
        n=stoi(argv[1]);
    }

    BiMap *bm=BiMap_create();

    Clock clock;
    clock.start();
    for(int i=0; i<n; i++){
        BiMap_insert(bm, std::to_string(i), i );
    }
    double tInsert=clock.stop();

    clock.start();
    for(int i=0; i<n; i++){
        int ti;
        string ts;
        BiMap_lookup(bm, std::to_string(i), ti );
        BiMap_lookup(bm, i, ts);
    }
    double tLookup=clock.stop();

    cout<<"Inserted "<<n<<" in "<<tInsert<<" seconds"<<endl;
    cout<<"Looked up "<<n<<" in "<<tLookup<<" seconds"<<endl;

    BiMap_destroy(bm);
}
