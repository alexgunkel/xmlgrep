#include "xml_grepper.hpp"

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

void XmlGrepper::parse(std::istream &in, OutputFormatter &out) {
    std::string line;
    uint64_t depth{0};
    bool found{false};
    while (std::getline(in, line)) {
        if (containsTag(begin_, line)) {
            depth++;
        }

        if (depth) {
            out.addLine(line);
        }

        if (depth && !found && line.find(needle_) != std::string::npos) {
            found = true;
        }

        if (depth && containsTag(end_, line)) {
            depth--;
            if (!depth && found) {
                found = false;
                out.addEntry();
            }
            if (!depth) {
                out.reset();
            }
        }
    }
}
}