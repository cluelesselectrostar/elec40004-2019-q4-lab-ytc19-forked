#include "row_set_factory.hpp"
#include "row_set_float.hpp"
#include "row_set_bool.hpp"
#include "row_set_complex.hpp"

RowSet *create_row_set(const string &field)
{
    if(field=="float"){
        return new RowSetFloat();
    }else if(field=="bool"){
        return new RowSetBool();
    }else if(field=="complex"){
        return new RowSetComplex();
    }else{
        cerr<<"Unknown field "<<field<<endl;
        exit(1);
    }
}

RowSet *read_row_set(istream &src)
{
    string field;
    src >> field;
    RowSet *res=create_row_set(field);
    int rows, cols;
    src >> rows >> cols;
    res->Resize(rows,cols);
    for(int r=1; r<=rows; r++){
        for(int c=1; c<=cols; c++){
            res->ReadBuffer(src);
            res->StoreBuffer(r,c);
        }
    }
    return res;
}

void write_row_set(RowSet *A, ostream &dst)
{
    dst << A->FieldName() << endl;
    dst << A->RowCount() << " " << A->ColCount() << endl;
    int rows=A->RowCount();
    int cols=A->ColCount();
    for(int r=1; r<=rows; r++){
        for(int c=1; c<=cols; c++){
            if(c!=1){
                dst << " ";
            }
            A->LoadBuffer(r,c);
            A->WriteBuffer(dst);
        }
        dst<<endl;
    }
}