#include "parser.hpp"

#include <iostream>
#include <utility>

using lftc::element;
using lftc::grammar;
using lftc::parser;
using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::vector;

element::element(string value, size_t production_no)
    : m_value(std::move(value))
    , m_production_no(production_no)
{}

parser::parser(grammar grammar)
    : m_grammar(std::move(grammar))
    , m_start("", 0)
    , m_state('q')
    , m_index(0)
{}

bool parser::solve(vector<string> sequence)
{
    m_sequence = std::move(sequence);
    // m_state = 'q';
    // m_index = 0;
    m_start = element(m_grammar.get_starting_symbol(), 0);
    m_alpha = stack<element>();
    m_beta  = stack<element>();
    m_beta.push(m_start);

    while (m_state != 'f' && m_state != 'e')
    {
        if (m_state == 'q')
        {
            if (m_beta.empty() && m_index == m_sequence.size())
                success();
            else
            {
                if (m_beta.empty())
                {
                    momentary_insuccess();
                    continue;
                }

                auto top = m_beta.top();
                if (is_nonterminal(top.m_value))
                    expand();
                else if (m_index < m_sequence.size() && top.m_value == m_sequence[m_index])
                    advance();
                else
                    momentary_insuccess();
            }
        }
        else if (m_state == 'b')
        {
            auto top = m_alpha.top();
            if (is_nonterminal(top.m_value))
                another_try();
            else
                back();
        }
    }

    return m_state != 'e';
}

vector<element> parser::get_prod_string()
{
    vector<element> result;
    while (!m_alpha.empty())
    {
        if (is_nonterminal(m_alpha.top().m_value))
            result.push_back(m_alpha.top());
        m_alpha.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}

void parser::expand()
{
    auto elem = m_beta.top();
    // std::cerr << "expanding " << elem.m_value << endl;
    m_beta.pop();

    elem.m_production_no = 1;
    m_alpha.push(elem);

    auto productions = m_grammar.get_production_for_nonterminal(elem.m_value).m_results;

    for (size_t index = productions[0].size() - 1; index != static_cast<decltype(index)>(-1); --index)
    {
        string s = productions[0][index];
        m_beta.push(element(s, 0));
    }
}

void parser::advance()
{
    // std::cerr << "advancing " << m_beta.top().m_value << endl;
    ++m_index;
    m_alpha.push(m_beta.top());
    m_beta.pop();
}

void parser::momentary_insuccess()
{
    // std::cerr << "momentary_insuccess" << endl;
    m_state = 'b';
}

void parser::back()
{
    // std::cerr << "back " << m_alpha.top().m_value << endl;
    --m_index;
    m_beta.push(m_alpha.top());
    m_alpha.pop();
}

void parser::another_try()
{
    // std::cerr << "another_try " << m_alpha.top().m_value <<  endl;
    auto elem = m_alpha.top();
    m_alpha.pop();

    if (m_index == 0 && elem.m_value == m_start.m_value)
    {
        cout << "error:" << endl
             << "\tm_state=" << m_state << endl
             << "\tm_index=" << m_index << endl
             << "\telem.m_value=" << elem.m_value << endl
             << "\telem.m_production_no=" << elem.m_production_no << endl;

        m_state = 'e';
        return;
    }

    auto productions = m_grammar.get_production_for_nonterminal(elem.m_value).m_results;
    // std::cerr << "possible productions for " << elem.m_value << " are ";
    // for(const auto& prod : productions[elem.m_production_no - 1])
    //     std::cerr << prod << ' ';
    // std::cerr << endl;

    for (size_t index = 0; index < productions[elem.m_production_no - 1].size(); ++index)
        m_beta.pop();

    if (productions.size() == elem.m_production_no)
    {
        elem.m_production_no = 0;
        m_beta.push(elem);
    }
    else
    {
        m_state = 'q';
        ++elem.m_production_no;

        m_alpha.push(elem);
        for (size_t index = productions[elem.m_production_no - 1].size() - 1; index != static_cast<decltype(index)>(-1); --index)
            m_beta.push(element(productions[elem.m_production_no - 1][index], 0));
    }
}

void parser::success()
{
    // std::cerr << "success" << endl;
    m_state = 'f';
}

bool parser::is_nonterminal(const std::string& elem)
{
    for (const auto& x : m_grammar.get_nonterminals())
        if (elem == x)
            return true;

    return false;
}
