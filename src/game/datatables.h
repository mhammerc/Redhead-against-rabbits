#ifndef DATATABLES_H
#define DATATABLES_H

#include "resourceidentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <functional>
#include <memory>

class TileMapNode;

struct Direction
{
    Direction(float angle, float distance) :
        angle(angle),
        distance(distance)
    {

    }

    float angle;
    float distance;
};


struct CharacterData
{
    int hitpoints;
    float speed;
    Textures::ID texture;
};

std::vector<CharacterData> initializeCharacterData();

struct LevelData
{
    int* firstLayer;
    int* secondLayer;
    int* collisions;
    sf::Vector2u tileSize;
    sf::Vector2f levelSize;
    Textures::ID texture;
    std::vector<std::function<void(TileMapNode*, const TextureHolder&, const FontHolder&)>> elements;
};

std::vector<LevelData> initializeLevelData();

#endif // DATATABLES_H

