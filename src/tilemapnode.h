#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include "scenenode.h"
#include "resourceholder.h"
#include "resourceidentifiers.h"

class TileMapNode : public SceneNode
{
public:
    TileMapNode(const TextureHolder& textures);
    TileMapNode(const sf::Texture& texture);
    ~TileMapNode();

    void setTexture(const TextureHolder& textures);
    void load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    void addObjectsLayer(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::VertexArray mVertices;
    sf::Texture mTileset;

};

#endif // TILEMAP_H
