#include "bit_utils.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	double clock_rate = 100e6;
	if(argv[1]!=NULL){
		clock_rate = argv[1];
	}

	double per_energy_signal = 1e-12;
	if(argv[2]!=NULL){
		per_energy_signal = argv[2];
	}
	
	int no_of_signals;
	int cycle_count = 0;
	int total_flips = 0;
	double power;
	vector<bool> current_cycle;
	vector<bool> previous_cycle;

	while(!cin.fail()){
		if(cycle_count>0){
		previous_cycle = current_cycle;
		}
		current_cycle = read_bit_vector(cin);
		if(cycle_count>0){
			vector<int> flip_positions = bit_flip_positions_in_vector(current_cycle, previous_cycle);
			total_flips += flip_positions.size();
			}
		cycle_count++;
	}

	no_of_signals = current_cycle.size();
	power = (total_flips * per_energy_signal) / (cycle_count * clock_rate);

	cout << no_of_signals << endl;
	cout << cycle_count << endl;
	cout << power << scientifc << endl;
}
