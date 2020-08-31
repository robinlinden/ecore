include(FetchContent)

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 7f21cc6c5599f59835f769debf13b4c3e6148a28 # v2.13.0
)
FetchContent_MakeAvailable(Catch2)

FetchContent_GetProperties(Catch2
    SOURCE_DIR Catch2_SOURCE_DIR
)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/contrib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
