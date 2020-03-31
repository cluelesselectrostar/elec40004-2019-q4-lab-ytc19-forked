#include <iostream>
#include "bimap.hpp"

int main()
{
	BiMap* prints = BiMap_create();
	int count = 0;
	int dummy = 0;

	cout << std::hex;

	while(1){
		string tmp;

		cin >> tmp;

		if(cin.fail()){
			break;
		}

		if(BiMap_lookup(prints, tmp, dummy)){
			cout << "@" << dummy << " ";
		} else {
			dummy = count;
			BiMap_insert(prints, tmp, count);
			count++;
			cout << tmp << " ";
		}
	}
	BiMap_destroy(prints);
}
