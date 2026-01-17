#include <iostream>

#include "Menu.hpp"

Menu::Menu(sf::Font &font)
{
    // ---- Title ----
    title.setFont(font);
    title.setString("Cybershoot");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color(57, 255, 20));

    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    title.setPosition(400.f, 150.f);

    // ---- Menu items ----
    const char *labels[COUNT] = {
        "PLAY",
        "PLAYER",
        "SETTINGS",
        "EXIT"};

    for (int i = 0; i < COUNT; ++i)
    {
        items[i].setFont(font);
        items[i].setString(labels[i]);
        items[i].setCharacterSize(40);
        items[i].setPosition(200.f, 250.f + i * 50.f);
    }

    updateColors();
}

void Menu::moveUp()
{
    if (selected > 0)
        selected = static_cast<Item>(selected - 1);

    updateColors();
}

void Menu::moveDown()
{
    if (selected < COUNT - 1)
        selected = static_cast<Item>(selected + 1);

    updateColors();
}

void Menu::confirm()
{
    switch (selected)
    {
    case PLAY:
        result = MenuResult::Play;
        std::cout << "Play selected\n";
        break;
    case PLAYER:
        result = MenuResult::Player;
        std::cout << "Player selected\n";
        break;
    case SETTINGS:
        result = MenuResult::Settings;
        std::cout << "Settings selected\n";
        break;
    case EXIT:
        result = MenuResult::Exit;
        std::cout << "Exit selected\n";
        break;
    default:
        break;
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int g = 0; g < 2; ++g)
    {
        sf::Text glow = title;
        glow.setFillColor(sf::Color(57, 255, 20, 60 - g * 20));
        glow.setScale(1.f + g * 0.04f, 1.f + g * 0.04f);
        window.draw(glow);
    }

    window.draw(title);

    for (int i = 0; i < COUNT; ++i)
    {
        if (i == selected)
        {
            for (int g = 0; g < 3; ++g)
            {
                sf::Text glow = items[i];
                glow.setFillColor(sf::Color(57, 255, 20, 90 - g * 25));
                glow.setScale(1.f + g * 0.06f, 1.f + g * 0.06f);
                window.draw(glow);
            }
        }

        // Menu item
        window.draw(items[i]);
    }
}

void Menu::updateColors()
{
    sf::Color inactive(30, 160, 20);
    sf::Color active(57, 255, 20);

    for (int i = 0; i < COUNT; ++i)
    {
        items[i].setFillColor(
            i == selected ? active : inactive);
    }
}

MenuResult Menu::getResult() const
{
    return result;
}

void Menu::resetResult()
{
    result = MenuResult::None;
}
