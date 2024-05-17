cmake_minimum_required(VERSION 3.23)
project(TapeSort)

set(CMAKE_CXX_STANDARD 20)



add_executable(TapeSort main.cpp Tape.cpp parcing.cpp TapeSorter.cpp)


include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(TapeSort PRIVATE nlohmann_json::nlohmann_json)

