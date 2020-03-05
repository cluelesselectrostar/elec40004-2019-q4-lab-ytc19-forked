#ifndef mapping_source_hpp
#define mapping_source_hpp

#include <cstdint>
#include <utility>
#include <string>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

class RepeatingMappingSource
{
private:
    vector<char> m_letters;
    std::mt19937 m_src;
public:
    RepeatingMappingSource(unsigned sequence)
        : m_letters{'a','b','c','d','e','f','g','h','i','j','k','l','_','-'}
        , m_src(sequence)
    {}
    
    pair<string,int> next_mapping()
    {
        string s;
        int x=m_src()>>1;
        while(x>m_letters.size()){
            s.push_back(m_letters[x%m_letters.size()]);
            x=x/m_letters.size();
        }
        int i=m_src()>>1;

        return {s,i};
    }
};

#endif
