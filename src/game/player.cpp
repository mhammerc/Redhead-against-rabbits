#include "player.h"
#include "engine/commandqueue.h"
#include "character.h"

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

struct PlayerMover
{
    PlayerMover(float vx, float vy) :
        velocity(vx, vy)
    {

    }

    void operator() (Character& player, sf::Time dt) const
    {
        if(player.isMoveAccepted(velocity, dt))
        {
            player.accelerate(velocity);
        }
    }

    sf::Vector2f velocity;
};

Player::Player()
{
    mKeyBinding[sf::Keyboard::Q] = MoveLeft;
    mKeyBinding[sf::Keyboard::D] = MoveRight;
    mKeyBinding[sf::Keyboard::Z] = MoveUp;
    mKeyBinding[sf::Keyboard::S] = MoveDown;

    initializeActions();

    for(auto& pair : mActionBinding)
    {
        pair.second.category = Category::PlayerCharacter;
    }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands)
{
    if(event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBinding.find(event.key.code);
        if(found != mKeyBinding.end() && !isRealtimeAction(found->second))
        {
            commands.push(mActionBinding[found->second]);
        }
    }
}

void Player::handleRealtimeInput(CommandQueue &commands)
{
    // Traverse all assigned keys and check if they are pressed
    for(auto pair : mKeyBinding)
    {
        if(sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
        {
            commands.push(mActionBinding[pair.second]);
        }
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    for(auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
    {
        if(itr->second == action)
        {
            mKeyBinding.erase(itr++);
        }
        else
        {
            ++itr;
        }
    }

    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for(auto pair : mKeyBinding)
    {
        if(pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
    mActionBinding[MoveLeft].action = derivedAction<Character>(PlayerMover(-150.f,  0.f));
    mActionBinding[MoveRight].action = derivedAction<Character>(PlayerMover(+150.f,  0.f));
    mActionBinding[MoveDown].action = derivedAction<Character>(PlayerMover(0.f, +150.f));
    mActionBinding[MoveUp].action = derivedAction<Character>(PlayerMover(0.f, -150.f));
}

bool Player::isRealtimeAction(Action action)
{
    switch(action)
    {
    case MoveLeft:
    case MoveRight:
    case MoveDown:
    case MoveUp:
        return true;
    default:
        return false;
    }
}
