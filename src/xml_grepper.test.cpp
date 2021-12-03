#include "xml_grepper.hpp"

#include <gtest/gtest.h>

struct GrepperTestParams {
    std::string in;
    std::string out;
};

class GrepperTest : public testing::TestWithParam<GrepperTestParams> {

};

TEST_P(GrepperTest, testFindTag) {
    xmlgrep::XmlGrepper grepper{"Tag", "needle"};
    std::stringstream input{GetParam().in};
    std::stringstream out{};
    Printer printer{out};
    grepper.parse(input, printer);

    EXPECT_EQ(GetParam().out, out.str());
}

INSTANTIATE_TEST_CASE_P

(validates, GrepperTest,
 ::testing::Values(GrepperTestParams{"<Tag><a>needle</a></Tag>\n", "<Tag><a>needle</a></Tag>\n"},
                   GrepperTestParams{"<Tag>\n<a>\nbar\n</a>\n</Tag>\n", ""},
                   GrepperTestParams{"<Tags>\n<a>\nneedle\n</a>\n</Tags>\n", ""},
                   GrepperTestParams{"<Tag>\n<Tag>\nneedle\n</Tag>\n</Tag>\n", "<Tag>\n<Tag>\nneedle\n</Tag>\n</Tag>\n"},
                   GrepperTestParams{"<Tag>\n<a>\nneedle\n</a>\n</Tag>\n", "<Tag>\n<a>\nneedle\n</a>\n</Tag>\n"}));