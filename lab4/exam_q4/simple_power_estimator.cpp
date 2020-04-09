#include "bit_utils.hpp"
#include <iostream>
#include <string>

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
	double per_energy_signal;
	double clock_rate;
	if(argc>=3){
		clock_rate = stod(argv[1]);
		per_energy_signal = stod(argv[2]);
	}else{
		clock_rate = 100e6;
		per_energy_signal = 1e-12;
	}
	
	int signals;
	int cycle_count = -1;
	int total_flips = 0;
	double power;
	string cc;
	string pc;

	while(!cin.fail()){
		cin >> cc;
		if(cycle_count>=0){
			if(cc!=pc){
				vector<bool> vcc = read_bit(cc);
				vector<bool> vpc = read_bit(pc);
				vector<int> flip_positions = bit_flip_positions_in_vector(vcc, vpc);
				total_flips += flip_positions.size();
			}
		}
		pc = cc;
		cycle_count++;
	}

	signals = cc.size();
	power = (total_flips*per_energy_signal)/(cycle_count/clock_rate);

	cout << signals << endl;
	cout << cycle_count << endl;
	cout << total_flips << endl;
	cout << power << endl;
}
