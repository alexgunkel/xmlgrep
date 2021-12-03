
add_library(grepper STATIC xml_grepper.cpp xml_grepper.hpp output_formatter.cpp output_formatter.hpp)

add_executable(tst-grepper xml_grepper.test.cpp)
target_link_libraries(tst-grepper gtest_main grepper)

add_executable(xmlgrep main.cpp)
target_link_libraries(xmlgrep PRIVATE grepper CLI11::CLI11)
install(TARGETS xmlgrep
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
        COMPONENT xmlgrep
        )
