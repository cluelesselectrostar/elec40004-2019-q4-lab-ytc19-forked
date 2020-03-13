#include <random>
#include <cstring>
#include <random>
#include <iostream>
#include <complex>

using namespace std;

int main(int argc, char *argv[])
{
    int rows=atoi(argv[1]);
    int cols=atoi(argv[2]);

    mt19937 rng(time(0));

    cout << "bool" << endl;
    cout << rows<<" "<<cols<<endl;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            cout << (rng()&1) <<" ";
        }
        cout << endl;
    }
}
