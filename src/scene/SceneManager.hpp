#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Scene.hpp"

class SceneManager
{
public:
    void changeScene(std::unique_ptr<Scene> newScene);

    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

    bool hasScene() const;

private:
    std::unique_ptr<Scene> currentScene;
};
