project(ecore_warnings)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ecore::warnings ALIAS ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall;
        -Wextra;
        -Werror;
        -pedantic-errors;
    >
)
