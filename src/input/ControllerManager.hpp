#pragma once

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>

class ControllerManager
{
public:
    void update();

    // Edge-triggered menu input
    bool menuUpPressed();
    bool menuDownPressed();
    bool menuConfirmPressed();
    bool menuBackPressed();

    // Continuous (for gameplay)
    float moveForward() const;
    float moveSide() const;

private:
    unsigned int id = 0;

    float deadzone = 25.f;
    float menuThreshold = 0.6f;

    // Axis
    float leftX = 0.f;
    float leftY = 0.f;

    // Current state
    bool menuUpNow = false;
    bool menuDownNow = false;
    bool confirmNow = false;
    bool backNow = false;

    // Previous state
    bool menuUpPrev = false;
    bool menuDownPrev = false;
    bool confirmPrev = false;
    bool backPrev = false;
};
