#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "input/ControllerManager.hpp"
#include "menu/Menu.hpp"

sf::View getLetterboxView(sf::View view, int winW, int winH)
{
    float windowRatio = (float)winW / (float)winH;
    float viewRatio = view.getSize().x / view.getSize().y;

    float sizeX = 1.f, sizeY = 1.f;
    float posX = 0.f, posY = 0.f;

    if (windowRatio > viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }

    view.setViewport({posX, posY, sizeX, sizeY});
    return view;
}

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
        sf::Style::Default);

    window.setFramerateLimit(60);

    sf::View gameView(sf::FloatRect(0, 0, GAME_W, GAME_H));
    window.setView(gameView);

    auto recreateWindow = [&](bool fs)
    {
        window.close();

        if (fs)
        {
            window.create(
                fullscreenMode,
                "Cybershoot",
                sf::Style::Fullscreen);
        }
        else
        {
            window.create(
                windowedMode,
                "Cybershoot",
                sf::Style::Default);
        }

        gameView = getLetterboxView(
            sf::View(sf::FloatRect(0.f, 0.f, GAME_W, GAME_H)),
            window.getSize().x,
            window.getSize().y);

        window.setView(gameView);
        window.setVerticalSyncEnabled(true);
    };

    sf::Font font;
    if (!font.loadFromFile("assets/vcr-osd-mono.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
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
                window.close();
        }

        controller.update();

        if (controller.menuUpPressed())
            menu.moveUp();

        if (controller.menuDownPressed())
            menu.moveDown();

        if (controller.menuConfirmPressed())
            menu.confirm();

        window.clear(sf::Color::Black);
        menu.draw(window);
        window.display();
    }
}
