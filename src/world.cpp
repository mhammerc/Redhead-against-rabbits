#include "world.h"
#include "textnode.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

World::World(sf::RenderWindow& window, FontHolder& fonts) :
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mFonts(fonts),
    mTextures(),
    mSceneGraph(),
    mSceneLayers()
{
    loadTextures();
    buildScene();
}

void World::update(sf::Time dt)
{
    handleCollisions();

    // Remove all destroyed entities, create new ones
    mSceneGraph.removeWrecks();

    // Regular update step, adapt position (correct if outside view)
    mSceneGraph.update(dt, mCommandQueue);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::Tileset, "Media/Textures/tileset_light.png");
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type261 and second has type2
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
    /*std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for(SceneNode::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
        {
            auto& player = static_cast<Aircraft&>(*pair.first);
            auto& enemy = static_cast<Aircraft&>(*pair.second);

            // Collision: Player damage = enemy's remaining HP
            player.damage(enemy.getHitpoints());
            enemy.destroy();
        }

        else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
        {
            auto& player = static_cast<Aircraft&>(*pair.first);
            auto& pickup = static_cast<Pickup&>(*pair.second);

            // Apply pickup effect to player, destroy projectile
            pickup.apply(player);
            pickup.destroy();
        }

        else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
              || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
        {
            auto& aircraft = static_cast<Aircraft&>(*pair.first);
            auto& projectile = static_cast<Projectile&>(*pair.second);

            // Apply projectile damage to aircraft, destroy projectile
            aircraft.damage(projectile.getDamage());
            projectile.destroy();
        }
    }*/
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
    std::unique_ptr<TileMapNode> tileMap(new TileMapNode(mTextures));
    tileMap->setPosition(0, 0);
    tileMap->load(sf::Vector2u(32, 32), rabbits::map, 32, 18);
    tileMap->addObjectsLayer(sf::Vector2u(32, 32), rabbits::objects, 32, 18);
    mSceneLayers[Background]->attachChild(std::move(tileMap));
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
