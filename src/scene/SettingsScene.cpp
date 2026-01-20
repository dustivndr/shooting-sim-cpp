#include "scene/SettingsScene.hpp"
#include "scene/MainMenuScene.hpp"

SettingsScene::SettingsScene(
    sf::RenderWindow& window_,
    sf::Font& font_,
    SceneManager& sceneManager_,
    WindowCommand& windowCommand_,
    ControllerManager& controller_
)
    : window(window_)
    , font(font_)
    , sceneManager(sceneManager_)
    , windowCommand(windowCommand_)
    , controller(controller_)
    , menu(font_)
{
}

void SettingsScene::handleEvent(const sf::Event& event)
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

        case sf::Keyboard::Escape:
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

void SettingsScene::update()
{
    controller.update();

    if (controller.menuUpPressed())
        menu.moveUp();

    if (controller.menuDownPressed())
        menu.moveDown();

    if (controller.menuConfirmPressed())
        menu.confirm();

    if (controller.menuBackPressed())
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
    menu.draw(window);
}
