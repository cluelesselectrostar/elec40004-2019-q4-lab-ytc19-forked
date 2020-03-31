#include <iostream>
#include "bimap.hpp"

using namespace std;

int main()
{
	BiMap* tester = BiMap_create();

	cout << "Insert dog <-> 1 : " << BiMap_insert(tester, "dog", 1) << endl;
	cout << "Insert cat <-> 1 : " << BiMap_insert(tester, "cat", 1) << endl;
	cout << "Insert cat <-> 2 : " << BiMap_insert(tester, "cat", 2) << endl;
	cout << "Insert dog <-> 2 : " << BiMap_insert(tester, "dog", 2) << endl;
	cout << "Insert mouse <-> 3 : " << BiMap_insert(tester, "mouse", 3) << endl;
	
	cout << "The size of this BiMap is : " << BiMap_size(tester) << endl;

	string dog = "dog";
	int dog_num = 4;
	string lion = "lion";
	int lion_num = 5;

	cout << "Does dog exists in the BiMap? " << BiMap_lookup(tester, dog, dog_num) << endl;
	cout << "If yes, what is its number now? " << dog_num << endl;

	vector<pair<string,int>> exported = BiMap_export_mappings(tester);
	cout << "Does lion exists in the BiMap? " << BiMap_lookup(tester, lion, lion_num) << endl;
	

	for(int i=0; i<exported.size(); i++){
		cout << exported[i].first << " " << exported[i].second << endl;
	}

	BiMap_destroy(tester);	//How to test a destructor?

	cout << "Done" << endl;
}
