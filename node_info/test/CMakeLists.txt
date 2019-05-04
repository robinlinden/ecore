include(Catch)
include(FetchContent)

project(test_ecore_node_info)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.7.0
)

FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/test_node_info.cpp
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Catch2::Catch2
        ecore::warnings
        ecore_node_info
)

catch_discover_tests(${PROJECT_NAME})
