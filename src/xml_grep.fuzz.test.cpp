#include "xml_grepper.hpp"

#include <string>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    std::string input(reinterpret_cast<const char*>(data), size);
    std::stringstream inputStream{input};
    std::ostream out(0);
    Counter printer{out};
    xmlgrep::XmlGrepper xmlGrepper{printer, "A", "b"};
    xmlGrepper.parse(inputStream);
    return 0;
}
