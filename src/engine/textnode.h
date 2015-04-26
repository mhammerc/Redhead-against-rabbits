#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "scenenode.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class TextNode : public SceneNode
{
public:
    explicit TextNode(const FontHolder& fonts, const std::string& text, unsigned int size = 20);

    void setString(const std::string& text);

protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Text mText;
};

#endif // TEXTNODE_H

