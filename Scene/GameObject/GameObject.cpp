#include "GameObject.h"

#include <iostream>


GameObject::GameObject(sf::String texture_path)
{
    loadTexture(texture_path);
}


void GameObject::loadTexture(sf::String texture_path){
    if( !texture.loadFromFile(texture_path) )
        std::cerr << "GameObject error in constructor -> not found file\"" << texture_path.toAnsiString() << "\"";
    this->setTexture(texture);
}


sf::Vector2f GameObject::getSize(){
    return this->getGlobalBounds().getSize();
}
