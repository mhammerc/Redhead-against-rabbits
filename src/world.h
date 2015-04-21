#ifndef WORLD_H
#define WORLD_H

#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "scenenode.h"
#include "spritenode.h"
#include "commandqueue.h"
#include "command.h"
#include "tilemapnode.h"

#include "rabbits_level.h"
#include "player.h"
#include "character.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <queue>

// Forward declaration
namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window, FontHolder& fonts);
    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event& event);

    CommandQueue& getCommandQueue();

private:
    void loadTextures();

    void handleCollisions();

    void buildScene();

    sf::FloatRect getViewBounds() const;

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
    FontHolder& mFonts;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    Player mPlayer;
    Character* mPlayerCharacter;

    TileMapNode* mTileMap;
};

#endif // WORLD_H
