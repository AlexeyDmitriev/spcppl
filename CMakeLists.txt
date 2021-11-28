set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wformat=2")

file(GLOB_RECURSE HEADERS "spcppl/*.hpp")

add_library(spcppl INTERFACE)
target_include_directories(spcppl INTERFACE .)
target_sources(spcppl INTERFACE ${HEADERS})

file(GLOB_RECURSE TESTS "tests/*.?pp")
add_executable(tests ${TESTS})
target_link_libraries(tests spcppl)

add_subdirectory(gtest)
target_link_libraries(tests gtest_main)
target_compile_options(tests PRIVATE -Werror -std=c++2a)
