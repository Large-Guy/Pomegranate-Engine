#include "archetype.h"

Archetype* Archetype::addComponent(ComponentID component) {
    if (edges.find(component) != edges.end()) {
        ArchetypeEdge& edge = edges[component];
        if (edge.add != nullptr) {
            return edge.add;
        } else {
            Type new_type = type;
            type.insert(component);
            edge.add = ecs->getArchetype(type);
            return edge.add;
        }
    } else {
        Type new_type = type;
        new_type.insert(component);
        ArchetypeEdge& edge = edges[component];
        edge.add = ecs->getArchetype(new_type);
        return edge.add;
    }
}

Archetype* Archetype::removeComponent(ComponentID component) {
    if (edges.find(component) != edges.end()) {
        ArchetypeEdge& edge = edges[component];
        if (edge.remove != nullptr) {
            return edge.remove;
        } else {
            Type new_type = type;
            new_type.erase(component);
            edge.remove = ecs->getArchetype(new_type);
            return edge.remove;
        }
    } else {
        Type new_type = type;
        new_type.erase(component);
        ArchetypeEdge& edge = edges[component];
        edge.remove = ecs->getArchetype(new_type);
        return edge.remove;
    }
}

void Archetype::removeRow(size_t row) {
    for (auto& component: components) {
        component.remove(row);
    }
}