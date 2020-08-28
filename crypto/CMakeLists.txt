project(ecore_crypto)

add_library(${PROJECT_NAME}
    include/ecore/crypto.h
    src/ecore/crypto.cpp
)
add_library(ecore::crypto ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
    PRIVATE
        src
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ecore::core
    PRIVATE
        ecore::warnings
        sodium
)

add_subdirectory(test)
