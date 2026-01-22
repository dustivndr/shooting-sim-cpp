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
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Up:
                if (!keyUpPressed)  // Only act on the initial press, not repeats
                {
                    menu.moveUp();
                    keyUpPressed = true;
                }
                break;

            case sf::Keyboard::Down:
                if (!keyDownPressed)
                {
                    menu.moveDown();
                    keyDownPressed = true;
                }
                break;

            case sf::Keyboard::Enter:
                if (!keyEnterPressed)
                {
                    menu.confirm();
                    keyEnterPressed = true;
                }
                break;

            default:
                break;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Up:
                keyUpPressed = false;
                break;

            case sf::Keyboard::Down:
                keyDownPressed = false;
                break;

            case sf::Keyboard::Enter:
                keyEnterPressed = false;
                break;

            default:
                break;
        }
    }
}

void MainMenuScene::update()
{
    controller.update();

    // Controller navigation
    if (controller.menuUpPressed())
        menu.moveUp();
    if (controller.menuDownPressed())
        menu.moveDown();
    if (controller.menuConfirmPressed())
        menu.confirm();

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
