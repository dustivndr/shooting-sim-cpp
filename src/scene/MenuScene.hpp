#pragma once

#include <SFML/Graphics.hpp>

#include "scene/Scene.hpp"
#include "menu/Menu.hpp"
#include "input/ControllerManager.hpp"

class MenuScene : public Scene
{
public:
    MenuScene(sf::Font& font);

    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

    MenuResult getResult() const;
    void resetResult();

private:
    ControllerManager controller;
    Menu menu;
};
