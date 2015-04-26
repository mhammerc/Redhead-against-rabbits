#ifndef CHARACTER_H
#define CHARACTER_H

#include "engine/entity.h"
#include "resourceidentifiers.h"
#include "engine/command.h"
#include "engine/commandqueue.h"

#include "tilemapnode.h"
#include "engine/animatedspritenode.h"

#include "animationtable.h"
#include "pathtable.h"

#include "engine/speakingbubblenode.h"

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
    virtual sf::FloatRect getBoundingRect() const;
    virtual bool isMarkedForRemoval() const;

    bool isAllied() const;
    bool isEnemy() const;
    bool isNeutral() const;
    bool isPlayer() const;

    float getMaxSpeed() const;

    bool isMoveAccepted(sf::Vector2f velocity, sf::Time dt);

    void backToPreviousPosition();

    void pausePath();
    void unpausePath();

    void speak(std::string& text, sf::Time countdown);

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    void selectAppropriateAnimation();

    void nextPathTick(sf::Time dt, PathType pathType);

    void verifySpeakingBubble(sf::Time dt);

private:
    const TextureHolder& mTextures;
    const FontHolder& mFonts;

    Type mType;
    AnimatedSpriteNode mSprite;
    bool mIsMarkedForRemoval;

    const std::vector<Path> mPathData;
    sf::Time mElapsedTimePath;
    bool mIsPathPaused;

    sf::Vector2f mPreviousPosition;

    TileMapNode* mTileMap;

    SpeakingBubbleNode* mSpeakingNode;
    sf::Time mSpeakingCountdown;
};

#endif // CHARACTER_H
