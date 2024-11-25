#include <iostream>
#include <cmath>
#include <string>
#include <random>

#include "GameScene.h"


// проверка на столкновения, используется способ AABB обнаружения колизии
bool checkAABBCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
  // Получение глобальных позиций спрайтов
  sf::FloatRect rect1 = sprite1.getGlobalBounds();
  sf::FloatRect rect2 = sprite2.getGlobalBounds();

  // Проверка пересечения прямоугольников
  return rect1.intersects(rect2);
}


// функция нормализации вектора
sf::Vector2f normalize(const sf::Vector2f& vector) {
  float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
  if (length == 0) {
    return vector;
  }
  return sf::Vector2f(vector.x / length, vector.y / length);
}


inline int RandomValue(int start, int end){
    return start + (rand() % (start - end + 1));  
}


GameScene::GameScene(sf::Vector2u viewport)
: viewport(viewport)
{
    // инициализирую все необходимые компоненты для дальнейшей работы с ними
    LeftPlayerScore = 0;
    RightPlayerScore = 0;

    // загрузка шрифтов и фона
    if(!font.loadFromFile("share/fonts/MenuFont.ttf"))
        std::cerr << "GAMESCENE::GAMESCENE -> font file not found" << std::endl;
    
    background.loadTexture("share/textures/background_v2.png");
    background.setScale(0.5f, 5.0f);
    background.setPosition( static_cast<sf::Vector2f>( (viewport / 2u) ) - background.getSize() / 2.0f );

    // загрузка текстуры левого игрока
    leftPlayer.loadTexture("share/textures/LeftPlayerTexture.png");
    leftPlayer.setScale(0.6, 1);
    leftPlayer.setPosition( 0 + 10, viewport.x / 2 - leftPlayer.getSize().y );

    // загрузка текстуры правого игрока
    rightPlayer.loadTexture("share/textures/RightPlayerTexture.png");
    rightPlayer.setScale(0.6, 1);
    rightPlayer.setPosition( viewport.x - rightPlayer.getSize().x - 10, viewport.x / 2 - rightPlayer.getSize().y );
    
    // загрузка текстуры шарика
    ball.loadTexture("share/textures/Ball_v2.png");
    ball.setScale(0.7, 0.7);
    ball.setPosition( static_cast<sf::Vector2f>( (viewport / 2u) ) - ball.getSize() / 2.0f );
    velocity_ball = normalize(sf::Vector2f(cos(RandomValue(50, 290)), sin(RandomValue(50, 290)))) * 6.5f;
    acceleration = 1.01f;

    LeftPlayerScoreLabel.setFont(font);
    LeftPlayerScoreLabel.setCharacterSize(20);
    LeftPlayerScoreLabel.setPosition( sf::Vector2f{viewport.x / 4 - LeftPlayerScoreLabel.getGlobalBounds().getSize().x, 20} );
    LeftPlayerScoreLabel.setString(std::to_string(LeftPlayerScore));

    RightPlayerScoreLabel.setFont(font);
    RightPlayerScoreLabel.setCharacterSize(20);
    RightPlayerScoreLabel.setPosition( sf::Vector2f{ (viewport.x / 4 + viewport.x / 2) + RightPlayerScoreLabel.getGlobalBounds().getSize().x, 20} );
    RightPlayerScoreLabel.setString(std::to_string(RightPlayerScore));

    if(!sound_buffer.loadFromFile("share/sounds/rebound_ball.wav"))
        std::cerr << "Not found or load sound effect" << std::endl;
    rebound_effect.setBuffer(sound_buffer);
}



// вся игровая логика будет именно тут
void GameScene::update(){
    
    // движение игроков
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPlayer.getPosition().y > 0)
        leftPlayer.move(0.0f, -5.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPlayer.getPosition().y + leftPlayer.getSize().y < viewport.y)
        leftPlayer.move(0.0f, 5.0f);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPlayer.getPosition().y > 0)
        rightPlayer.move(0.0f, -5.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPlayer.getPosition().y + rightPlayer.getSize().y < viewport.y)
        rightPlayer.move(0.0f, 5.0f);

    
    ball.move(velocity_ball);
    // проверка на столкновение об игрока и верхнюю и нижнюю границу экрана
    if( (ball.getPosition().y < 0 || ball.getPosition().y + ball.getSize().y > viewport.y) ){
        velocity_ball.y *= -1;
        rebound_effect.play();  // воспроизвеление звукового эффекта после удара об игрока
    }
    if( checkAABBCollision(leftPlayer, ball) || checkAABBCollision(rightPlayer, ball) ){
        velocity_ball.x *= -1;
        velocity_ball *= acceleration;  // ускорение мяча после удара
        rebound_effect.play();  // воспроизвеление звукового эффекта после удара об игрока
    }
    
    // проверка на выход за границу по оси X, в зависимости от стороны границы, мы икрементируем счётчик икроку на противоположной стороне
    if(ball.getPosition().x <= 0){
        RightPlayerScore += 1;
        RightPlayerScoreLabel.setString(std::to_string(RightPlayerScore));
        reset();
    }
    if(ball.getPosition().x + ball.getSize().x >= viewport.x){
        LeftPlayerScore += 1;
        LeftPlayerScoreLabel.setString(std::to_string(LeftPlayerScore));
        reset();
    }
    
}


// возвращение элементов на начальные позиции
void GameScene::reset(){
    rightPlayer.setPosition( viewport.x - rightPlayer.getSize().x - 10, viewport.x / 2 - rightPlayer.getSize().y );
    leftPlayer.setPosition( 0 + 10, viewport.x / 2 - leftPlayer.getSize().y );
    ball.setPosition( static_cast<sf::Vector2f>( (viewport / 2u) ) - ball.getSize() / 2.0f );
    velocity_ball = normalize( sf::Vector2f(cos(RandomValue(50, 290)), sin(RandomValue(50, 290))) ) * 6.5f;
}



// рисование сцены
void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(leftPlayer, states);
    target.draw(rightPlayer, states);
    target.draw(LeftPlayerScoreLabel, states);
    target.draw(RightPlayerScoreLabel, states);
    target.draw(ball, states);
}
