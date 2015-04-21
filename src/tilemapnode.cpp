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

void TileMapNode::completeLoad(sf::Vector2u tileSize, const int *tiles, const int *objects, const int *collisions, unsigned int width, unsigned int height)
{
    load(tileSize, tiles, width, height);

    addObjectsLayer(tileSize, objects, width, height);

    mCollisions = collisions;
}

void TileMapNode::load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    mTileSize = tileSize;
    mWidth = width;
    mHeight = height;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * width];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (mTileset.getSize().x / tileSize.x);
            int tv = tileNumber / (mTileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &mVertices[(i + j * width) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
}

bool TileMapNode::checkCollisions(sf::FloatRect rect)
{
    for(unsigned int i = 0; i * 4 < mVertices.getVertexCount(); ++i)
    {
        if(mCollisions[i] == 0)
        {
            continue;
        }

        int y = 0;

        for(int j = i; j >= mWidth; y += 1, j -= mWidth);

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

void TileMapNode::addObjectsLayer(sf::Vector2u tileSize, const int *tiles, unsigned int width, unsigned int height)
{
    std::unique_ptr<TileMapNode> objects(new TileMapNode(mTileset));
    objects->setPosition(0, 0);
    objects->load(tileSize, tiles, width, height);
    attachChild(std::move(objects));
}

void TileMapNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //states.transform *= getTransform();

    states.texture = &mTileset;

    target.draw(mVertices, states);
}



