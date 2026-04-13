#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "GameObjects/GameObject.h"

class Renderer;

class Scene {
public:
    Scene();
    ~Scene();

    void addGameObject(std::unique_ptr<GameObject> obj);
    void removeGameObject(GameObject* obj);
    void removeGameObject(const std::string& name);

    void start();
    void update(float deltaTime);
    void render(Renderer& renderer);

    GameObject* findObject(const std::string& name);
    void clear();

private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    std::unordered_map<std::string, GameObject*> m_nameMap;
};