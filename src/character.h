#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"
#include "resourceidentifiers.h"
#include "command.h"
#include "commandqueue.h"

#include <SFML/Graphics.hpp>

#include <string>


class Character : public Entity
{
public:
    enum Type
    {
        Player,
        Allied,
        Neutral,
        Enemy,
        TypeCount
    };

public:
    Character(Type type, const TextureHolder& textures, const FontHolder& fonts);

    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect();
    virtual bool isMarkedForRemoval() const;

    bool isAllied() const;
    bool isEnemy() const;
    bool isNeutral() const;
    bool isPlayer() const;

    float getMaxSpeed() const;

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
    Type mType;
    sf::Sprite mSprite;
    bool mIsMarkedForRemoval;
};

#endif // CHARACTER_H
