#ifndef _LFTC_PARSER_HPP_
#define _LFTC_PARSER_HPP_

#include "grammar.hpp"

#include <stack>
#include <string>
#include <vector>

namespace lftc {
    class element;
    class parser;
} // namespace lftc

class lftc::element
{
public:
    element(std::string value, uint64_t production_no);

    std::string m_value;
    uint64_t m_production_no;
};

class lftc::parser
{
public:
    explicit parser(grammar g);
    bool                 solve(std::vector<std::string> sequence);
    std::vector<element> get_prod_string();

private:
    void expand();
    void advance();
    void momentary_insuccess();
    void back();
    void another_try();
    void success();

    bool is_nonterminal(const std::string& element);

    grammar                  m_grammar;
    std::vector<std::string> m_sequence;
    element                  m_start;
    char                     m_state;
    uint32_t                 m_index;
    std::stack<element>      m_alpha;
    std::stack<element>      m_beta;
};

#endif // !_LFTC_PARSER_HPP_
