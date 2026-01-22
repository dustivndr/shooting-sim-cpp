#pragma once

#include "graphics/ViewManager.hpp"

class WindowCommand
{
public:
    WindowCommand(sf::RenderWindow& window, ViewManager& viewManager);

    void setWindowed();
    void setFullscreen();
    void setBorderless();

private:
    void recreate(sf::VideoMode mode, sf::Uint32 style);

private:
    sf::RenderWindow& window;
    ViewManager& viewManager;

    sf::VideoMode windowedMode;
    sf::VideoMode desktopMode;
};
