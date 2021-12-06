
add_library(grepper STATIC xml_grepper.cpp xml_grepper.hpp output_formatter.cpp output_formatter.hpp)

add_executable(tst-grepper xml_grepper.test.cpp)
target_link_libraries(tst-grepper gtest_main grepper)

add_executable(fuzz-xmlgrep xml_grep.fuzz.test.cpp)
target_link_libraries(fuzz-xmlgrep PUBLIC grepper)
target_compile_options(fuzz-xmlgrep
        PRIVATE $<$<C_COMPILER_ID:Clang>:-g -O1 -fsanitize=fuzzer>
        )

target_link_libraries(fuzz-xmlgrep
        PRIVATE $<$<C_COMPILER_ID:Clang>:-fsanitize=fuzzer>
        )

add_executable(split-text split.cpp split/params.cpp split/params.hpp)
target_link_libraries(split-text PRIVATE CLI11::CLI11)

add_executable(xmlgrep xmlgrep.cpp params.cpp params.hpp input.cpp input.hpp)
target_link_libraries(xmlgrep PRIVATE grepper CLI11::CLI11)
install(TARGETS xmlgrep split-text
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
        COMPONENT xmlgrep
        )
