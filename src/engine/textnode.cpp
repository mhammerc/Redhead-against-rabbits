#include "textnode.h"
#include "utility.h"

#include <SFML/Graphics/RenderTarget.hpp>

TextNode::TextNode(const FontHolder& fonts, const std::string& text, unsigned int size)
{
    mText.setFont(fonts.getConst(Fonts::Main));
    mText.setCharacterSize(size);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}
