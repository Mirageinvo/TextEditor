cmake_minimum_required(VERSION 3.16.3)
project(Text_Editor VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 20)

set(PATH Text_Editor/sources)

add_executable(main main.cpp ${PATH}/dictionary.cpp ${PATH}/hash_table.cpp ${PATH}/text_editor.cpp)
target_include_directories(main PUBLIC Text_Editor/includes/)

add_custom_target(
    run_main
    COMMAND ./main
)
add_dependencies(run_main main)