#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include "scenenode.h"
#include "resourceholder.h"
#include "resourceidentifiers.h"

#include <iostream>

class TileMapNode : public SceneNode
{
public:
    TileMapNode(const TextureHolder& textures);
    TileMapNode(const sf::Texture& texture);
    ~TileMapNode();

    void setTexture(const TextureHolder& textures);

    void completeLoad(sf::Vector2u tileSize, const int* tiles, const int* objects, const int* collisions, unsigned int width, unsigned int height);
    void load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    bool checkCollisions(sf::FloatRect rect);

private:
    void addObjectsLayer(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::VertexArray mVertices;
    sf::Texture mTileset;

    sf::Vector2u mTileSize;
    unsigned int mWidth;
    unsigned int mHeight;

    const int* mCollisions;

};

#endif // TILEMAP_H
