
add_library(grepper STATIC XmlGrepper.cpp XmlGrepper.hpp)

add_executable(xmlgrep main.cpp)
target_link_libraries(xmlgrep PRIVATE grepper)
