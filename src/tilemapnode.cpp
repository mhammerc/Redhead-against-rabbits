#include "tilemapnode.h"

TileMapNode::TileMapNode(const TextureHolder& textures) :
    mTileset(textures.getConst(Textures::Tileset))
{

}

TileMapNode::TileMapNode(const sf::Texture &texture) :
    mTileset(texture)
{

}

TileMapNode::~TileMapNode()
{

}

void TileMapNode::setTexture(const TextureHolder &textures)
{
    mTileset = textures.getConst(Textures::Tileset);
}

void TileMapNode::completeLoad(sf::Vector2u tileSize, const int* firstLayer, const int* secondLayer, const int *collisions, unsigned int width, unsigned int height)
{
    mTileSize = tileSize;
    mWidth = width;
    mHeight = height;
    mCollisions = collisions;

    addLayer(firstLayer);
    addLayer(secondLayer);
}

void TileMapNode::addLayer(const int* layer)
{
    sf::VertexArray vertexArray;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(mWidth * mHeight * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < mWidth; ++i)
    {
        for (unsigned int j = 0; j < mHeight; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = layer[i + j * mWidth];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (mTileset.getSize().x / mTileSize.x);
            int tv = tileNumber / (mTileset.getSize().x / mTileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &vertexArray[(i + j * mWidth) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * mTileSize.x, j * mTileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * mTileSize.x, j * mTileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * mTileSize.x, (j + 1) * mTileSize.y);
            quad[3].position = sf::Vector2f(i * mTileSize.x, (j + 1) * mTileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * mTileSize.x, tv * mTileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * mTileSize.x, tv * mTileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * mTileSize.x, (tv + 1) * mTileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * mTileSize.x, (tv + 1) * mTileSize.y);
        }
    }

    mVerticesArray.push_back(vertexArray);
}

bool TileMapNode::checkCollisions(sf::FloatRect rect)
{
    unsigned int verticeCount = mWidth * mHeight * 4;

    for(unsigned int i = 0; i * 4 < verticeCount; ++i)
    {
        if(mCollisions[i] == 0)
        {
            continue;
        }

        int y = 0;

        for(unsigned int j = i; j >= mWidth; y += 1, j -= mWidth);

        y *= mTileSize.y;

        sf::Vector2i tilePosition;
        tilePosition.y = y;
        tilePosition.x = (i % mWidth) * mTileSize.x;

        sf::FloatRect tile(sf::Vector2f(tilePosition.x, tilePosition.y), sf::Vector2f(mTileSize.x, mTileSize.y));

        if(tile.intersects(rect))
        {
            return true;
        }
    }

    return false;
}

void TileMapNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = &mTileset;

    for(sf::VertexArray vertex : mVerticesArray)
    {
        target.draw(vertex, states);
    }
}



