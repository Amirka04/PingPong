add_library(GameObject STATIC GameObject.h GameObject.cpp)


target_include_directories( GameObject PUBLIC "../../lib/SFML-2.6.1/include/" )

target_link_libraries( GameObject PUBLIC sfml-graphics sfml-window sfml-system )