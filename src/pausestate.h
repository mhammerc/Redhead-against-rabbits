#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "engine/state.h"
#include "engine/gui/container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mBackgroundSprite;
    sf::Text mPausedText;
    GUI::Container mGUIContainer;
};

#endif // PAUSESTATE_H

