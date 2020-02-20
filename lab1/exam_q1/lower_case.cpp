#include "lower_case.hpp"
#include <cctype>

string lower_case(const string &x)
{
	string y;
	for(int i=0; i<x.size(); i++)
		{
			y.push_back(tolower(x[i]);
		} 
	return y;
}
