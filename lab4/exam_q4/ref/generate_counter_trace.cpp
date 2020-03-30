
#include "../bit_utils.hpp"
#include <cassert>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
    int n=stoi(argv[1]);

    for(uint64_t i=0; i< uint64_t(1)<<n ; i++){
        write_bits_in_word(i, n, cout);
        cout << endl;
    }
    write_bits_in_word(0, n, cout);
    cout << endl;    

}
