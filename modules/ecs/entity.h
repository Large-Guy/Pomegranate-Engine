#ifndef POMEGRANATE_ENGINE_ECS_ENTITY_H
#define POMEGRANATE_ENGINE_ECS_ENTITY_H
#include<string>
#include<unordered_map>
#include<vector>
#include<core/serializable.h>
#include"archetype.h"
#include "ecs_typedefs.h"
#include "component.h"
#include "core.h"

struct EntityRecord
{
    Archetype* archetype;
    size_t row;

    EntityRecord(Archetype* archetype, size_t row);
};

class Entity : public Reflectable
{
public:
    //Static

    EntityID id;
    ECS* ecs;
    Entity();
    Entity(ECS* ecs, EntityID id);
    Entity(const Entity& entity);
    Entity(const Entity* entity);

    Entity& operator=(const Entity& entity);
    Entity& operator=(const EntityID& entity);
    bool operator==(const Entity& entity) const;
    explicit operator EntityID() const;
    bool exists() const;
    [[nodiscard]] bool has(ComponentID component) const;
    [[nodiscard]] bool has(const std::string& component) const;

    template<typename T>
    [[nodiscard]] bool has() const
    {
        return has(ecs->component_ids[typeid(T).hash_code()]);
    }

    [[nodiscard]] void* get(ComponentID component) const;
    [[nodiscard]] void* get(const std::string& component) const;
    template<typename T>
    T* get() const
    {
        return (T*) get(ecs->component_ids[typeid(T).hash_code()]);
    }
    template<typename T>
    T* get(ComponentID component) const
    {
        return (T*) get(component);
    }
    template<typename T>
    T* get(const std::string& component) const
    {
        return (T*) get(component);
    }
    void* add(ComponentID component) const;
    void* add(const std::string& component) const;
    template<typename T, typename... Args>
    T* addNamed(const std::string& component, Args&&... args)
    {
        Debug::AssertIf::isFalse(ecs->component_ids.count(typeid(T).hash_code()),"Component not registered!");
        T* t = (T*) add(component);
        return new (t) T(std::forward<Args>(args)...);
        return t;
    }
    template<typename T, typename... Args>
    T* add(Args&&... args)
    {
        Debug::AssertIf::isFalse(ecs->component_ids.count(typeid(T).hash_code()),"Component not registered!");
        T* t = (T*) add(ecs->component_ids[typeid(T).hash_code()]);
        return new (t) T(std::forward<Args>(args)...);
    }

    void remove(ComponentID component) const;
    void remove(const std::string& component) const;
    [[nodiscard]] Type getType() const;

    void destroy();

    void serialize(Archive& archive) const override;
    void deserialize(Archive& archive) override;
};

template<>
struct std::hash<Entity>
{
    std::size_t operator()(const Entity& entity) const
    {
        return std::hash<EntityID>()(entity.id);
    }
};
#endif //POMEGRANATE_ENGINE_ENTITY_H
