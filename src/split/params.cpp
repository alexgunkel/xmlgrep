#include "params.hpp"

#include <CLI/CLI.hpp>

namespace split {

Params::Params(int argc, char **argv) {
    CLI::App app;

    app.add_option("--delimiter,-d", delimiter);
    app.add_option("--path", directory);
    app.add_option("--pre", prefix);
    app.add_option("--post", postfix);

    try {
        app.parse(argc, argv);
    } catch (const CLI::Error& callForHelp) {
        app.exit(callForHelp);
        valid = false;
    }
}
}