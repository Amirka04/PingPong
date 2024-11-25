#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/Graphics.hpp"


class GameObject : public sf::Sprite
{
public:
    GameObject() = default;
    GameObject(sf::String texture_path);
    void loadTexture(sf::String texture_path);
    sf::Vector2f getSize(); // для удобного получения размера
private:
    sf::Texture texture;    // текстура
};

#endif
