#include "menu/SettingsMenu.hpp"

SettingsMenu::SettingsMenu(sf::Font& font)
{
    // ---- Title ----
    title.setFont(font);
    title.setString("SETTINGS");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color(57, 255, 20));

    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    title.setPosition(400.f, 140.f);

    // ---- Menu items ----
    const char* labels[ITEM_COUNT] =
    {
        "WINDOWED",
        "FULLSCREEN",
        "BORDERLESS",
        "BACK"
    };

    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        items[i].setFont(font);
        items[i].setString(labels[i]);
        items[i].setCharacterSize(34);
        items[i].setPosition(260.f, 260.f + i * 50.f);
    }

    updateColors();
}

void SettingsMenu::moveUp()
{
    if (selected > 0)
        selected--;

    updateColors();
}

void SettingsMenu::moveDown()
{
    if (selected < ITEM_COUNT - 1)
        selected++;

    updateColors();
}

void SettingsMenu::confirm()
{
    switch (selected)
    {
        case 0: result = SettingsMenuResult::Windowed; break;
        case 1: result = SettingsMenuResult::Fullscreen; break;
        case 2: result = SettingsMenuResult::Borderless; break;
        case 3: result = SettingsMenuResult::Back; break;
        default: result = SettingsMenuResult::None; break;
    }
}

SettingsMenuResult SettingsMenu::getResult() const
{
    return result;
}

void SettingsMenu::resetResult()
{
    result = SettingsMenuResult::None;
}

void SettingsMenu::updateColors()
{
    sf::Color active(57, 255, 20);
    sf::Color inactive(30, 160, 20);

    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        items[i].setFillColor(i == selected ? active : inactive);
    }
}

void SettingsMenu::draw(sf::RenderWindow& window)
{
    // ---- Title glow ----
    for (int g = 0; g < 2; ++g)
    {
        sf::Text glow = title;
        glow.setFillColor(sf::Color(57, 255, 20, 60 - g * 20));
        glow.setScale(1.f + g * 0.04f, 1.f + g * 0.04f);
        window.draw(glow);
    }

    window.draw(title);

    // ---- Menu items ----
    for (int i = 0; i < ITEM_COUNT; ++i)
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

        window.draw(items[i]);
    }
}
