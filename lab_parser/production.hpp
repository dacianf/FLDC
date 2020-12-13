#ifndef _LFTC_PRODUCTION_HPP_
#define _LFTC_PRODUCTION_HPP_

#include <string>
#include <vector>

namespace lftc {
    class production;
} // namespace lftc

class lftc::production {
    public:
        production() = default;
        production(std::string start, std::vector<std::vector<std::string>> results);
        [[nodiscard]] std::string to_string() const;
        std::string m_start;
        std::vector<std::vector<std::string>> m_results;
};

#endif // !_LFTC_PRODUCTION_HPP_
