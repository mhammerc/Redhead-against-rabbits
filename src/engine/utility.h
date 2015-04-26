#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

namespace sf
{
    class Sprite;
    class Text;
    class Shape;
}

std::string toString(sf::Keyboard::Key key);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);

float toDegree(float radian);
float toRadian(float degree);

int randomInt(int exclusiveMax);

float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

#endif
