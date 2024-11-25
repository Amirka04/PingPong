#include <iostream>
#include <random>
#include <time.h>

#include "SFML/Graphics.hpp"
#include "MenuScene.h"
#include "GameScene.h"



int main(){
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong", sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("share/ping_pong_icon.png");  
    window.setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
    
    MenuScene menu(window.getSize());
    GameScene game(window.getSize());

    sf::Drawable* drawScene = &menu;


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Q)
                    window.close();
                if(event.key.code == sf::Keyboard::Space)
                    drawScene = &game;
        }

        window.clear(sf::Color::Black);

        if(drawScene == &game)
            game.update();

        window.draw(*drawScene);
        
        window.display();
    }
    

    return 0;
}
