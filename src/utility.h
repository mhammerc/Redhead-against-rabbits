#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace sf
{
    class Sprite;
    class Text;
}

std::string toString(sf::Keyboard::Key key);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#endif
