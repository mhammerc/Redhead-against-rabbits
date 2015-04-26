#include "speakingbubblenode.h"

SpeakingBubbleNode::SpeakingBubbleNode(std::string &text, const TextureHolder &texture, const FontHolder &fonts) :
    TextNode(fonts, text, 10),
    mBackground(sf::Vector2f(50, 15))
{
    mBackground.setFillColor(sf::Color::Black);
    centerOrigin(mBackground);
}

void SpeakingBubbleNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
    TextNode::drawCurrent(target, states);
}

