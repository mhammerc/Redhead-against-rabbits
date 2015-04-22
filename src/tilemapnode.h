#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include "scenenode.h"
#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "datatables.h"

#include <iostream>
#include <vector>

class TileMapNode : public SceneNode
{
public:
    enum Type
    {
        Rabbits,
        TypeCount
    };

public:
    TileMapNode(const TextureHolder& textures);
    ~TileMapNode();

    void setTexture(const TextureHolder& textures);

    void completeLoad(Type type);
    void load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    bool checkCollisions(sf::FloatRect rect);

private:
    void addLayer(const int* layer);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const TextureHolder& mTextures;

    std::vector<sf::VertexArray> mVerticesArray;

    sf::Texture mTileset;

    sf::Vector2u mTileSize;
    unsigned int mWidth;
    unsigned int mHeight;

    const int* mCollisions;

     std::vector<LevelData> mData;

};

#endif // TILEMAP_H
