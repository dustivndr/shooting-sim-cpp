#pragma once

#include <SFML/Graphics.hpp>

class WindowCommand;

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
