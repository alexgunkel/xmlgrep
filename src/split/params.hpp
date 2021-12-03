#ifndef XMLGREP_PARAMS_HPP
#define XMLGREP_PARAMS_HPP

#include <filesystem>
#include <string>

namespace split {
class Params {
public:
    Params(int argc, char ** argv);

    std::string delimiter{"--"};
    std::filesystem::path directory;
    std::string prefix{"file-"};
    std::string postfix{".split"};
    bool valid{false};
};
}

#endif //XMLGREP_PARAMS_HPP
