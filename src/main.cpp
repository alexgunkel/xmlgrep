#include <string>
#include <iostream>
#include "xml_grepper.hpp"

#include <CLI/CLI.hpp>

int main(int argc, char *argv[])
{
    CLI::App app{"xmlparser"};
    std::string tag{};
    std::string needle{};
    std::string file{};
    bool countOnly{false};
    app.add_option<std::string>("--tag", tag, "tag to report")->required();
    app.add_option<std::string>("--needle", needle, "tag to report");
    app.add_flag("-c", countOnly);
    app.add_option<std::string>("file", file);
    CLI11_PARSE(app, argc, argv);

    std::unique_ptr<OutputFormatter> output;
    if (countOnly) {
        output = std::make_unique<Counter>(std::cout);
    } else {
        output = std::make_unique<Printer>(std::cout);
    }

    xmlgrep::XmlGrepper grepper{*output, tag, needle};

    if (file.empty()) {
        grepper.parse(std::cin);
    } else {
        std::fstream fileStream{file};
        grepper.parse(fileStream);
    }

    return 0;
}