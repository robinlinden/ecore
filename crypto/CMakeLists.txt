project(ecore_crypto)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Sodium REQUIRED)

add_library(${PROJECT_NAME}
    include/ecore/crypto/random_bytes.h
    src/random_bytes.cpp
)

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
    PRIVATE
        sodium
)

add_subdirectory(test)
