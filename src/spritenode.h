#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SFML/Graphics.hpp>

#include "scenenode.h"

class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture &texture, const sf::IntRect& textureRect);

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    sf::Sprite mSprite;
};

#endif // SPRITENODE_H
