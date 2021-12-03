#include "XmlGrepper.hpp"

#include <utility>
#include <vector>

namespace xmlgrep {

XmlGrepper::XmlGrepper(const std::string &tagName, std::string needle) : begin_{"<" + tagName},
                                                                         end_{"</" + tagName},
                                                                         needle_{std::move(needle)} {

}

namespace
{
bool containsTag(const std::string& needle, const std::string& hayStack)
{
    const auto pos{hayStack.find(needle)};
    if (pos == std::string::npos) {
        return false;
    }

    const auto c{hayStack[pos + needle.size()]};
    return c == '>' || c == ' ';
}
}

void XmlGrepper::parse(std::istream &in, std::ostream &out) {
    std::string line;
    uint64_t depth{0};
    bool found{false};
    std::vector<std::string> cache;
    while (std::getline(in, line)) {
        if (containsTag(begin_, line)) {
            depth++;
        }

        if (depth) {
            cache.push_back(line);
        }

        if (depth && !found && line.find(needle_) != std::string::npos) {
            found = true;
        }

        if (depth && containsTag(end_, line)) {
            depth--;
            if (!depth && found) {
                found = false;
                for (const auto &l: cache) {
                    out << l << "\n";
                }
            }
            if (!depth) {
                cache.clear();
            }
        }
    }
}
}