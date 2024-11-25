cmake_minimum_required(VERSION 3.5)

project(PingPong-v2)


set(BUILD_SHARED_LIBS OFF)
add_subdirectory(lib/SFML-2.6.1)

add_subdirectory(Scene)

add_executable(PingPong main.cpp)

target_include_directories(PingPong PUBLIC "lib/SFML-2.6.1/include/" "Scene/")

link_libraries(sfml-graphics sfml-window sfml-system)

target_link_libraries(PingPong PUBLIC MenuScene GameScene)
