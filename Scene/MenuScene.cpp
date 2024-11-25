#include <iostream>

#include "MenuScene.h"



MenuScene::MenuScene(sf::Vector2u viewport)
: viewport(viewport)
{
    if(!font.loadFromFile("share/fonts/pixpopenei.ttf"))
        std::cerr << "MENUSCENE::MENUSCENE -> error: ttf file not found" << std::endl;
    text.setFont(font);
    text.setCharacterSize(25);
    text.setString(sf::String("Click on the SPACE to play\nQ - quit\nLeft player - W/S\nRight player - arrow up/down"));
    text.setPosition( static_cast<sf::Vector2f>( (viewport / 2u) ) - text.getGlobalBounds().getSize() / 2.0f );
}



void MenuScene::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(text, state);
}
