cmake_minimum_required(VERSION 3.16.3)
project(Text_Editor VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 20)

set(PATH Text_Editor/sources)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB_RECURSE SOURCE_FILES ./Text_Editor/*.cpp)
file(GLOB_RECURSE DICT_FILES *.cpp *.hpp)

add_compile_options (
    -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls
    -Wnon-virtual-dtor -Woverloaded-virtual 
)

add_custom_target(
    clang_format
    COMMAND clang-format -i ${DICT_FILES}
)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=.*;
)

add_subdirectory("Text_Editor")
add_subdirectory("tests")