#include <iostream>

#include <SFML/Graphics.hpp>

#include "graphics/ViewManager.hpp"
#include "scene/SceneManager.hpp"
#include "scene/MenuScene.hpp"

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

        window.create(
            fs ? fullscreenMode : windowedMode,
            "Cybershoot",
            fs ? sf::Style::Fullscreen
               : (sf::Style::Titlebar | sf::Style::Close)
        );

        viewManager.update(window.getSize());
        window.setVerticalSyncEnabled(true);
    };

    sf::Font font;
    if (!font.loadFromFile("assets/vcr-osd-mono.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return 1;
    }

    SceneManager sceneManager;
    sceneManager.setScene(std::make_unique<MenuScene>(font));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F11)
            {
                fullscreen = !fullscreen;
                recreateWindow(fullscreen);
            }

            if (sceneManager.getCurrent())
                sceneManager.getCurrent()->handleEvent(event);
        }

        if (sceneManager.getCurrent())
        {
            sceneManager.getCurrent()->update();
            
            if (auto menuScene = dynamic_cast<MenuScene*>(sceneManager.getCurrent()))
            {
                if (menuScene->getResult() == MenuResult::Exit)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        viewManager.apply(window);
       
        if (sceneManager.getCurrent())
            sceneManager.getCurrent()->draw(window);

        window.display();
    }

    return 0;
}
