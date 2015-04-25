#ifndef PATHTABLE_H
#define PATHTABLE_H

#include <vector>

#include <SFML/System/Vector2.hpp>

enum PathType
{
    HorizontalShortBackAndForth,
    TypeCount
};

struct PathSegment
{
    sf::Vector2f vector;
    unsigned int duration;
    unsigned int totalDuration;
};

struct Path
{
    std::vector<PathSegment> path;
    unsigned int totalDuration;
};

const std::vector<Path> initializePathData();

#endif // PATHTABLE_H

