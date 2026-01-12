#include "Game.hpp"
#include "../states/MenuState.hpp"

Game::Game()
: window(sf::VideoMode(800, 600), "Shooting Sim C++")
{
    window.setFramerateLimit(60);
    //currentState = std::make_unique<MenuState>(*this);
}