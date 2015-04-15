#ifndef WORLD_H
#define WORLD_H

#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "scenenode.h"
#include "spritenode.h"
#include "aircraft.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>

// Forward declaration
namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Aircraft* mPlayerAircraft;
};

#endif // WORLD_H
