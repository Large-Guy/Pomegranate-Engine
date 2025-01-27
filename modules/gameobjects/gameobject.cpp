#include "gameobject.h"

std::unordered_map<GameObjectID, GameObject *> GameObject::gameObjects = {};
std::unordered_map<std::string, std::vector<GameObject *>> GameObject::gameObjectsByName = {};
GameObjectID GameObject::nextID = 0;

GameObject::GameObject() : id(nextID++) {
    name = "GameObject";
    gameObjects[id] = this;
    gameObjectsByName[name].push_back(this);
}

GameObject::GameObject(const std::string &name) : id(nextID++) {
    this->name = name;
    gameObjects[id] = this;
    gameObjectsByName[name].push_back(this);
}

GameObject::~GameObject() {
    gameObjects.erase(id);
    gameObjectsByName[name].erase(std::remove(gameObjectsByName[name].begin(), gameObjectsByName[name].end(), this),
                                  gameObjectsByName[name].end());
    for (GameObject *child: children) {
        delete child;
    }
}

std::string GameObject::getName() const {
    return name;
}

void GameObject::setName(const std::string &name) {
    gameObjectsByName[this->name].erase(
            std::remove(gameObjectsByName[name].begin(), gameObjectsByName[name].end(), this),
            gameObjectsByName[name].end());
    this->name = name;
    gameObjectsByName[name].push_back(this);
}

void GameObject::addChild(GameObject *child) {
    if (std::find(children.begin(), children.end(), child) != children.end()) {
        return;
    }
    children.push_back(child);
    if (child->parent != nullptr) {
        child->parent->removeChild(child);
    }
    child->parent = this;
}

void GameObject::removeChild(GameObject *child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void GameObject::setParent(GameObject *parent) {
    parent->addChild(this);
}

GameObject *GameObject::getParent() {
    return this->parent;
}

std::vector<GameObject *> GameObject::getChildren() {
    return children;
}

GameObject *GameObject::find(GameObjectID id) {
    return gameObjects[id];
}

GameObject *GameObject::find(const std::string &name) {
    return gameObjectsByName[name][0];
}

std::vector<GameObject *> GameObject::findAll(const std::string &name) {
    return gameObjectsByName[name];
}