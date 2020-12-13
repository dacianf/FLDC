#include "node.hpp"

#include <utility>

using lftc::node;
using std::string;

node::node(string value)
    : m_value(std::move(value))
    , m_production_no(0)
    , m_left_child(nullptr)
    , m_right_sibling(nullptr)
{}
