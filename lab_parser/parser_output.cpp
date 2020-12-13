#include "parser_output.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>

using lftc::grammar;
using lftc::node;
using lftc::parser_output;
using std::endl;
using std::queue;
using std::shared_ptr;
using std::vector;

parser_output::parser_output(grammar grammar)
    : m_tree_head(nullptr)
    , m_grammar(std::move(grammar))
{}

void parser_output::left_child_right_sibling(vector<element> production_string)
{
    if (production_string.empty())
        return;

    m_tree_head = std::make_shared<node>("");

    m_tree_head->m_value         = production_string[0].m_value;
    m_tree_head->m_production_no = production_string[0].m_production_no;

    size_t index = 1;
    parse_node(m_tree_head, production_string, &index);
}

void parser_output::print_node_to_console(shared_ptr<node> node, std::ostream& out)
{
    queue<shared_ptr<class node>> next;
    out << node->m_value;

    if (node->m_left_child.get() != nullptr)
        next.push(node->m_left_child);

    auto aux = node;
    while (aux->m_right_sibling != nullptr)
    {
        aux = aux->m_right_sibling;
        out << ' ' << aux->m_value;

        if (aux->m_left_child != nullptr)
            next.push(aux);
    }

    out << endl;

    if (node->m_left_child != nullptr)
        out << "Left child: " << node->m_left_child->m_value << endl;
    out << endl;

    while (!next.empty())
    {
        print_node_to_console(next.front(), out);
        next.pop();
    }
}

void parser_output::print_to_console()
{
    print_node_to_console(m_tree_head, std::cout);
}

void parser_output::write_to_file(const std::filesystem::path& path)
{
    std::ofstream out(path);
    print_node_to_console(m_tree_head, out);
    // out.close();
}

void parser_output::parse_node(
    std::shared_ptr<node>       node,
    const std::vector<element>& production_string,
    size_t*                    index)
{
    production p;
    for (const auto& el : production_string)
    {
        p = m_grammar.get_production_for_nonterminal(el.m_value);

        node->m_left_child.reset(new class node(""));
        node          = node->m_left_child;
        node->m_value = p.m_results[el.m_production_no - 1][0];

        if (*index < production_string.size() && node->m_value == production_string[*index].m_value)
        {
            ++*index;
            parse_node(node, production_string, index);
        }

        for (size_t i = 1; i < p.m_results[el.m_production_no - 1].size(); ++i)
        {
            node->m_right_sibling.reset(new class node(""));
            node          = node->m_right_sibling;
            node->m_value = p.m_results[el.m_production_no - 1][i];

            if (*index < production_string.size() && node->m_value == production_string[*index].m_value)
            {
                ++*index;
                parse_node(node, production_string, index);
            }
        }
    }
}
