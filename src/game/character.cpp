#include "character.h"

#include "engine/utility.h"
#include "datatables.h"
#include "engine/commandqueue.h"
#include "engine/resourceholder.h"

#include <cmath>

namespace
{
    const std::vector<CharacterData> Table = initializeCharacterData();
}

Character::Character(Type type, const TextureHolder& textures, const FontHolder& fonts, TileMapNode* tileMap) :
    Entity(Table[type].hitpoints),
    mType(type),
    mSprite(textures.getConst(Table[type].texture), initializeAnimationData(Table[type].texture)),
    mIsMarkedForRemoval(false),
    mPathData(initializePathData()),
    mPreviousPosition(0, 0),
    mTileMap(tileMap)
{
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

sf::FloatRect Character::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getBoundingRect());
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

    sf::FloatRect rect;
    rect.left = position.x - getBoundingRect().width / 2;
    rect.top = position.y - getBoundingRect().height / 2;
    rect.width = getBoundingRect().width;
    rect.height = getBoundingRect().height;

    if(mTileMap->checkCollisions(rect))
    {
        return false;
    }

    return true;
}

void Character::backToPreviousPosition()
{
    setPosition(mPreviousPosition);
}

void Character::pausePath()
{
    mIsPathPaused = true;
}

void Character::unpausePath()
{
    mIsPathPaused = false;
}

void Character::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isNeutral() && !mIsPathPaused)
    {
        nextPathTick(dt, PathType::HorizontalShortBackAndForth);
    }

    if(mIsPathPaused)
    {
        unpausePath();
    }

    if(getVelocity().x == 0 && getVelocity().y == 0)
    {
        mSprite.setState(PlayerAnimations::Idle);
    }
    else if(!(getVelocity().x == 0) || !(getVelocity().y == 0))
    {
        mSprite.setState(PlayerAnimations::Walk);

        if(getVelocity().x > 0)
        {
            mSprite.setScale(1, 1);
        }
        else if(getVelocity().x < 0)
        {
            mSprite.setScale(-1, 1);
        }
    }

    mSprite.nextTick(dt);

    mPreviousPosition = this->getPosition();

    Entity::updateCurrent(dt, commands);

    setVelocity(0, 0);
}

void Character::nextPathTick(sf::Time dt, PathType pathType)
{
    mElapsedTimePath += dt;

    if(mElapsedTimePath.asMilliseconds() > mPathData[pathType].totalDuration)
    {
        mElapsedTimePath -= sf::milliseconds(mPathData[pathType].totalDuration);
    }

    int x = 0;

    for(; mPathData[pathType].path.size() > x && mElapsedTimePath.asMilliseconds() > mPathData[pathType].path[x].totalDuration; ++x);

    sf::Vector2f pathVector = mPathData[pathType].path[x].vector;
    unsigned int pathDuration = mPathData[pathType].path[x].duration;

    sf::Vector2f vector;
    vector.x = pathVector.x / pathDuration * dt.asMilliseconds();
    vector.y = pathVector.y / pathDuration * dt.asMilliseconds();

    setVelocity(vector);
}
