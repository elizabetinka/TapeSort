cmake_minimum_required(VERSION 3.23)
project(TapeSort)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)


enable_testing()
add_subdirectory(tests)


add_executable(${PROJECT_NAME} main.cpp parcing.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Tape)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)









