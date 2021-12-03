#include <iostream>
#include <fstream>
#include "split/params.hpp"

int main(int argc, char **argv) {
    split::Params params{argc, argv};

    std::string line{};
    auto create{[params]() -> std::unique_ptr<std::ostream> {
        static int index{0};
        const auto fileName{params.prefix + std::to_string(index) + params.postfix};
        index++;
        std::cout << fileName << "\n";
        return std::make_unique<std::ofstream>(fileName);
    }};

    auto out{create()};
    while (std::getline(std::cin, line)) {
        if (const auto pos{line.find(params.delimiter)}; pos != std::string::npos) {
            if (pos) {
                *out << line.substr(0, pos) << "\n";
            }
            out = create();
            if (pos + params.delimiter.length() < line.length()) {
                *out << line.substr(pos + params.delimiter.length()) << "\n";
            }
        } else {
            *out << line << "\n";
        }
    }

    return 0;
}