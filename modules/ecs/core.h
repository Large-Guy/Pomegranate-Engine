#ifndef POMEGRANATE_ENGINE_ECS_CORE_H
#define POMEGRANATE_ENGINE_ECS_CORE_H

#include <unordered_map>
#include <string>
#include <core/core.h>
#include "ecs_typedefs.h"
#include <functional>

struct Entity;
struct EntityRecord;
struct ArchetypeRecord;
struct Archetype;

struct SetHash {
    std::size_t operator()(const std::unordered_set<EntityID>& set) const;
};

struct SetEqual {
    bool operator()(const std::unordered_set<EntityID>& set1, const std::unordered_set<EntityID>& set2) const;
};

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

class ECS {
public:
    std::unordered_map<EntityID, EntityRecord*> entity_index;
    std::unordered_map<Type, Archetype*, SetHash, SetEqual> archetype_index;
    std::unordered_map<ComponentID, ArchetypeMap> component_index;
    std::unordered_map<ComponentID, size_t> component_sizes;
    std::unordered_map<std::string, ComponentID> component_names;
    std::unordered_map<size_t, ComponentID> component_ids;
    std::unordered_map<ComponentID, ClassFunctions> functions;
    int threadCount;

    Archetype* getArchetype(const Type& type);

    void moveEntityArchetype(EntityID entity, Archetype* new_archetype);

    bool hasComponent(EntityID entity, ComponentID component);

    bool hasComponent(EntityID entity, const std::string& component);

    void* getComponent(EntityID entity, ComponentID component);

    void* getComponent(EntityID entity, const std::string& component);

    void* addComponent(EntityID entity, ComponentID component);

    void* addComponent(EntityID entity, const std::string& component);

    void removeComponent(EntityID entity, ComponentID component);

    void removeComponent(EntityID entity, const std::string& component);

    Entity entity();

    Entity get(EntityID entity);

    ComponentID component(const std::string& component, size_t size, ClassFunctions functions);

    template<typename T>
    ComponentID component(const std::string& component);

    ComponentID getComponentID(const std::string& component);

    std::string getComponentName(ComponentID component);

    template<typename Args>
    void parallelEach(ComponentID component, std::function<void(Args*)> func);

    template<typename Args>
    void parallelEach(const std::string& component, std::function<void(Args*)> func);

    template<typename Args>
    void parallelEach(ComponentID component, std::function<void(Args*, Entity&)> func);

    template<typename Args>
    void parallelEach(const std::string& component, std::function<void(Args*, Entity&)> func);

    template<typename T>
    void parallelEach(std::function<void(T*)> func);

    template<typename T>
    void parallelEach(std::function<void(T*, Entity&)> func);

    void parallelEach(ComponentID component, std::function<void(void*)> func);

    void parallelEach(ComponentID component, std::function<void(void*, Entity&)> func);

    void parallelEach(const std::string& component, std::function<void(void*)> func);

    void parallelEach(const std::string& component, std::function<void(void*, Entity&)> func);

    void foreach(const std::vector<ComponentID>& components, std::function<void(std::vector<void*>)> func);

    template<typename...Args, typename Func>
    void each(const std::vector<ComponentID>& components, Func func);

    template<typename...Args, typename Func>
    void each(Func func);

    void setThreadCount(int count);

    unsigned int getMaxThreadCount();
};

#endif //POMEGRANATE_ENGINE_CORE_H
