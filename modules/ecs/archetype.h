#ifndef POMEGRANATE_ENGINE_ECS_ARCHETYPE_H
#define POMEGRANATE_ENGINE_ECS_ARCHETYPE_H

#include <unordered_set>
#include <unordered_map>
#include "ecs_typedefs.h"
#include <cstring>
#include "component.h"
#include "core.h"

struct Archetype;

struct ArchetypeRecord {
    size_t column;
    Archetype* archetype;
};

struct ArchetypeEdge {
    Archetype* add;
    Archetype* remove;
};

struct Archetype {
    ArchetypeID id;
    Type type;
    ECS* ecs;
    std::vector<ComponentList> components;
    std::unordered_map<size_t, EntityID> entities;
    std::unordered_map<ComponentID, ArchetypeEdge> edges;

    Archetype* addComponent(ComponentID component);

    Archetype* removeComponent(ComponentID component);

    void removeRow(size_t row);
};

#endif //POMEGRANATE_ENGINE_ARCHETYPE_H
