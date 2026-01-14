#pragma once

#include <SFML/Graphics.hpp>

enum class MenuResult
{
    None,
    Play,
    Player,
    Settings,
    Exit
};

class Menu
{
public:
    Menu(sf::Font& font);

    void moveUp();
    void moveDown();
    void confirm();

    void draw(sf::RenderWindow& window);

    MenuResult getResult() const;
    void resetResult();

private:
    void updateColors();

    enum Item { PLAY, PLAYER, SETTINGS, EXIT, COUNT };

    Item selected = PLAY;
    MenuResult result = MenuResult::None;

    sf::Text title;
    sf::Text items[COUNT];
};