#ifndef SPEAKINGBUBBLENODE_H
#define SPEAKINGBUBBLENODE_H

#include "textnode.h"

#include "utility.h"

class SpeakingBubbleNode : public TextNode
{
public:
    explicit SpeakingBubbleNode(std::string& text, const TextureHolder& texture, const FontHolder& fonts);

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::RectangleShape mBackground;
};

#endif // SPEAKINGBUBBLENODE_H
