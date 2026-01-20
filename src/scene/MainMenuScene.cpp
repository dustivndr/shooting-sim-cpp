#include "scene/MainMenuScene.hpp"
#include "scene/SettingsScene.hpp"

MainMenuScene::MainMenuScene(
    sf::RenderWindow& window,
    sf::Font& font,
    SceneManager& sceneManager,
    WindowCommand& windowCommand,
    ControllerManager& controllerManager
)
: window(window)
, font(font)
, sceneManager(sceneManager)
, windowCommand(windowCommand)
, controllerManager(controllerManager)
, menu(font)
{
}

void MainMenuScene::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
            menu.moveUp();
        else if (event.key.code == sf::Keyboard::Down)
            menu.moveDown();
        else if (event.key.code == sf::Keyboard::Enter)
            menu.confirm();
    }
}

void MainMenuScene::update()
{
    switch (menu.getResult())
    {
    case MainMenuResult::Play:
        // later
        break;

    case MainMenuResult::Settings:
        sceneManager.changeScene(
            std::make_unique<SettingsScene>(
                window,
                font,
                sceneManager,
                windowCommand,
                controllerManager
            )
        );
        break;

    case MainMenuResult::Exit:
        window.close();
        break;

    default:
        break;
    }

    menu.resetResult();
}

void MainMenuScene::render(sf::RenderWindow& window)
{
    menu.draw(window);
}
