#include "entity.h"

#include <cassert>


Entity::Entity(int hitpoints) :
    mVelocity(),
    mHitpoints(hitpoints),
    isMoveRefused(false),
    isDenyingNextMove(false)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}

void Entity::repair(int points)
{
    assert(points > 0);

    mHitpoints += points;
}

void Entity::damage(int points)
{
    assert(points > 0);

    mHitpoints -= points;
}

void Entity::destroy()
{
    mHitpoints = 0;
}

bool Entity::isDestroyed() const
{
    return mHitpoints <= 0;
}

void Entity::agreeMove()
{
    isMoveRefused = false;
}

void Entity::denyMove()
{
    isMoveRefused = true;
}

void Entity::denyNextMove()
{
    isMoveRefused = true;
    isDenyingNextMove = true;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
    if(!isMoveRefused)
        move(mVelocity * dt.asSeconds());

    if(isDenyingNextMove)
    {
        isMoveRefused = false;
        isDenyingNextMove = false;
    }
}


