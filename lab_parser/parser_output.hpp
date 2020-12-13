#ifndef _LFTC_PARSER_OUTPUT_HPP_
#define _LFTC_PARSER_OUTPUT_HPP_

#include "grammar.hpp"
#include "node.hpp"
#include "parser.hpp"

namespace lftc {
    class parser_output;
} // namespace lftc

class lftc::parser_output
{
public:
    explicit parser_output(grammar grammar);

    void left_child_right_sibling(std::vector<element> production_string);
    void print_to_console();
    void write_to_file(const std::filesystem::path& path);

private:
    void parse_node(std::shared_ptr<node> n, const std::vector<element>& production_string, size_t* index);
    void print_node_to_console(std::shared_ptr<node> n, std::ostream& out);

    std::shared_ptr<node>   m_tree_head;
    grammar m_grammar;
};

#endif // !_LFTC_PARSER_OUTPUT_HPP_
