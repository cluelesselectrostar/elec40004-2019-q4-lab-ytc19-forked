#ifndef row_set_bool_hpp
#define row_set_bool_hpp


#include "row_set.hpp"

#include <vector>
#include <cassert>

class RowSetBool
    : public RowSet
{
private:
    int m_r;
    int m_c;
    vector<vector<bool>> m_A;
    bool m_B;
public:
    virtual std::string FieldName() const
    { return "bool"; }

    virtual int RowCount() const override
    { return m_r; }

    virtual int ColCount() const override 
    { return m_c; }

    virtual void Resize(int rows, int cols) override
    {
        m_A.resize(rows+1);
        for(int r=1; r<=rows; r++){
            m_A[r].resize(cols+1, false);
        }
        m_r=rows;
        m_c=cols;
    }

    virtual void ZeroBuffer() override
    { m_B = false; }

    virtual void UnitBuffer() override
    { m_B = true; }

    virtual void LoadBuffer(int r, int c) override
    { m_B = m_A[r][c]; }

    virtual void StoreBuffer(int r, int c) override
    { m_A[r][c] = m_B; }

    virtual void SwapBuffer(int r, int c) override
    { swap( m_B, m_A[r][c]); }

    virtual void MulBuffer(int r, int c) override
    { m_B = m_B && m_A[r][c]; }

    virtual void AddBuffer(int r, int c) override
    { m_B = m_B ^ m_A[r][c]; }

    virtual void NegBuffer() override
    { /* no-op for bool field */ }

    virtual void InvBuffer() override
    {
        assert(m_B);
        m_B = true;;
    }

    virtual bool MaxAbsBuffer(int r, int c) override
    {
        if(m_A[r][c] && !m_B){
            m_B=true;
            return true;
        }else{
            return false;
        }
    }

    virtual ostream &WriteBuffer(ostream &dst) const override
    { return dst << m_B; }

    virtual istream &ReadBuffer(istream &dst) override
    { return dst >> m_B; }

    virtual bool IsUnit(int r, int c) const override
    { return m_A[r][c]; }
    
    virtual bool IsZero(int r, int c) const override
    { return !m_A[r][c]; }
    
    virtual void SwapRows(int r1, int r2) override
    { swap(m_A[r1], m_A[r2] ); }

    virtual void MultiplyRow(int row) override
    {
        if(m_B){
            // do nothing
        }else{
            m_A[row].assign(m_c+1, false);
        }
    }

    virtual void AddMultipleOfRow(int row, int src_row) override
    {
        if(m_B){
            for(int c=1; c<=m_c; c++){
                m_A[row][c] = m_A[row][c] ^ m_A[src_row][c];  
            }
        }
    }
};



#endif
