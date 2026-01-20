#include "menu/MainMenu.hpp"

MainMenu::MainMenu(sf::Font& font)
    : view(font)
{
    view.setTitle("Cybershoot");
    view.setItems({ "PLAY", "PLAYER", "SETTINGS", "EXIT" });
    view.setSelected(0);
}

void MainMenu::moveUp()
{
    if (selected > 0) selected--;
    view.setSelected(selected);
}

void MainMenu::moveDown()
{
    if (selected < view.getItemCount() - 1) selected++;
    view.setSelected(selected);
}

void MainMenu::confirm()
{
    switch (selected)
    {
        case 0: result = MainMenuResult::Play; break;
        case 1: result = MainMenuResult::Player; break;
        case 2: result = MainMenuResult::Settings; break;
        case 3: result = MainMenuResult::Exit; break;
    }
}

MainMenuResult MainMenu::getResult() const
{
    return result;
}

void MainMenu::resetResult()
{
    result = MainMenuResult::None;
}

void MainMenu::updateLayout(const sf::View& view_)
{
    view.updateLayout(view_);
}

void MainMenu::draw(sf::RenderWindow& window)
{
    view.draw(window);
}
