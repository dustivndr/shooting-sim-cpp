#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "input/ControllerManager.hpp"
#include "menu/Menu.hpp"
#include "graphics/ViewManager.hpp"

int main()
{
    constexpr unsigned GAME_W = 800;
    constexpr unsigned GAME_H = 600;

    bool fullscreen = false;

    sf::VideoMode windowedMode(GAME_W, GAME_H);
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(
        windowedMode,
        "Cybershoot",
        sf::Style::Titlebar | sf::Style::Close
    );

    ViewManager viewManager(GAME_W, GAME_H);
    viewManager.update(window.getSize());

    window.setFramerateLimit(60);

    auto recreateWindow = [&](bool fs)
    {
        window.close();

        if (fs)
        {
            window.create(
                fullscreenMode,
                "Cybershoot",
                sf::Style::Fullscreen
            );
        }
        else
        {
            window.create(
                windowedMode,
                "Cybershoot",
                sf::Style::Titlebar | sf::Style::Close
            );
        }

        viewManager.update(window.getSize());
        window.setVerticalSyncEnabled(true);
    };

    sf::Font font;
    if (!font.loadFromFile("assets/vcr-osd-mono.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return 1;
    }

    ControllerManager controller;
    Menu menu(font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (menu.getResult() == MenuResult::Exit)
            {
                window.close();
                menu.resetResult();
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F11)
            {
                fullscreen = !fullscreen;
                recreateWindow(fullscreen);
            }
        }

        controller.update();

        if (controller.menuUpPressed())
            menu.moveUp();

        if (controller.menuDownPressed())
            menu.moveDown();

        if (controller.menuConfirmPressed())
            menu.confirm();

        window.clear(sf::Color::Black);
        viewManager.apply(window);
        menu.draw(window);
        window.display();
    }

    return 0;
}
