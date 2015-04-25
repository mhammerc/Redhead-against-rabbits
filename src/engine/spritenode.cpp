#include "spritenode.h"

SpriteNode::SpriteNode(const sf::Texture &texture) :
    mTexture(texture),
    mSprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) :
    mTexture(texture),
    mSprite(texture, textureRect)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mSprite, states);
}
