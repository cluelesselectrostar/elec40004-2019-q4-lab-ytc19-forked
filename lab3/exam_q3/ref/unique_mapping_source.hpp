#ifndef mapping_source_hpp
#define mapping_source_hpp

#include <cstdint>
#include <utility>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class UniqueMappingSource
{
private:
    vector<char> m_letters;
    uint32_t m_s1;
    uint32_t m_s2;

    const unsigned long long M=((1ull<<31)-1);

    int next(uint32_t &x)
    {
        x=(uint64_t(x)*48271)%M;
        return x;
    }
public:
    UniqueMappingSource(unsigned sequence)
        : m_letters{'a','b','c','d','e','f','g','h','i','j','k','l','_','-'}
        , m_s1( max(1ull, sequence%M) )
        , m_s2( max(1ull, sequence%M) )
    {}
    
    pair<string,int> next_mapping()
    {
        m_s1 = (m_s1*48271ull)%M;
        m_s2 = (m_s2*16807ull)%M;

        string s;
        int x=m_s1;
        while(x>m_letters.size()){
            s.push_back(m_letters[x%m_letters.size()]);
            x=x/m_letters.size();
        }
        int i=m_s2;

        return {s,i};
    }
};

#endif
