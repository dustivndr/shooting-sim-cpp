#pragma once

#include "MenuView.hpp"

enum class SettingsMenuResult
{
    None,
    Windowed,
    Fullscreen,
    Borderless,
    Back
};

class SettingsMenu
{
public:

    SettingsMenu(sf::Font& font);

    void moveUp();
    void moveDown();
    void confirm();

    SettingsMenuResult getResult() const;
    void resetResult();

    void draw(sf::RenderWindow& window);

    void updateLayout(const sf::View& view_);

private:
    MenuView view;
    int selected = 0;
    SettingsMenuResult result = SettingsMenuResult::None;
};
