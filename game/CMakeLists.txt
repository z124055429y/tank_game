set(GAME_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

aux_source_directory(src GAME_SRC)

find_library(ncurses ncurses)

add_executable(game ${GAME_SRC})
target_include_directories(game
  PUBLIC ${GAME_INCLUDE_DIR}
)
target_link_libraries(game
  gtank
  ncurses
)