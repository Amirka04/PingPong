#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "SFML/Graphics.hpp"



class MenuScene : public sf::Drawable
{
public:
    MenuScene(sf::Vector2u viewport);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Font font;  // font - будет хранить в себе информацию о ttf файле
    sf::Text text;  // text - отображаемый текст
    sf::Vector2u viewport; // отображаемая область, что б можно было расположить фигуру по середине и не только
};



#endif
