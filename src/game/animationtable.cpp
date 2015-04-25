#include "animationtable.h"

Animation initializeAnimationData(Textures::ID texture)
{
    if(texture == Textures::PlayerCharacter)
    {
        Animation a;
        a.interval = 200u;
        a.textureRect[Idle].push_back(sf::IntRect(3, 18, 34, 58));

        a.textureRect[Walk].push_back(sf::IntRect(0, 77, 34, 58));
        a.textureRect[Walk].push_back(sf::IntRect(34, 77, 34, 58));
        a.textureRect[Walk].push_back(sf::IntRect(72, 77, 34, 58));
        a.textureRect[Walk].push_back(sf::IntRect(110, 77, 34, 58));
        a.textureRect[Walk].push_back(sf::IntRect(143, 77, 34, 58));
        a.textureRect[Walk].push_back(sf::IntRect(177, 77, 34, 58));

        return a;
    }

    else if(texture == Textures::NeutralCharacter)
    {
        Animation a;
        a.interval = 500u;
        a.textureRect[Idle].push_back(sf::IntRect(0, 0, 32, 32));

        a.textureRect[Walk].push_back(sf::IntRect(0, 0, 32, 32));
        a.textureRect[Walk].push_back(sf::IntRect(128, 0, 32, 32));

        return a;
    }
}
