#include "params.hpp"

#include <CLI/CLI.hpp>

namespace xmlparser
{
Params::Params(int argc, char **argv) {
    CLI::App app{"xmlparser"};
    app.add_option<std::string>("--tag,-t", tag, "specify the element name for the enclosing tag")->required();
    app.add_option<std::string>("--pattern,-e", needle, "any string to search for");
    app.add_flag("-c", count, "count occurences");
    app.add_option<std::vector<std::string>>("files", files);

    try {
        app.parse(argc, argv);
    } catch (const CLI::CallForHelp& callForHelp) {
        help = true;
        status = app.exit(callForHelp);
    }
}
}