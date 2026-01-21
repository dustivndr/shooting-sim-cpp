#include "scene/MainMenuScene.hpp"
#include "scene/SettingsScene.hpp"

MainMenuScene::MainMenuScene(
    sf::RenderWindow& window,
    sf::Font& font,
    SceneManager& sceneManager,
    WindowCommand& windowCommand,
    ControllerManager& controller
)
: window(window)
, font(font)
, sceneManager(sceneManager)
, windowCommand(windowCommand)
, controller(controller)
, menu(font)
{
}

void MainMenuScene::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return;

    switch (event.key.code)
    {
        case sf::Keyboard::Up:
            menu.moveUp();
            break;

        case sf::Keyboard::Down:
            menu.moveDown();
            break;

        case sf::Keyboard::Enter:
            menu.confirm();
            break;

        default:
            break;
    }
}

void MainMenuScene::update()
{
    controller.update();
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
                controller
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
    window.setView(window.getDefaultView());
    menu.updateLayout(window.getView());
    menu.draw(window);
}
