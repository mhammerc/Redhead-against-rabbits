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

Character::Character(Type type, const TextureHolder& textures, const FontHolder& fonts) :
    Entity(Table[type].hitpoints),
    mType(type),
    mSprite(textures.getConst(Table[type].texture)),
    mIsMarkedForRemoval(false)
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

void Character::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    Entity::updateCurrent(dt, commands);
}
