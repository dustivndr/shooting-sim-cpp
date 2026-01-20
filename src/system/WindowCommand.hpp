#pragma once

#include <SFML/Graphics.hpp>

#include "system/DisplayMode.hpp"

struct WindowCommand
{
    bool requested = false;
    DisplayMode mode = DisplayMode::Windowed;
};

class WindowCommand
{
public:
    WindowCommand(sf::RenderWindow& window);

    void setWindowed();
    void setFullscreen();
    void setBorderless();

private:
    sf::RenderWindow& window;
    sf::VideoMode desktop;
};