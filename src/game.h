#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "resourceholder.h"


namespace Textures
{
    enum ID
    {
        Landscape,
        Airplaine
    };
}

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update(sf::Time elapsedTime);
    void render();

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    static const float PlayerSpeed;
    static const sf::Time TimePerFrame;

    ResourceHolder<sf::Texture, Textures::ID> textures;

    sf::RenderWindow mWindow;
    sf::Sprite mPlayer;
    sf::Sprite mLandscape;
    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;

    std::size_t mStatisticsNumFrames;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingRight;
    bool mIsMovingLeft;
};

#endif // GAME_H
