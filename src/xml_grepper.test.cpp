#include "xml_grepper.hpp"

#include <gtest/gtest.h>

struct GrepperTestParams {
    std::string in;
    std::string out;
};

class GrepperTest : public testing::TestWithParam<GrepperTestParams> {

};

TEST_P(GrepperTest, testFindTag) {
    std::stringstream out{};
    Printer printer{out, ""};
    xmlgrep::XmlGrepper grepper{printer, "Tag", "needle"};
    std::stringstream input{GetParam().in};
    grepper.parse(input);

    EXPECT_EQ(GetParam().out, out.str());
}

INSTANTIATE_TEST_CASE_P

(validates, GrepperTest,
 ::testing::Values(GrepperTestParams{"<Tag><a>needle</a></Tag>\n", "<Tag><a>needle</a></Tag>\n"},
                   GrepperTestParams{"<Tag>\n<a>\nbar\n</a>\n</Tag>\n", ""},
                   GrepperTestParams{"<Tags>\n<a>\nneedle\n</a>\n</Tags>\n", ""},
                   GrepperTestParams{"<Tag>\n\tneedle\n</Tag>\t\n", "<Tag>\n\tneedle\n</Tag>\n"},
                   GrepperTestParams{"\x01\x00\x00\x00\x00\x00\x00\x00", "<Tag>\n\tneedle\n</Tag>\n"},
                   GrepperTestParams{"<Tag>\n<Tag>\nneedle\n</Tag>\n</Tag>\n",
                                     "<Tag>\n<Tag>\nneedle\n</Tag>\n</Tag>\n"},
                   GrepperTestParams{"<a>b</a><Tag>needle</Tag>\n", "        <Tag>needle</Tag>\n"},
                   GrepperTestParams{"<Tag>needle</Tag><a>b</a>\n", "<Tag>needle</Tag>\n"},
                   GrepperTestParams{"<Tag class=\"needle\"/>\n",
                                     "<Tag class=\"needle\"/>\n"},
                   GrepperTestParams{"<Tag>\n<a>\nneedle\n</a>\n</Tag>\n", "<Tag>\n<a>\nneedle\n</a>\n</Tag>\n"}));