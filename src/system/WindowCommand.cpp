#include "WindowCommand.hpp"

WindowCommand::WindowCommand(sf::RenderWindow& window)
    : window(window),
      desktop(sf::VideoMode::getDesktopMode())
{
}

void WindowCommand::setWindowed()
{
    window.create(
        sf::VideoMode(800, 600),
        "Cybershoot",
        sf::Style::Default
    );
}

void WindowCommand::setFullscreen()
{
    window.create(
        desktop,
        "Cybershoot",
        sf::Style::Fullscreen
    );
}

void WindowCommand::setBorderless()
{
    window.create(
        desktop,
        "Cybershoot",
        sf::Style::None
    );
}
