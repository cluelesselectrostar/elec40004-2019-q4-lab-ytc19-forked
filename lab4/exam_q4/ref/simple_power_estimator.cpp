
#include "../bit_utils.hpp"
#include <cassert>
#include <string>

int main(int argc, char **argv)
{
    double energy_per_flip = 1e-15;
    double clock_rate = 100e6;

    if(argc>1){
        clock_rate = stod(argv[1]);
    }
    if(argc>2){
        energy_per_flip = stod(argv[2]);
    }

    vector<bool> prev;
    
    int cycles=0;
    int total_flips=0;

    while(1){
        vector<bool> curr=read_bit_vector(cin);
        if(curr.empty()){
            break;
        }

        if(!prev.empty()){
            assert(curr.size()==prev.size());
            for(int i=0; i<curr.size(); i++){
                if(curr[i]!=prev[i]){
                    total_flips++;
                }
            }
        }

        cycles+=1;
        prev=curr;
    }

    double P = ( total_flips * energy_per_flip ) / ( cycles / clock_rate );

    cout << prev.size() << endl;
    cout << cycles << endl;
    cout << total_flips << endl;
    cout << P << endl;
}
