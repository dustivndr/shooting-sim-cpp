#pragma once

#include "MenuView.hpp"

enum class MainMenuResult
{
    None,
    Play,
    Player,
    Settings,
    Exit
};

class MainMenu
{
public:
    MainMenu(sf::Font& font);

    void moveUp();
    void moveDown();
    void confirm();

    MainMenuResult getResult() const;
    void resetResult();

    void updateLayout(const sf::View& view);
    void draw(sf::RenderWindow& window);

private:
    MenuView view;
    int selected = 0;
    MainMenuResult result = MainMenuResult::None;
};
