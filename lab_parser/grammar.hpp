#ifndef _LFTC_GRAMMAR_H_
#define _LFTC_GRAMMAR_H_

#include "production.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace lftc {
    class grammar;
} // namespace lftc

class lftc::grammar
{
public:
    static grammar                  from_file(const std::filesystem::path& path);
    const std::string&              get_starting_symbol();
    const std::vector<std::string>& get_terminals();
    const std::vector<std::string>& get_nonterminals();
    const std::vector<production>&  get_productions();
    production                      get_production_for_nonterminal(const std::string& nonterminal);

private:
    grammar();
    static production        split_production(const std::string& production);
    std::vector<std::string> m_terminals;
    std::vector<std::string> m_nonterminals;
    std::vector<production>  m_productions;
    std::string              m_starting_symbol;
};

#endif // !_LFTC_GRAMMAR_H_
