#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"   // для музыки и музыкальных эффектов
#include "GameObject/GameObject.h"



class GameScene : public sf::Drawable
{

public:
    GameScene(sf::Vector2u viewport);

    void update();
    void reset();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::SoundBuffer sound_buffer;
    sf::Sound rebound_effect;

    sf::Vector2f velocity_ball; // скорость
    float acceleration; // ускорение после отскока
    GameObject background;
    GameObject ball;
    GameObject leftPlayer;
    GameObject rightPlayer;

    sf::Font font;
    sf::Text LeftPlayerScoreLabel;
    sf::Text RightPlayerScoreLabel;

    int LeftPlayerScore;
    int RightPlayerScore;

    sf::Vector2u viewport;
};


#endif
