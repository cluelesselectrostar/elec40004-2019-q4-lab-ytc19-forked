#include "lower_case.hpp"

string lower_case(const string &x)
{
    string result=x;
    for(int i=0; i<result.size(); i++){
        result[i]=tolower(result[i]);
    }
    return result;
}