#include <SFML/Graphics.hpp>

#include "scene/SceneManager.hpp"
#include "scene/MainMenuScene.hpp"
#include "input/ControllerManager.hpp"
#include "system/WindowCommand.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Cybershoot",
        sf::Style::Titlebar | sf::Style::Close);

    // Disable OS key repeat to ensure only one KeyPressed per physical press
    window.setKeyRepeatEnabled(false);

    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("assets/vcr-osd-mono.ttf"))
    {
        return 1;
    }

    ControllerManager controller;
    ViewManager viewManager(800, 600);
    WindowCommand windowCommand(window, viewManager);

    // Ensure the view starts letterboxed at 4:3
    viewManager.update(window.getSize());
    window.setView(viewManager.getView());

    SceneManager sceneManager;

    sceneManager.changeScene(
        std::make_unique<MainMenuScene>(
            window,
            font,
            sceneManager,
            windowCommand,
            controller
        )
    );

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                viewManager.update({ event.size.width, event.size.height });
                window.setView(viewManager.getView());
            }

            sceneManager.handleEvent(event);
        }

        sceneManager.update();

        window.clear(sf::Color::Black);
        sceneManager.render(window);
        window.display();
    }

    return 0;
}