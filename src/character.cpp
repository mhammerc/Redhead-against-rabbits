#include "character.h"

#include "utility.h"
#include "datatables.h"
#include "commandqueue.h"
#include "resourceholder.h"

#include <cmath>

namespace
{
    const std::vector<CharacterData> Table = initializeCharacterData();
}

Character::Character(Type type, const TextureHolder& textures, const FontHolder& fonts, TileMapNode* tileMap) :
    Entity(Table[type].hitpoints),
    mType(type),
    mSprite(textures.getConst(Table[type].texture)),
    mIsMarkedForRemoval(false),
    mPreviousPosition(0, 0),
    mTileMap(tileMap)
{
   centerOrigin(mSprite);
}

unsigned int Character::getCategory() const
{
    if(isAllied())
        return Category::AlliedCharacter;
    else if(isEnemy())
        return Category::EnemyCharacter;
    else if(isNeutral())
        return Category::NeutralCharacter;
    else
        return Category::PlayerCharacter;
}

sf::FloatRect Character::getBoundingRect()
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Character::isMarkedForRemoval() const
{
    return mIsMarkedForRemoval;
}

bool Character::isAllied() const
{
    return mType == Allied;
}

bool Character::isEnemy() const
{
    return mType == Enemy;
}

bool Character::isNeutral() const
{
    return mType == Neutral;
}

bool Character::isPlayer() const
{
    return mType == Player;
}

float Character::getMaxSpeed() const
{
    return Table[mType].speed;
}

bool Character::isMoveAccepted(sf::Vector2f velocity, sf::Time dt)
{
    sf::Vector2f position = getPosition();
    position.x += velocity.x * dt.asSeconds();
    position.y += velocity.y * dt.asSeconds();

    if(mTileMap->checkCollisions(sf::FloatRect(sf::Vector2f(position.x-getBoundingRect().width/2, position.y-getBoundingRect().height/2), sf::Vector2f(getBoundingRect().width, getBoundingRect().height))))
    {
        return false;
    }

    return true;
}

void Character::backToPreviousPosition()
{
    setPosition(mPreviousPosition);
}

void Character::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    mPreviousPosition = this->getPosition();

    Entity::updateCurrent(dt, commands);
}
