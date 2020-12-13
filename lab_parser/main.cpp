#include "parser.hpp"
#include "parser_output.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using lftc::grammar;
using lftc::parser;
using lftc::parser_output;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

static vector<string> read_pif(string path);

int main()
{
    auto g = grammar::from_file("g2.txt");

    std::cout << "terminals:" << endl;
    for (const auto& terminal : g.get_terminals())
        std::cout << terminal << ' ';
    std::cout << std::endl;

    std::cout << "non-terminals:" << endl;
    for (const auto& nonterminal : g.get_nonterminals())
        std::cout << nonterminal << ' ';
    std::cout << std::endl;

    std::cout << "productions:" << endl;
    for (const auto& production : g.get_productions())
        std::cout << production.to_string() << endl;
    std::cout << std::endl;

    parser p(g);

    if (p.solve(read_pif("pif.out")))
    {
        std::cout << "seq accepted" << endl;

        parser_output po(g);
        po.left_child_right_sibling(p.get_prod_string());
        po.print_to_console();
        po.write_to_file("tree.out");
    }
    else
    {
        std::cout << "seq not accepted" << endl;
    }

    return 0;
}

static vector<string> read_pif(string path)
{
    ifstream       file(path);
    vector<string> tokens;
    string         line, a, b;
    std::cout << "Tokens: ";
    while (getline(file, line))
    {
        std::istringstream iss(line);
        while (iss >> a >> b)
        {
            tokens.push_back(a);
            std::cout << a << ' ';
        }
    }
    std::cout << endl;
    // file.close();
    return tokens;
}
