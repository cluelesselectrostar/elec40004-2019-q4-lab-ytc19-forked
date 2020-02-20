#include "lower_case.hpp"
#include <cstring>
#include <cstdio>
#include <cctype>

string lower_case(const string &x)
{

  //create test infrastructure later.

    string initialise = " ";
    string &y = initialise;
    for (int i=0; i<x.size(); i++)
        y.push_back(tolower(x[i]));

    return y;
}
