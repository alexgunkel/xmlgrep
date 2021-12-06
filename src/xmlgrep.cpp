#include <string>
#include <iostream>
#include "xml_grepper.hpp"

#include "params.hpp"
#include "input.hpp"

#include <CLI/CLI.hpp>

int main(int argc, char *argv[])
{
    const xmlparser::Params params{argc, argv};
    if (params.help) {
        return params.status;
    }

    auto output{createOutputFormatter(std::cout, params.count)};

    xmlgrep::XmlGrepper grepper{*output, params.tag, params.needle};

    xmlgrep::Input input{params.files};

    for (auto &in: input) {
        grepper.parse(in);
    }

    return 0;
}