#ifndef POMEGRANATEENGINE_COMPONENT_H
#define POMEGRANATEENGINE_COMPONENT_H

#include <core/core.h>
#include <unordered_map>
#include <functional>
#include "typedefs.h"

class GameObject;

struct ClassFunctions {
    std::function<void(void*)> constructor;
    std::function<void(void*)> destructor;
    std::function<void(void*, void*)> copy;
    std::function<void(void*, void*)> move;
    std::function<void(Archive&, void*)> serialize;
    std::function<void(Archive&, void*)> deserialize;
};

template<typename T>
void _constructor(void* ptr) {
    new(ptr) T();
}

template<typename T>
void _destructor(void* ptr) {
    ((T*) ptr)->~T();
}

template<typename T>
void _copy(void* dest, void* src) {
    //Make sure to use the copy constructor because some objects are not trivially copyable
    T* d = (T*) dest;
    T* s = (T*) src;
    new(dest) T(*(T*) src);
}

template<typename T>
void _move(void* dest, void* src) {
    //Make sure to use the move constructor because some objects are not trivially copyable
    new(dest) T(std::move(*(T*) src));
}

template<typename T>
void _serialize(Archive& archive, void* ptr) {
    ((T*) ptr)->serialize(archive);
}

template<typename T>
void _deserialize(Archive& archive, void* ptr) {
    ((T*) ptr)->deserialize(archive);
}

class ComponentList;

class Component {
private:
    static std::unordered_map<ComponentID, ClassFunctions> components;
    static std::unordered_map<std::string, ComponentID> component_names;
    static std::unordered_map<size_t, ComponentID> component_types;

    static std::unordered_map<ComponentID, ComponentList> component_lists;
public:
    GameObject* const gameObject = nullptr;

    Component();

    friend GameObject;

    template<typename Comp>
    static ComponentID create(const std::string& name);

    virtual void start() {};

    virtual void update() {};

    virtual void draw() {};

    virtual void serialize(Archive& archive) const {};

    virtual void deserialize(Archive& archive) {};

    static size_t addComponent(ComponentID component, void* data);

    static void* getComponent(ComponentID component, size_t owner);

    static void callUpdate(ComponentID component);

    static void callDraw(ComponentID component);

    static void callUpdate();

    static void callDraw();
};

struct ComponentList {
    ComponentID component;
    void* elements;
    bool* occupied;
    size_t element_size;
    size_t capacity;
    size_t count;

    ComponentList();

    explicit ComponentList(ComponentID component, size_t component_size);

    void resize(size_t new_size);

    void* get(size_t i) const;

    void remove(size_t i);

    size_t add();

    bool has(size_t i) const;

    friend Component;
};

#include "component_impl.h"

#endif //POMEGRANATEENGINE_COMPONENT_H
