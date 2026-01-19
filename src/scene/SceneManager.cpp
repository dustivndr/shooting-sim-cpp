#include "SceneManager.hpp"

void SceneManager::setScene(std::unique_ptr<Scene> newScene)
{
    current = std::move(newScene);
}

Scene* SceneManager::getCurrent()
{
    return current.get();
}
