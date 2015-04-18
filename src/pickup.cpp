#include "pickup.h"
#include "datatables.h"
#include "category.h"
#include "commandqueue.h"
#include "utility.h"
#include "resourceholder.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
    const std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textures) :
    Entity(1),
    mType(type),
    mSprite(textures.getConst(Table[type].texture))
{
    centerOrigin(mSprite);
}

unsigned int Pickup::getCategory() const
{
    return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::apply(Aircraft& player) const
{
    Table[mType].action(player);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
