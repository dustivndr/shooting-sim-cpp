#include <cmath>

#include "ControllerManager.hpp"

static float normalizeAxis(float v, float deadzone)
{
    if (std::abs(v) < deadzone)
        return 0.f;

    return v / 100.f;
}

void ControllerManager::update()
{
    // Save previous states
    menuUpPrev = menuUpNow;
    menuDownPrev = menuDownNow;
    confirmPrev = confirmNow;
    // backPrev     = backNow;

    menuUpNow = false;
    menuDownNow = false;
    confirmNow = false;
    // backNow     = false;

    // Keyboard
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        menuUpNow = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        menuDownNow = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        confirmNow = true;

    // Read Controller
    if (sf::Joystick::isConnected(id))
    {
        float rawY = sf::Joystick::getAxisPosition(id, sf::Joystick::Y);

        float leftY = normalizeAxis(rawY, deadzone);

        // rawY = -rawY;

        leftY = normalizeAxis(rawY, deadzone);

        if (leftY < -menuThreshold)
            menuUpNow = true;
        if (leftY > menuThreshold)
            menuDownNow = true;

        if (sf::Joystick::hasAxis(id, sf::Joystick::PovY))
        {
            float povY = sf::Joystick::getAxisPosition(id, sf::Joystick::PovY);

            if (povY > 50)
                menuUpNow = true;
            if (povY < -50)
                menuDownNow = true;
        }
        else
        {
            if (sf::Joystick::isButtonPressed(id, 11))
                menuUpNow = true;
            if (sf::Joystick::isButtonPressed(id, 12))
                menuDownNow = true;
        }

        // Confirm X
        if (sf::Joystick::isButtonPressed(id, 2)) // X
            confirmNow = true;
    }

    // Current logical menu states
    // menuUpNow   = dpadUp   || leftY < -menuThreshold;
    // menuDownNow = dpadDown || leftY >  menuThreshold;

    // confirmNow = sf::Joystick::isButtonPressed(id, 3); // X
    // backNow    = sf::Joystick::isButtonPressed(id, 1); // B
}

bool ControllerManager::menuUpPressed()
{
    return menuUpNow && !menuUpPrev;
}

bool ControllerManager::menuDownPressed()
{
    return menuDownNow && !menuDownPrev;
}

bool ControllerManager::menuConfirmPressed()
{
    return confirmNow && !confirmPrev;
}

// bool ControllerManager::menuBackPressed()
// {
//     return backNow && !backPrev;
// }

// float ControllerManager::moveForward() const
// {
//     return leftY;
// }

// float ControllerManager::moveSide() const
// {
//     return leftX;
// }
