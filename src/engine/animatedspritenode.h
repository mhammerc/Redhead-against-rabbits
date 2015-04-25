#ifndef ANIMATEDSPRITENODE_H
#define ANIMATEDSPRITENODE_H

#include "spritenode.h"
#include "animationtable.h"
#include "utility.h"

class AnimatedSpriteNode : public SpriteNode
{
public:
    explicit AnimatedSpriteNode(const sf::Texture& texture, Animation animationTable);

    void setState(int state);
    void nextTick(sf::Time dt);

    virtual sf::FloatRect getBoundingRect() const;

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    int mState;
    Animation mAnimationTable;
    sf::Time mElapsedTime;
};

#endif // ANIMATEDSPRITENODE_H
