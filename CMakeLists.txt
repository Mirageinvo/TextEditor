cmake_minimum_required(VERSION 3.16.3)
project(Text_Editor VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 20)

set(PATH Text_Editor/sources)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB_RECURSE SOURCE_FILES ./Text_Editor/*.cpp)
file(GLOB_RECURSE DICT_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format -i ${DICT_FILES}
)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=*.hpp;
)

add_executable(main ${SOURCE_FILES})
target_include_directories(main PUBLIC Text_Editor/includes/)

add_custom_target(
    run_main
    COMMAND ./main
)
add_dependencies(run_main main)

if (ADD_SANITIZERS)
    target_compile_options(main PUBLIC -fsanitize=address -g)
    set_target_properties(main PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()