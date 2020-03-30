
#include "../bit_utils.hpp"
#include <cassert>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
    double clock_rate = stod(argv[1]);
    string energy_per_flip_file = argv[2];

    vector<double> energy_per_flip;

    std::ifstream energy_per_flip_stream(energy_per_flip_file);
    while(1){
        double x;
        energy_per_flip_stream >> x;
        if(energy_per_flip_stream.fail()){
            break;
        }
        energy_per_flip.push_back(x);
    }

    vector<bool> prev;
    
    int cycles=0;
    int total_flips=0;

    vector<int> flip_counts(energy_per_flip.size(), 0);

    while(1){
        vector<bool> curr=read_bit_vector(cin);
        if(curr.empty()){
            break;
        }

        assert(curr.size()==energy_per_flip.size());

        if(!prev.empty()){
            vector<int> flip_positions=bit_flip_positions_in_vector(curr, prev);
            for(int i=0; i<flip_positions.size(); i++){
                flip_counts[flip_positions[i]]+=1;
                total_flips+=1;
            }
        }

        cycles+=1;
        prev=curr;
    }

    double P=0;
    for(int i=0; i<flip_counts.size(); i++){
        P += ( flip_counts[i] * energy_per_flip[i] ) / ( cycles / clock_rate );
    }

    cout << prev.size() << endl;
    cout << cycles << endl;
    cout << total_flips << endl;
    cout << P << endl;
    for(int i=0; i<flip_counts.size(); i++){
        cout << ( flip_counts[i] * energy_per_flip[i] ) / ( cycles / clock_rate ) << endl;
    }
}
