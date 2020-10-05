project(ecore_util)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ecore::util ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
    INTERFACE
        cxx_std_17
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include
)

add_subdirectory(test)
