#ifndef _LFTC_NODE_HPP_
#define _LFTC_NODE_HPP_

#include <string>
#include <memory>

namespace lftc {
    class node;
} // namespace lftc

class lftc::node
{
public:
    explicit node(std::string value);

    std::string m_value;
    size_t      m_production_no;

    std::shared_ptr<node> m_left_child;
    std::shared_ptr<node> m_right_sibling;
};

#endif // !_LFTC_NODE_HPP_
