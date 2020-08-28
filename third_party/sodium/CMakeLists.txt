include(FetchContent)

FetchContent_Declare(Sodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
    GIT_TAG 6f384498d2f6a8e33797697349b00dfd8a985d1e
)
set(SODIUM_DISABLE_TESTS ON)
FetchContent_MakeAvailable(Sodium)
