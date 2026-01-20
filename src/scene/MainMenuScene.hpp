#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "menu/MainMenu.hpp"
#include "system/WindowCommand.hpp"
#include "input/ControllerManager.hpp"

class SceneManager;

class MainMenuScene : public Scene
{
public:
    MainMenuScene(
        sf::RenderWindow& window,
        sf::Font& font,
        SceneManager& sceneManager,
        WindowCommand& windowCommand,
        ControllerManager& controllerManager
    );

    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    sf::RenderWindow& window;
    sf::Font& font;
    SceneManager& sceneManager;
    WindowCommand& windowCommand;
    ControllerManager& controllerManager;

    MainMenu menu;
};
