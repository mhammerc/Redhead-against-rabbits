#include "animatedspritenode.h"

AnimatedSpriteNode::AnimatedSpriteNode(const sf::Texture &texture, Animation animationTable) :
    SpriteNode(texture),
    mState(0),
    mAnimationTable(animationTable)
{
}

void AnimatedSpriteNode::setState(int state)
{
    mState = state;
}

void AnimatedSpriteNode::nextTick(sf::Time dt)
{
    mElapsedTime += dt;

    short numberOfTextures = mAnimationTable.textureRect[mState].size();

    int interval = mAnimationTable.interval;

    int x = mElapsedTime.asMilliseconds() / interval % numberOfTextures;

    mSprite.setTextureRect(mAnimationTable.textureRect[mState][x]);

    centerOrigin(mSprite);
}

sf::FloatRect AnimatedSpriteNode::getBoundingRect() const
{
    return mSprite.getLocalBounds();
}

void AnimatedSpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


