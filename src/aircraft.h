#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "resourceidentifiers.h"

class Aircraft : public Entity
{
public:
    enum Type
    {
        Eagle,
        Raptor
    };

public:
    Aircraft(Type type, TextureHolder& textures);

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    Type mType;
    sf::Sprite mSprite;
};

#endif // AIRCRAFT_H
