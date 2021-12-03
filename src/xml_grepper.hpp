#ifndef XMLGREP_XML_GREPPER_HPP
#define XMLGREP_XML_GREPPER_HPP

#include "output_formatter.hpp"

#include <iostream>
#include <string>

namespace xmlgrep {
class XmlGrepper {
public:
    XmlGrepper(OutputFormatter& out, const std::string& tagName, std::string  needle);

    void parse(std::istream& in);

private:
    void flush();
    bool found_{false};
    OutputFormatter& out_;
    std::string begin_;
    std::string end_;
    std::string needle_;
};
}

#endif //XMLGREP_XML_GREPPER_HPP
