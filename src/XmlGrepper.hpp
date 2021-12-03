#ifndef XMLGREP_XMLGREPPER_HPP
#define XMLGREP_XMLGREPPER_HPP

#include <iostream>
#include <string>

namespace xmlgrep {
class XmlGrepper {
public:
    XmlGrepper(const std::string& tagName, std::string  needle);

    void parse(std::istream& in, std::ostream& out);

private:
    std::string begin_;
    std::string end_;
    std::string needle_;
};
}

#endif //XMLGREP_XMLGREPPER_HPP
