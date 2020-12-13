#include "production.hpp"

#include <utility>

using lftc::production;
using std::string;
using std::vector;

production::production(string start, vector<vector<string>> results)
    : m_start(std::move(start))
    , m_results(std::move(results))
{}

string production::to_string() const {
    string s = m_start + "->";
    
    for(size_t index = 0; index < m_results.size(); ++index)
    {
        for(const auto& a : m_results[index])
            s += a + ' ';

        if (index < m_results.size() - 1)
            s += "| ";
    }
    return s;
}
