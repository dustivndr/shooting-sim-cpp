#include <iostream>
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

    // Read Controller
    if (sf::Joystick::isConnected(id))
    {
        // float rawY = sf::Joystick::getAxisPosition(id, sf::Joystick::Y);

        // float leftY = normalizeAxis(rawY, deadzone);

        float leftY = normalizeAxis(
            sf::Joystick::getAxisPosition(id, sf::Joystick::Y),
            deadzone
        );

        if (leftY < -menuThreshold)
            menuUpNow = true;
        if (leftY > menuThreshold)
            menuDownNow = true;

        if (sf::Joystick::hasAxis(id, sf::Joystick::PovY))
        {
            float povY = sf::Joystick::getAxisPosition(id, sf::Joystick::PovY);
            
            #ifdef __linux__
            povY = -povY; // Invert POV Y on Linux
            #endif

            if (povY > 50)
                menuUpNow = true;
            if (povY < -50)
                menuDownNow = true;
            
            // inverted
            // if (povY < -50)
            //     menuUpNow = true;
            // if (povY > 50)
            //     menuDownNow = true;
        }

        // Confirm A btn
        if (sf::Joystick::isButtonPressed(id, 0))
            confirmNow = true;

        // DEBUG: Print all pressed buttons
        for (unsigned i = 0; i < sf::Joystick::getButtonCount(id); ++i)
        {
            if (sf::Joystick::isButtonPressed(id, i))
            {
                std::cout << "Joystick button " << i << " pressed\n";
            }
        }
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

bool ControllerManager::menuBackPressed()
{
    return backNow && !backPrev;
}

// float ControllerManager::moveForward() const
// {
//     return leftY;
// }

// float ControllerManager::moveSide() const
// {
//     return leftX;
// }
