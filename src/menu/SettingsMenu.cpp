#include "menu/SettingsMenu.hpp"

SettingsMenu::SettingsMenu(sf::Font& font)
    : view(font)
{
    view.setTitle("SETTINGS");
    view.setItems({ "WINDOWED", "FULLSCREEN", "BORDERLESS", "BACK" });
    view.setSelected(0);
}

void SettingsMenu::moveUp()
{
    if (selected > 0) selected--;
    view.setSelected(selected);
}

void SettingsMenu::moveDown()
{
    if (selected < view.getItemCount() - 1) selected++;
    view.setSelected(selected);
}

void SettingsMenu::confirm()
{
    switch (selected)
    {
        case 0: result = SettingsMenuResult::Windowed; break;
        case 1: result = SettingsMenuResult::Fullscreen; break;
        case 2: result = SettingsMenuResult::Borderless; break;
        case 3: result = SettingsMenuResult::Back; break;
        //default: result = SettingsMenuResult::None; break;
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

void SettingsMenu::updateLayout(const sf::View& view_)
{
    view.updateLayout(view_);
}

void SettingsMenu::draw(sf::RenderWindow& window)
{
    view.draw(window);
}
