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

    void handleEvent(const sf::Event& event);
    void updateController();
    void draw(sf::RenderWindow& window);

    MenuResult getResult() const;
    void resetResult();

private:
    enum Item
    {
        PLAY,
        PLAYER,
        SETTINGS,
        EXIT,
        COUNT
    };

    Item selected = PLAY;
    MenuResult result = MenuResult::None;

    sf::Text title;
    sf::Text items[COUNT];

    bool dpadUsed = false;

    void updateColors();
};
