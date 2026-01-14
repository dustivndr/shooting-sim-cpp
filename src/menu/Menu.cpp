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

void Menu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up && selected > 0)
            selected = static_cast<Item>(selected - 1);

        if (event.key.code == sf::Keyboard::Down && selected < COUNT - 1)
            selected = static_cast<Item>(selected + 1);

        if (event.key.code == sf::Keyboard::Enter)
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
    }

    // ---- Controller confirm ----
    if (event.type == sf::Event::JoystickButtonPressed)
    {
        const unsigned X_BUTTON = 3;

        if (event.joystickButton.joystickId == 0 &&
            event.joystickButton.button == X_BUTTON)
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
    }

    updateColors();
}

void Menu::updateController()
{
    if (!sf::Joystick::isConnected(0))
        return;

    float povY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

    if (!dpadUsed)
    {
        if (povY > 50 && selected < COUNT - 1)
        {
            selected = static_cast<Item>(selected + 1);
            dpadUsed = true;
        }
        else if (povY < -50 && selected > 0)
        {
            selected = static_cast<Item>(selected - 1);
            dpadUsed = true;
        }
    }

    if (povY > -20 && povY < 20)
        dpadUsed = false;

    updateColors();
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
        items[i].setFillColor(
            i == selected ? sf::Color::White : inactive);
}

MenuResult Menu::getResult() const
{
    return result;
}

void Menu::resetResult()
{
    result = MenuResult::None;
}
