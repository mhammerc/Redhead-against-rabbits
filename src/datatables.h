#ifndef DATATABLES_H
#define DATATABLES_H

#include "resourceidentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <functional>

class Aircraft;

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

struct AircraftData
{
    int hitpoints;
    float speed;
    Textures::ID texture;
    sf::Time fireInterval;
    std::vector<Direction> directions;
};

struct ProjectileData
{
    int damage;
    float speed;
    Textures::ID texture;
};

struct PickupData
{
    std::function<void(Aircraft&)> action;
    Textures::ID texture;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();

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
};

std::vector<LevelData> initializeLevelData();

#endif // DATATABLES_H

