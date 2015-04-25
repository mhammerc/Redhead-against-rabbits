#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "engine/state.h"
#include "player.h"
#include "engine/gui/container.h"
#include "engine/gui/button.h"
#include "engine/gui/label.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

class SettingsState : public State
{
public:
    SettingsState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    void updateLabels();
    void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

private:
    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;
    std::array<GUI::Button::Ptr, Player::ActionCount> mBindingButtons;
    std::array<GUI::Label::Ptr, Player::ActionCount> mBindingLabels;
};

#endif // SETTINGSSTATE_H

