#include "bit_utils.hpp"
#include <iostream>
#include <string>

using namespace std;

vector<bool> read_bits(string s)
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
	double clock_rate = 1e8;
	/*if(argv[1]!=NULL){
		clock_rate = *argv[1];
	}*/

	double per_energy_signal = 1e-15;
	/*if(argv[2]!=NULL){
		per_energy_signal = *argv[2];
	}*/
	
	int no_of_signals;
	int cycle_count = -1;
	int total_flips = 1;
	double power;
	vector<bool> current_cycle;
	vector<bool> previous_cycle;
	string cc;

	while(!cin.fail()){
		cin >> cc;
		current_cycle = read_bits(cc);
		if(cycle_count>=1){
			vector<int> flip_positions = bit_flip_positions_in_vector(current_cycle, previous_cycle);
			total_flips = total_flips + flip_positions.size();
		}
		previous_cycle = current_cycle;
		cycle_count++;
	}

	no_of_signals = current_cycle.size();
	power = (total_flips*per_energy_signal)/(cycle_count*clock_rate);

	cout << no_of_signals << endl;
	cout << cycle_count << endl;
	cout << total_flips << endl;
	cout << power << endl;
}
