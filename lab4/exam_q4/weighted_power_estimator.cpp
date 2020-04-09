#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "bit_utils.hpp"

using namespace std;

vector<bool> read_bit(string s)
{
	vector<bool> out;
	for(int i=0; i<s.length(); i++){
		bool bit;
		if(s[i]=='0'){
			bit = false;
		}
		if(s[i]=='1'){
			bit = true;
		}
		out.push_back(bit);
	}
	return out;
}

int main(int argc, char** argv)
{
	assert(argc>=3);
	double clock_rate = stod(argv[1]);
	string per_signal_energy = argv[2];
	
	ifstream file (per_signal_energy);

	vector<double> pse;
	double tmp_pse;
	while(file >> tmp_pse)
	{
		pse.push_back(tmp_pse);
	}

	int signals;
	int cycle_count = -1;
	vector<int> flips = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	double total_flips = 0;
	vector<double> per_power;
	double total_power = 0;
	string cc;
	string pc;

	while(!cin.fail()){
		cin >> cc;
		if(cycle_count>=0){
			if(cc!=pc){
				vector<bool> vcc = read_bit(cc);
				vector<bool> vpc = read_bit(pc);
				vector<int> flip_positions = bit_flip_positions_in_vector(vcc, vpc);
				for(int i=0; i<flip_positions.size(); i++){
					int flip_p = flip_positions[i];
					flips[flip_p]++;
				}
			}
		}	
		pc = cc;
		cycle_count++;
	}

	signals = cc.length();

	for(int j=0; j<pse.size(); j++){
		double tmp_power = (flips[j]*pse[j])/(cycle_count/clock_rate);
		per_power.push_back(tmp_power);
	}

	for(int j=0; j<per_power.size(); j++){
		total_power += per_power[j];
	}

	for(int j=0; j<flips.size(); j++){
		total_flips += flips[j];
	}

	cout << signals << endl;
	cout << cycle_count << endl;
	cout << total_flips << endl;
	cout << total_power << endl;
	for(int j=0; j<per_power.size(); j++){
		cout << per_power[j] << endl;
	}
}
