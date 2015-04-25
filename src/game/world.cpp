#include "world.h"
#include "engine/textnode.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

World::World(sf::RenderWindow& window, FontHolder& fonts) :
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mTextures(),
    mFonts(fonts),
    mSceneGraph(),
    mSceneLayers()
{
    loadTextures();
    buildScene();
}

void World::update(sf::Time dt)
{
    handleCollisions();
    
    mPlayer.handleRealtimeInput(mCommandQueue);

    mPlayerCharacter->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty())
            mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    // Remove all destroyed entities, create new ones
    mSceneGraph.removeWrecks();

    // Regular update step, adapt position (correct if outside view)
    mSceneGraph.update(dt, mCommandQueue);

    // Center view on Player
    mWorldView.setCenter(mPlayerCharacter->getPosition());
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::handleEvent(const sf::Event &event)
{
    mPlayer.handleEvent(event, mCommandQueue);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::Tileset, "Media/Textures/tileset_light.png");
    mTextures.load(Textures::PlayerCharacter, "Media/Textures/Buster.png");
    mTextures.load(Textures::NeutralCharacter, "Media/Textures/npc.png");
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for(SceneNode::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::PlayerCharacter, Category::NeutralCharacter))
        {
            auto& player = static_cast<Character&>(*pair.first);
            auto& npc = static_cast<Character&>(*pair.second);

            // Collision: freeze the npc
            npc.pausePath();
        }
    }
}

void World::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;

        SceneNode::Ptr layer(new SceneNode(category));
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Add the tile map
    std::unique_ptr<TileMapNode> tileMap(new TileMapNode(mTextures, mFonts));
    mTileMap = tileMap.get();
    mTileMap->setPosition(0, 0);
    mTileMap->completeLoad(TileMapNode::Rabbits);
    mSceneLayers[Air]->attachChild(std::move(tileMap));

    // Add the player
    std::unique_ptr<Character> player(new Character(Character::Player, mTextures, mFonts, mTileMap));
    mPlayerCharacter = player.get();
    mPlayerCharacter->scale(0.8, 0.8);
    mPlayerCharacter->setPosition(64, 64);
    mTileMap->attachChild(std::move(player));

    // Set the view
    mWorldView.zoom(0.6);
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
