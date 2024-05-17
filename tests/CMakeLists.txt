include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        sortTests
        sortTests.cpp
)

target_link_libraries(
        sortTests
        Tape
        GTest::gtest_main
)

target_include_directories(sortTests PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(sortTests PUBLIC ../test)
target_include_directories(sortTests PUBLIC ../lib)
target_include_directories(sortTests PUBLIC ../tmp)

include(GoogleTest)

gtest_discover_tests(sortTests)