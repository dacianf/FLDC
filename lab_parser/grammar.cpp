#include "grammar.hpp"

#include <fstream>
#include <sstream>

using lftc::grammar;
using lftc::production;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::filesystem::path;

grammar::grammar() = default;

grammar grammar::from_file(const path& p)
{
    grammar  result;
    ifstream file(p);

    {
        string line;
        getline(file, line);

        istringstream iss(line);
        string        a;
        while (iss >> a)
            result.m_nonterminals.push_back(a);
    }

    {
        string line;
        getline(file, line);
        istringstream iss(line);
        string        a;
        while (iss >> a)
            result.m_terminals.push_back(a);
    }

    {
        file >> result.m_starting_symbol;
        file.get();
    }

    {
        string line;
        while (getline(file, line))
        {
            if (line != "")
                result.m_productions.push_back(result.split_production(line));
        }
    }

    return result;
}

const std::string& grammar::get_starting_symbol() {
    return m_starting_symbol;
}

const vector<string>& grammar::get_terminals()
{
    return m_terminals;
}

const vector<string>& grammar::get_nonterminals()
{
    return m_nonterminals;
}

const vector<production>& grammar::get_productions()
{
    return m_productions;
}

production grammar::get_production_for_nonterminal(const string& nonterminal)
{
    production result;
    for (const auto& production : get_productions())
        if (production.m_start == nonterminal)
            result = production;

    // TODO(mdibu) WTF
    return result;
}

production grammar::split_production(const string& production_string)
{
    auto position = production_string.find("->");

    class production production;
    production.m_start = production_string.substr(0, position);
    production.m_start.erase(
        remove(production.m_start.begin(), production.m_start.end(), ' '), production.m_start.end());

    string rhs = production_string.substr(position + 2, production_string.size());
    position   = rhs.find('|');

    while (position != string::npos)
    {

        vector<string> elems;
        istringstream  iss(rhs.substr(0, position));
        string         a;
        while (iss >> a)
            elems.push_back(a);

        production.m_results.push_back(std::move(elems));

        rhs      = rhs.substr(position + 1, rhs.size());
        position = rhs.find('|');
    }

    vector<string> elems;
    istringstream  iss(rhs);
    string         a;
    while (iss >> a)
        elems.push_back(a);

    production.m_results.push_back(elems);
    return production;
}
