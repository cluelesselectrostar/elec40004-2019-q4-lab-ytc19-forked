#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "sentence_reader.hpp"
#include "histogram.hpp"
#include "lower_case.hpp"

using namespace std;

struct out_param {
  string oword;
  float os_tw;
  int oa_w;
  int oc_tw;
};

int main(int argc, char** argv)
{
	string target = argv[1];

	vector<pair<string,int>> close_counts;
	vector<pair<string,int>> all_counts;

	while (1) {

		bool tfound = false;

		SentenceReader eater(cin);	
		
		vector<string> sentence = eater.next();
		
		if (sentence.empty()) {
			break;
  		}
			
		for (int i=0; i<sentence.size(); i++) {
			if (sentence[i] == target) {
				tfound = true;
				break;
			}
		}

		if (tfound) {
			for (int j=0; j<sentence.size(); j++) {
				if (sentence[j] != target) {
					histogram_add(close_counts, sentence[j]);
					histogram_add(all_counts, sentence[j]);
				}
			}
		}
	
		if (!tfound) {
			for (int j=0; j<sentence.size(); j++) {
				histogram_add(all_counts, sentence[j]);
			}
		}
	}

	vector<out_param> outers;

	for (int k=0; k<close_counts.size(); k++) {
		for(int i=0; i<all_counts.size(); i++) {
			if (close_counts[k].first == all_counts[i].first) {
				out_param tmp;
  				tmp.oword = close_counts[k].first;
  				tmp.oa_w = all_counts[i].second;
  				tmp.oc_tw = close_counts[k].second;
				tmp.os_tw = tmp.oc_tw / sqrt(tmp.oa_w);
				outers.push_back(tmp);
				}
			}
	}

	if (close_counts.size() < 10) {
		for(int i=0; i<outers.size(); i++) {
			cout << outers[i].oword << " " << outers[i].os_tw << " " << outers[i].oa_w << " " << outers[i].oc_tw << endl;
		}
	} else {
		sort(outers.begin(), outers.end(), [](const out_param& lhs, const out_param& rhs) {return lhs.os_tw > rhs.os_tw;});
		for(int j=0; j<10; j++) {
			cout << outers[j].oword << " " << outers[j].os_tw << endl;
		}
	}
}
