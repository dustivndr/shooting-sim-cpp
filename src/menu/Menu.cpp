#include "Menu.hpp"

Menu::Menu(sf::Font& font)
{
    // ---- Title ----
    title.setFont(font);
    title.setString("Cybershoot");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);

    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    title.setPosition(400.f, 150.f);

    // ---- Menu items ----
    const char* labels[COUNT] = {
        "PLAY",
        "PLAYER",
        "SETTINGS",
        "EXIT"
    };

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
    case PLAY:     result = MenuResult::Play; break;
    case PLAYER:   result = MenuResult::Player; break;
    case SETTINGS: result = MenuResult::Settings; break;
    case EXIT:     result = MenuResult::Exit; break;
    default: break;
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(title);
    for (int i = 0; i < COUNT; ++i)
        window.draw(items[i]);
}

void Menu::updateColors()
{
    sf::Color inactive(120, 120, 120);

    for (int i = 0; i < COUNT; ++i)
    {
        items[i].setFillColor(
            i == selected ? sf::Color::White : inactive
        );
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
