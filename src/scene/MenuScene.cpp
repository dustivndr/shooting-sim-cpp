#include "MenuScene.hpp"

MenuScene::MenuScene(sf::Font& font)
    : menu(font)
{
}

void MenuScene::handleEvent(const sf::Event&)
{
    // Keyboard input can be added here later
}

void MenuScene::update()
{
    controller.update();

    if (controller.menuUpPressed())
        menu.moveUp();

    if (controller.menuDownPressed())
        menu.moveDown();

    if (controller.menuConfirmPressed())
        menu.confirm();
}

void MenuScene::draw(sf::RenderWindow& window)
{
    menu.draw(window);
}

MenuResult MenuScene::getResult() const
{
    return menu.getResult();
}

void MenuScene::resetResult()
{
    menu.resetResult();
}
