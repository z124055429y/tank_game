cmake_minimum_required(VERSION 3.26.3)
project(game)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# jsoncpp
# FetchContent_Declare(
#   jsoncpp
#   URL https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.zip
# )

# FetchContent_MakeAvailable(jsoncpp)

add_subdirectory(tank)
add_subdirectory(game)