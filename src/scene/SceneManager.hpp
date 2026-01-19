#pragma once

#include <memory>
#include "Scene.hpp"

class SceneManager
{
public:
    void setScene(std::unique_ptr<Scene> newScene);
    Scene* getCurrent();

private:
    std::unique_ptr<Scene> current;
};
