set(GAME_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

aux_source_directory(src GAME_SRC)
aux_source_directory(test GAME_TEST_SRC)
list(FILTER GAME_SRC EXCLUDE REGEX "main.cpp")

find_library(ncurses ncurses)

add_executable(game ${GAME_SRC} src/main.cpp)
target_include_directories(game
  PUBLIC ${GAME_INCLUDE_DIR}
)
target_link_libraries(game
  gtank
  ncurses
)

# 测试
enable_testing()

add_executable(
  game_test
  ${GAME_TEST_SRC}
  ${GAME_SRC}
)
target_include_directories(game_test
  PUBLIC ${GAME_INCLUDE_DIR}
)
target_link_libraries(
  game_test
  GTest::gtest_main
  gtank
  ncurses
)

include(GoogleTest)
gtest_discover_tests(game_test)