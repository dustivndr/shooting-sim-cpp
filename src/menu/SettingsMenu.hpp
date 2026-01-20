#pragma once

#include <SFML/Graphics.hpp>

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
    static constexpr int ITEM_COUNT = 4;

    SettingsMenu(sf::Font& font);

    void moveUp();
    void moveDown();
    void confirm();

    SettingsMenuResult getResult() const;
    void resetResult();

    void draw(sf::RenderWindow& window);

private:
    void updateColors();

private:
    sf::Text title;
    sf::Text items[ITEM_COUNT];

    int selected = 0;
    SettingsMenuResult result = SettingsMenuResult::None;
};
