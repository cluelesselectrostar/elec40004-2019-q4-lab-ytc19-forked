#include "bimap.hpp"
#include <vector>
#include <map>

struct BiMap
{
    map<string,int> mappings;
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
  //iterating through string (value 1) first; iterating with key.
  map<string,int>::iterator it1;
  it1 = bm->mappings.find(value1);

  if (it1 != bm->mappings.end()) {
    return false;
  } else {
    //if string doesnt matches, then iterate through integer.
    // then iterating through integer key (value2), like a vector (so use auto)
    for (auto it2=bm->mappings.begin(); it2!=bm->mappings.end(); it2++) {
      if (it2->second == value2) {
        return false;
      }
      if (it2 == bm->mappings.end()) {
        bm->mappings.insert(it2, pair<string,int>(value1, value2));
        return true;
      }
    }
  }
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
  map<string,int>::iterator it1;
  it1 = bm->mappings.find(value1);

  if (it1 == bm->mappings.end()) {
    return false;
  } else {
    it1->second = value2;
    return true;
  }
}

/* Lookup a mapping by id.
    If the mapping is found, return true and put string into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, int value2, string &value1)
{
  for (auto it2=bm->mappings.begin(); it2!=bm->mappings.end(); it2++) {
    if (it2->second == value2) {
      bm->mappings.erase(it2);
      bm->mappings.insert(it2, pair<string,int>(value1, value2));
      return true;
    }
    if (it2 == bm->mappings.end()) {
      return false;
    }
  }
}

map<string,int> BiMap_export_mappings(const BiMap *bm)
{
    return bm->mappings;
}
