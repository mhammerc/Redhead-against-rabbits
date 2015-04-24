#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"
#include "resourceidentifiers.h"
#include "command.h"
#include "commandqueue.h"

#include "tilemapnode.h"
#include "animatedspritenode.h"
#include "animationtable.h"

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
    Character(Type type, const TextureHolder& textures, const FontHolder& fonts, TileMapNode* tileMap);

    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect();
    virtual bool isMarkedForRemoval() const;

    bool isAllied() const;
    bool isEnemy() const;
    bool isNeutral() const;
    bool isPlayer() const;

    float getMaxSpeed() const;

    bool isMoveAccepted(sf::Vector2f velocity, sf::Time dt);

    void backToPreviousPosition();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
    Type mType;
    AnimatedSpriteNode mSprite;
    bool mIsMarkedForRemoval;

    sf::Vector2f mPreviousPosition;

    TileMapNode* mTileMap;
};

#endif // CHARACTER_H
