#ifndef bimap_hpp
#define bimap_hpp

#include <string>
#include <vector>

using namespace std;

struct BiMap;

/* Create a new BiMap */
BiMap *BiMap_create();


/* Free all resources assocated with the bimap */
void BiMap_destroy(BiMap *bm);

/*  Inserts a mapping value1 <-> value2
    If either value1 or value2 already exists then to nothing and return false.
    Otherwise insert the value and return true.
*/
bool BiMap_insert(BiMap *bm, const string &value1, int value2);

/*  Number of mappings in the data-structure */
unsigned BiMap_size(const BiMap *bm);

/* Lookup a mapping by string.
    If the mapping is found, return true and put integer into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, const string &value1, int &value2);

/* Lookup a mapping by integer.
    If the mapping is found, return true and put string into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, int value2, string &value1);

/* Extract all mappings as a vector
    The pairs can appear in any order.
*/
vector<pair<string,int>> BiMap_export_mappings(const BiMap *bm);

#endif
