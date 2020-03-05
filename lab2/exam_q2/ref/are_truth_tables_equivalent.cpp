#include <fstream>
#include <set>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> read_truth_table(istream &src)
{
    vector<string> ones;

    string x;
    while(getline(src,x)){
        if(x.empty() || isspace(x[0])){
            continue;
        }
        int pipe=x.find('|');
        assert(pipe!=-1);
        string inputs=x.substr(0, pipe);
        char output=x[pipe+1];

        assert(output=='0' || output=='1');

        if(output=='1'){
            //cerr<<x<<endl;
            ones.push_back(inputs);
        }
    }

    return ones;
}

int main(int argc, char *argv[])
{
    ifstream file1(argv[1]);
    ifstream file2(argv[2]);

    vector<string> ones1=read_truth_table(file1);
    vector<string> ones2=read_truth_table(file2);

    if(ones1.empty() && !ones2.empty()){
        cout << ones2[0] << endl;
        return 1;
    }
    if(ones2.empty() && !ones1.empty()){
        cout << ones1[0] << endl;
        return 1;
    }

    int w1=ones1[0].size();
    int w2=ones2[0].size();

    if(w1<w2){
        string pad(w2-w1, '0');
        for(unsigned i=0; i<ones1.size(); i++){
            ones1[i] += pad;
        }
    }

    if(w1>w2){
        string pad(w1-w2, '0');
        for(unsigned i=0; i<ones2.size(); i++){
            ones2[i] += pad;
        }
    }

    assert(ones1[0].size()==ones2[1].size());

    sort(ones1.begin(), ones1.end());
    sort(ones2.begin(), ones2.end());

    for(unsigned i=0; i<min(ones1.size(),ones2.size()); i++){
        //cerr << i<< " X"<<ones1[i] <<"X Y"<<ones2[i]<<"Y"<<endl;
        if(ones1[i] != ones2[i]){
            if(ones1[i] < ones2[i]){
                cout << ones1[i] << endl;
            }else{
                cout << ones2[i] << endl;
            }
            return 1;
        }
    }

    if(ones1.size() > ones2.size()){
        cout << ones1[ones2.size()] << endl;
        return 1;
    }else if(ones1.size() < ones2.size()){
        cout << ones2[ones1.size()] << endl;
        return 1;
    }else{
        return 0;
    }

}