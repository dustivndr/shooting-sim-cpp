#pragma once

#include <SFML/Graphics.hpp>

#include "scene/Scene.hpp"
#include "scene/SceneManager.hpp"
#include "menu/SettingsMenu.hpp"
#include "system/WindowCommand.hpp"
#include "input/ControllerManager.hpp"

class SettingsScene : public Scene
{
public:
    SettingsScene(
        sf::RenderWindow& window,
        sf::Font& font,
        SceneManager& sceneManager,
        WindowCommand& windowCommand,
        ControllerManager& controller
    );

    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    sf::RenderWindow& window;
    sf::Font& font; 
    SceneManager& sceneManager;
    WindowCommand& windowCommand;
    ControllerManager& controller;

    SettingsMenu menu;

    // Track which keys are currently pressed to prevent repeated triggers
    bool keyUpPressed = false;
    bool keyDownPressed = false;
    bool keyEnterPressed = false;
    bool keyEscapePressed = false;
};
