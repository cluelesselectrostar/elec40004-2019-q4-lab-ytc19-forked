#include "SOP.hpp"

#include "SOP_helpers.hpp"

void write_truth_table_row(uint64_t input, int num_inputs)
{
    for(unsigned i=0; i<num_inputs; i++){
        if( (input>>i)&1 ){
            cout << "1";
        }else{
            cout << "0";
        }
    }
    cout<<"|1"<<endl;
}

int main()
{
    string sop_form;
    getline(cin, sop_form);

    cerr<<"SOP (str) = "<<sop_form<<endl;
    SOP tt=SOP_from_string(sop_form);
    cerr<<"SOP = "<<SOP_to_string(&tt)<<endl;

    int num_inputs=SOP_largest_input_index(&tt);
    cerr<<"Num inputs = "<<num_inputs<<endl;

    uint64_t max_x=(uint64_t(1)<<num_inputs)-1;
    for(uint64_t x=0; x<=max_x; x++){
        if(SOP_evaluate(&tt, x)){
            write_truth_table_row(x, num_inputs);
        }
    }
}
