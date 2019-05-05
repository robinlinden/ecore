project(ecore_crypto)

include(FetchContent)

FetchContent_Declare(
    Sodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
    GIT_TAG c6171bfca479fb2ee375e2b1f55e174ed79c4f87
)

FetchContent_GetProperties(Sodium)
if(NOT sodium_POPULATED)
    set(SODIUM_DISABLE_TESTS ON CACHE INTERNAL "")

    FetchContent_Populate(Sodium)
    add_subdirectory(
        ${sodium_SOURCE_DIR}
        ${sodium_BINARY_DIR}
    )
endif()

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
