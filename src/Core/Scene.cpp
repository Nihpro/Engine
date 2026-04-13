#include "Scene.h"
#include <iostream>
#include "../Renderer/Renderer.h"

Scene::Scene() {}

Scene::~Scene() {
    clear();
}

void Scene::addGameObject(std::unique_ptr<GameObject> obj) {
    if (!obj) return;

    if (!obj->getName().empty()) {
        m_nameMap[obj->getName()] = obj.get();
    }

    m_gameObjects.push_back(std::move(obj));
}

void Scene::removeGameObject(GameObject* obj) {
    if (!obj) return;

    auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [obj](const std::unique_ptr<GameObject>& o) {
            return o.get() == obj;
        });

    if (it != m_gameObjects.end()) {
        if (!obj->getName().empty()) {
            m_nameMap.erase(obj->getName());
        }
        m_gameObjects.erase(it);
    }
}

void Scene::removeGameObject(const std::string& name) {
    auto it = m_nameMap.find(name);
    if (it != m_nameMap.end()) {
        removeGameObject(it->second);
    }
}

void Scene::start() {
    for (auto& obj : m_gameObjects) {
        obj->start();
    }
}

void Scene::update(float deltaTime) {
    for (auto& obj : m_gameObjects) {
        if (obj->isActive()) {
            obj->update(deltaTime);
        }
    }
}

void Scene::render(Renderer& renderer) {
    static int renderCount = 0;
    if (renderCount++ % 60 == 0) {
        std::cout << "Scene::render, drawing " << m_gameObjects.size() << " objects" << std::endl;
    }
    for (auto& obj : m_gameObjects) {
        if (obj->isActive()) {
            obj->render(renderer);
        }
    }
}

GameObject* Scene::findObject(const std::string& name) {
    auto it = m_nameMap.find(name);
    if (it != m_nameMap.end()) {
        return it->second;
    }
    return nullptr;
}

void Scene::clear() {
    m_gameObjects.clear();
    m_nameMap.clear();
}