#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "state.h"
#include "container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <memory>

class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;
};

#endif // MENUSTATE_H

