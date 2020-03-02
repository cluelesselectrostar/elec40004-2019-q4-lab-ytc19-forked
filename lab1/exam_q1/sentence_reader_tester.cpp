#include "sentence_reader.hpp"
#include <cassert>
#include <algorithm>
#include <vector>
#include "lower_case.hpp"
#include <iostream>

int main()
{
	while(1){
		SentenceReader reader(cin);
		vector<string> sentence = reader.next();
		for(int i = 0; i<sentence.size(); i++){
			cout << sentence[i] << " ";
		}
	}
}
