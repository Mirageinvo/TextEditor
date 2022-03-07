set(INCL_PATH "../Text_Editor/includes/")
set(SRCS_PATH "../Text_Editor/sources/")
set(SRCS ${SRCS_PATH}/hash_table.cpp ${SRCS_PATH}/dictionary.cpp ${SRCS_PATH}/text_editor.cpp)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests tests.cpp ${SRCS})
target_link_libraries(tests gtest_main)
target_include_directories(tests PUBLIC ${INCL_PATH})

include(GoogleTest)
gtest_discover_tests(tests)

add_custom_target(
    run_tests
    COMMENT "Running tests for Text_Editor"
    COMMAND ./tests
)
add_dependencies(run_tests tests)

target_compile_options(tests PUBLIC -fsanitize=address -g)
set_target_properties(tests PROPERTIES LINK_FLAGS "-fsanitize=address")

add_custom_target(
    run_all
    COMMENT "Running tests and main for Text_Editor"
)
add_dependencies(run_all run_tests run_main)