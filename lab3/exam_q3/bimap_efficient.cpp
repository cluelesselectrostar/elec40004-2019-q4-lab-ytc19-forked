#include "bimap.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

struct BiMap
{
    map<string,int> mapstoi;
    map<int,string> mapitos;
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

  map<string,int>::iterator it1;
  it1 = bm->mapstoi.find(value1);
  map<int,string>::iterator it2;
  it2 = bm->mapitos.find(value2);

  //if either value 1 or value 2 is matched; i.e. iterator does not reach the end
  if ( (it1 != bm->mapstoi.end()) || (it2 != bm->mapitos.end())) {
    return false;
  } else {
    bm->mapstoi.insert({value1, value2});
    bm->mapitos.insert({value2, value1});
    return true;
  }
}

/*  Number of mappings in the data-structure */
unsigned BiMap_size(const BiMap *bm)
{
    return bm->mapstoi.size();
}

/* Lookup a mapping by string.
    If the mapping is found, return true and put integer into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, const string &value1, int &value2)
{
  if (bm->mapstoi.size()==0) {
    cerr << "Error";
    return false;
  }

  map<string,int>::iterator it1;
  it1 = bm->mapstoi.find(value1);
  if (it1 == bm->mapstoi.end()) {
    return false;
  } else {
    value2 = it1->second;
    return true;
  }
}

/* Lookup a mapping by id.
    If the mapping is found, return true and put string into value2.
    Otherwise return false.
*/
bool BiMap_lookup(BiMap *bm, int value2, string &value1)
{
  if (bm->mapitos.size()==0) {
    cerr << "Error";
    return false;
  }

  map<int,string>::iterator it2;
  it2 = bm->mapitos.find(value2);

  if (it2 == bm->mapitos.end()) {
    return false;
  } else {
    value1 = it2->second;
    return true;
  }
}

bool sortbyint (const pair<string,int> &left, const pair<string,int> &right) {
  return (left.second < right.second);
}

vector<pair<string,int>> BiMap_export_mappings(const BiMap *bm)
{
  if (bm->mapstoi.size()==0) {
    cerr << "Error";
  }
  vector<pair<string,int>> unsorted = vector<pair<string,int>>(bm->mapstoi.begin(), bm->mapstoi.end());
  sort(unsorted.begin(),unsorted.end(), sortbyint);

  return unsorted;
}
