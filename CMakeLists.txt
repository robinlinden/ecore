cmake_minimum_required(VERSION 3.11)

project(ecore)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

enable_testing()

add_subdirectory(crypto)
add_subdirectory(network)
