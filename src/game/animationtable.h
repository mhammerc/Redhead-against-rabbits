#ifndef ANIMATIONTABLE_H
#define ANIMATIONTABLE_H

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <map>

#include "resourceidentifiers.h"

enum CharacterAnimations
{
    Idle = 0,
    Walk,
    WalkingUp,
    WalkingDown,
    WalkingRight,
    WalkingLeft
};

struct Animation
{
    Animation(std::map<int, std::vector<sf::IntRect>> textureRect, unsigned int interval) :
        textureRect(textureRect),
        interval(interval)
    {

    }

    Animation()
    {

    }

    std::map<int, std::vector<sf::IntRect>> textureRect;
    unsigned int interval;
};

Animation initializeAnimationData(Textures::ID texture);


#endif // ANIMATIONTABLE_H

