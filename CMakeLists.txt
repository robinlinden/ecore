cmake_minimum_required(VERSION 3.14)

project(ecore)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(third_party/catch2)
add_subdirectory(third_party/sodium)

enable_testing()

add_subdirectory(warnings)

add_subdirectory(core)
add_subdirectory(crypto)
add_subdirectory(node_info)
add_subdirectory(util)
