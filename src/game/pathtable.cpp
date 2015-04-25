#include "pathtable.h"

const std::vector<Path> initializePathData()
{
    std::vector<Path> pathList(TypeCount);

    PathSegment first;
    first.duration = 1500u;
    first.totalDuration = 1500u;
    first.vector = sf::Vector2f(3000, 0);

    PathSegment second;
    second.duration = first.duration;
    second.totalDuration = first.duration + second.duration;
    second.vector = -first.vector;

    pathList[HorizontalShortBackAndForth].path.push_back(first);
    pathList[HorizontalShortBackAndForth].path.push_back(second);

    pathList[HorizontalShortBackAndForth].totalDuration = 3000u;

    return pathList;
}
