add_library(testthingy parser.cpp parser.hpp spec_parser.cpp spec_parser.hpp StudentCode.hpp util.hpp)

add_executable(testinglib_exe main.cpp)
target_link_libraries(testinglib_exe PUBLIC testthingy)
