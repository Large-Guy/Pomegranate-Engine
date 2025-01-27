#ifndef POMEGRANATEENGINE_GAMEOBJECT_H
#define POMEGRANATEENGINE_GAMEOBJECT_H

#include "typedefs.h"
#include<string>
#include<vector>
#include<unordered_map>
#include "component.h"

class GameObject {
    static std::unordered_map<GameObjectID, GameObject *> gameObjects;
    static std::unordered_map<std::string, std::vector<GameObject *>> gameObjectsByName;
    static GameObjectID nextID;

    std::vector<GameObject *> children;
    GameObject *parent = nullptr;
    std::string name;

    std::unordered_map<ComponentID, size_t> components;
public:
    const GameObjectID id;

    GameObject();

    GameObject(const std::string &name);

    ~GameObject();

    std::string getName() const;

    void setName(const std::string &name);

    void addChild(GameObject *child);

    void removeChild(GameObject *child);

    void setParent(GameObject *parent);

    GameObject *getParent();

    std::vector<GameObject *> getChildren();

    static GameObject *find(const std::string &name);

    static GameObject *find(GameObjectID id);

    static std::vector<GameObject *> findAll(const std::string &name);

    template<typename Comp, typename...Args>
    void addComponent(Args... args) {
        Comp *component = (Comp *) malloc(sizeof(Comp));
        size_t pointer = sizeof(GameObject *);
        GameObject *gameObject = this;
        memcpy((void *) &(component->gameObject), (void *) &gameObject, pointer); //Override const
        new(component) Comp(args...);
        memcpy((void *) &(component->gameObject), (void *) &gameObject, pointer); //Override const

        component->start();

        ComponentID id = Component::component_types[typeid(Comp).hash_code()];
        components[id] = Component::addComponent(id, component);
    }

    template<typename Comp>
    Comp *getComponent() {
        ComponentID id = Component::component_types[typeid(Comp).hash_code()];
        return (Comp *) Component::getComponent(id, components[id]);
    }
};


#endif //POMEGRANATEENGINE_GAMEOBJECT_H
