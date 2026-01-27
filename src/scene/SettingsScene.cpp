#include "scene/SettingsScene.hpp"
#include "scene/MainMenuScene.hpp"

SettingsScene::SettingsScene(
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

void SettingsScene::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Up:
                if (!keyUpPressed)
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

            case sf::Keyboard::Escape:
                if (!keyEscapePressed)
                {
                    sceneManager.changeScene(
                        std::make_unique<MainMenuScene>(
                            window,
                            font,
                            sceneManager,
                            windowCommand,
                            controller
                        )
                    );
                    keyEscapePressed = true;
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

            case sf::Keyboard::Escape:
                keyEscapePressed = false;
                break;

            default:
                break;
        }
    }
}

void SettingsScene::update()
{
    controller.update();

    // Controller navigation
    if (controller.menuUpPressed())
        menu.moveUp();
    if (controller.menuDownPressed())
        menu.moveDown();
    if (controller.menuConfirmPressed())
        menu.confirm();
    if (controller.menuBackPressed()) {
        sceneManager.changeScene(
            std::make_unique<MainMenuScene>(
                window,
                font,
                sceneManager,
                windowCommand,
                controller
            )
        );
        return;
    }

    switch (menu.getResult())
    {
        case SettingsMenuResult::Windowed:
            windowCommand.setWindowed();
            menu.resetResult();
            break;

        case SettingsMenuResult::Fullscreen:
            windowCommand.setFullscreen();
            menu.resetResult();
            break;

        case SettingsMenuResult::Borderless:
            windowCommand.setBorderless();
            menu.resetResult();
            break;

        case SettingsMenuResult::Back:
            sceneManager.changeScene(
                std::make_unique<MainMenuScene>(
                    window,
                    font,
                    sceneManager,
                    windowCommand,
                    controller
                )
            );
            break;

        default:
            break;
    }
}

void SettingsScene::render(sf::RenderWindow& window)
{
    menu.updateLayout(window.getView());
    menu.draw(window);
}
