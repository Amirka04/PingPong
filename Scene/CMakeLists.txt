cmake_minimum_required(VERSION 3.5)


add_library(MenuScene STATIC MenuScene.h MenuScene.cpp)
add_library(GameScene STATIC GameScene.h GameScene.cpp)
add_subdirectory(GameObject)

target_include_directories( MenuScene PUBLIC "../lib/SFML-2.6.1/include/" )
target_include_directories( GameScene PUBLIC "../lib/SFML-2.6.1/include/" )

target_link_libraries( MenuScene PUBLIC sfml-graphics sfml-window sfml-system sfml-audio )
target_link_libraries( GameScene PUBLIC sfml-graphics sfml-window sfml-system sfml-audio GameObject)
