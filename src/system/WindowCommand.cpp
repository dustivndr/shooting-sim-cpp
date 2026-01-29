
#include "system/WindowCommand.hpp"

WindowCommand::WindowCommand(
    sf::RenderWindow& window_,
    ViewManager& viewManager_
)
    : window(window_)
    , viewManager(viewManager_)
{
    windowedMode = sf::VideoMode(800, 600);
    desktopMode  = sf::VideoMode::getDesktopMode();
}

void WindowCommand::recreate(sf::VideoMode mode, sf::Uint32 style)
{
    window.close();
    window.create(mode, "Cybershoot", style);

    viewManager.update(window.getSize());
    window.setView(viewManager.getView());

    window.setFramerateLimit(60);
}

void WindowCommand::setWindowed()
{
    recreate(windowedMode, sf::Style::Titlebar | sf::Style::Close);
}

void WindowCommand::setFullscreen()
{
    recreate(desktopMode, sf::Style::Titlebar | sf::Style::Close);
}

void WindowCommand::setBorderless()
{
    recreate(desktopMode, sf::Style::Fullscreen);
}
