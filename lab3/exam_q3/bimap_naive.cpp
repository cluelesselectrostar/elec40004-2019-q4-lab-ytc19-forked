#include "bimap.hpp"

#include <vector>

struct BiMap
{
    vector<pair<string,int>> mappings;
};

/* Create a new BiMap */
BiMap *BiMap_create()
{
    return new BiMap();
}

/* Free all resources assocated with the bimap */
void BiMap_destroy(BiMap *bm)
{
    delete bm;
}

/*  Inserts a mapping value1 <-> value2
    If either value1 or value2 already exists then to nothing and return false.
    Otherwise insert the value and return true.
*/
bool BiMap_insert(BiMap *bm, const string &value1, int value2)
{
    for(unsigned i=0; i<bm->mappings.size(); i++){
        if(bm->mappings[i].first==value1){
            return false;
        }
        if(bm->mappings[i].second==value2){
            return false;
        }
    }
    bm->mappings.push_back( pair<string,int>(value1,value2) );
    return true;
}

/*  Number of mappings in the data-structure */
unsigned BiMap_size(const BiMap *bm)
{
    return bm->mappings.size();
}

/* Lookup a mapping by string.
    If the mapping is found, return true and put integer into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, const string &value1, int &value2)
{
    for(unsigned i=0; i<bm->mappings.size(); i++){
        if(bm->mappings[i].first==value1){
            value2 = bm->mappings[i].second;
            return true;
        }
    }
    return false;
}

/* Lookup a mapping by id.
    If the mapping is found, return true and put string into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, int value2, string &value1)
{
    // TODO
    return false;
}


vector<pair<string,int>> BiMap_export_mappings(const BiMap *bm)
{
    return bm->mappings;
}
