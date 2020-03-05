#include "../bimap.hpp"

#include <map>

struct BiMap
{
    map<string,int> string_to_int;
    map<int,string> int_to_string;
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
    map<string,int>::iterator it1=bm->string_to_int.find(value1);
    if(it1!=bm->string_to_int.end()){
        return false;
    }
    
    map<int,string>::iterator it2=bm->int_to_string.find(value2);
    if(it2!=bm->int_to_string.end()){
        return false;
    }

    bm->string_to_int[value1]=value2;
    bm->int_to_string[value2]=value1;
    return true;
}

/*  Number of mappings in the data-structure */
unsigned BiMap_size(const BiMap *bm)
{
    return bm->string_to_int.size();
}

/*  Remove mapping by string.
    Return true if a mapping existed and was deleted, or false if no such mapping.
*/
bool BiMap_remove(BiMap *bm, const string &value1)
{
    map<string,int>::iterator itS2I=bm->string_to_int.find(value1);
    if(itS2I==bm->string_to_int.end()){
        return false;
    }
    int value2=itS2I->second;
    bm->int_to_string.erase( bm->int_to_string.find( value2 ) );
    return true;
}

/*  Remove mapping by id.
    Return true if a mapping existed and was deleted, or false if no such mapping.
*/
bool BiMap_remove(BiMap *bm, int value2)
{
    map<int,string>::iterator itI2S=bm->int_to_string.find(value2);
    if(itI2S==bm->int_to_string.end()){
        return false;
    }
    string value1=itI2S->second;
    bm->string_to_int.erase( bm->string_to_int.find( value1 ) );
    return true;
}

/* Lookup a mapping by string.
    If the mapping is found, return true and put integer into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, const string &value1, int &value2)
{
    map<string,int>::iterator itS2I=bm->string_to_int.find(value1);
    if(itS2I==bm->string_to_int.end()){
        return false;
    }
    value2=itS2I->second;
    return true;
}

/* Lookup a mapping by id.
    If the mapping is found, return true and put string into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, int value2, string &value1)
{   
    map<int,string>::iterator itI2S=bm->int_to_string.find(value2);
    if(itI2S==bm->int_to_string.end()){
        return false;
    }
    value1=itI2S->second;
    return true;    
}

vector<pair<string,int>> BiMap_export_mappings(const BiMap *bm)
{
    vector<pair<string,int>> result(bm->string_to_int.begin(), bm->string_to_int.end());
    return result;
}
