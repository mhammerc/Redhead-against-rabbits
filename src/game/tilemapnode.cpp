#include "tilemapnode.h"

TileMapNode::TileMapNode(const TextureHolder& textures, const FontHolder &fonts) :
    mTextures(textures),
    mFonts(fonts)
{

}

TileMapNode::~TileMapNode()
{

}

void TileMapNode::setTexture(const TextureHolder &textures)
{
    mTileset = textures.getConst(Textures::Tileset);
}

void TileMapNode::completeLoad(Type type)
{
    mData = initializeLevelData();

    mTileset = mTextures.getConst(mData[type].texture);

    mTileSize = mData[type].tileSize;
    mMapSize.x = (uint)mData[type].levelSize.x;
    mMapSize.y = (uint)mData[type].levelSize.y;

    mCollisions = mData[type].collisions;

    addLayer(mData[type].firstLayer);
    addLayer(mData[type].secondLayer);

    for(std::function<void(TileMapNode*, const TextureHolder&, const FontHolder&)> element : mData[type].elements)
    {
        element(this, mTextures, mFonts);
    }
}

void TileMapNode::addLayer(const int* layer)
{
    sf::VertexArray vertexArray;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(mMapSize.x * mMapSize.y * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < mMapSize.x; ++i)
    {
        for (unsigned int j = 0; j < mMapSize.y; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = layer[i + j * mMapSize.x];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (mTileset.getSize().x / mTileSize.x);
            int tv = tileNumber / (mTileset.getSize().x / mTileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &vertexArray[(i + j * mMapSize.x) * 4];

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
    unsigned int verticeCount = mMapSize.x * mMapSize.y * 4;

    for(unsigned int i = 0; i * 4 < verticeCount; ++i)
    {
        if(mCollisions[i] == 0)
        {
            continue;
        }

        int y = 0;

        for(unsigned int j = i; j >= mMapSize.x; y += 1, j -= mMapSize.x);

        y *= mTileSize.y;

        sf::Vector2i tilePosition;
        tilePosition.y = y;
        tilePosition.x = (i % mMapSize.x) * mTileSize.x;

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



