include(Catch)

project(test_ecore_node_info)

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
        ecore::node_info
        ecore::warnings
)

catch_discover_tests(${PROJECT_NAME})
