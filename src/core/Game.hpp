#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class State;

class Game
{
public:
    Game();
    void run();

    // State control
    void changeState(std::unique_ptr<State> newState);

    // Global actions
    void quit();
    sf::RenderWindow &getWindow();

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    std::unique_ptr<State> currentState;
};