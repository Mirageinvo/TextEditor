add_executable(main ${SOURCE_FILES})
target_include_directories(main PUBLIC includes/)

add_custom_target(
    run_main
    COMMAND ./main
)
add_dependencies(run_main main)

if (ADD_SANITIZERS)
    target_compile_options(main PUBLIC -fsanitize=address -g)
    set_target_properties(main PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()