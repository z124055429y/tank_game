set(TANK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

aux_source_directory(src TANK_SRC)
aux_source_directory(test TANK_TEST_SRC)

add_library(gtank ${TANK_SRC})
target_include_directories(gtank
  PUBLIC ${TANK_INCLUDE_DIR}
)

# 测试
enable_testing()

add_executable(
  gtank_test
  ${TANK_TEST_SRC}
)
target_link_libraries(
  gtank_test
  GTest::gtest_main
  gtank
)

include(GoogleTest)
gtest_discover_tests(gtank_test)