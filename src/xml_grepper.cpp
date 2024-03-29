#include "xml_grepper.hpp"

#include <utility>
#include <vector>

namespace xmlgrep {

XmlGrepper::XmlGrepper(OutputFormatter &outputFormatter, const std::string &tagName, std::string needle) :
        out_{outputFormatter}, begin_{"<" + tagName},
        end_{"</" +
             tagName +
             ">"},
        needle_{std::move(
                needle)} {

}

namespace {
std::pair<uint64_t, bool> containsTag(const std::string_view needle, const std::string &hayStack) {
    const auto pos{hayStack.find(needle)};
    if (pos == std::string::npos) {
        return {0, false};
    }

    if (const auto c{hayStack[pos + needle.size()]}; c == '>' || c == ' ') {
        return {pos, true};
    }

    return {0, false};
}
}

void XmlGrepper::parse(std::istream &in) {
    std::string line;
    uint64_t depth{0};
    bool isOpen{false};
    bool isSelfClosing{false};
    size_t closingSignPosition{};
    while (std::getline(in, line)) {
        const auto[pos, containsStartTag] = containsTag(begin_, line);
        if (containsStartTag) {
            depth++;
            std::fill_n(line.begin(), pos, ' ');

            isOpen = true;
        }

        if (isOpen) {
            closingSignPosition = line.find('>');
            isOpen = closingSignPosition == std::string::npos;
            isSelfClosing = !isOpen && line[closingSignPosition + 1] == '/';
        }

        if (depth) {
            if (isSelfClosing) {
                line.resize(closingSignPosition + 1);
                depth--;
            } else if (const auto posOfEndTag = line.find(end_); posOfEndTag != std::string::npos) {
                line.resize(posOfEndTag + end_.size());
                depth--;
            }
            out_.addLine(line);

            found_ |= line.find(needle_) != std::string::npos;

            if (!depth) {
                flush();
            }
        }
    }
    flush();
}

void XmlGrepper::flush() {
    if (found_) {
        out_.addEntry();
        found_ = false;
    } else {
        out_.reset();
    }
}
}