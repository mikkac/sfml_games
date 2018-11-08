find_program(CLANG_TIDY NAMES "clang-tidy" "clang-tidy-6.0")
find_program(CLANG_FORMAT NAMES "clang-format" "clang-format-6.0")

message(STATUS "clang-format found: ${CLANG_FORMAT}")
message(STATUS "clang-tidy found: ${CLANG_TIDY}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(add_clang_tool_targets target_name source_files header_files)
    add_custom_target("${target_name}-format" COMMAND ${CLANG_FORMAT} -i -style=file ${source_files} ${header_files})
    add_custom_target("${target_name}-tidy" COMMAND ${CLANG_TIDY} -p build ${source_files} -header-filter="${CMAKE_SOURCE_DIR}/" )
endfunction()
