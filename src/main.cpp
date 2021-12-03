#include <string>
#include <iostream>
#include "XmlGrepper.hpp"

enum class State
{
    outside,
    inside,
};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        return 1;
    }
    const std::string tag{argv[1]};
    const std::string needle{argv[2]};

    xmlgrep::XmlGrepper grepper{tag, needle};
    grepper.parse(std::cin, std::cout);

    return 0;
}