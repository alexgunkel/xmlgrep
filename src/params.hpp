#ifndef XMLGREP_PARAMS_HPP
#define XMLGREP_PARAMS_HPP

#include <string>
#include <vector>

namespace xmlparser {
class Params {
public:
    Params(int argc, char *argv[]);

    bool count{};
    bool help{};
    std::string tag{};
    std::string needle{};
    std::string file{};
    std::vector<std::string> files{};
    std::string delimiter{};
    int status{0};
};
}
#endif //XMLGREP_PARAMS_HPP
