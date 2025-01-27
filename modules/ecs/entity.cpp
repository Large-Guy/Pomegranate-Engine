#include "entity.h"

#include <utility>

EntityRecord::EntityRecord(Archetype* archetype, size_t row) {
    this->archetype = archetype;
    this->row = row;
}

Entity::Entity() {
    this->ecs = nullptr;
    this->id = 0;
}

Entity::Entity(ECS* ecs, EntityID id) {
    this->ecs = ecs;
    this->id = id;
}

Entity::Entity(const Entity& entity) {
    this->ecs = entity.ecs;
    this->id = entity.id;
}

Entity::Entity(const Entity* entity) {
    if (entity != nullptr) {
        this->id = entity->id;
        this->ecs = entity->ecs;
    } else {
        this->id = NULL_ENTITY;
        this->ecs = nullptr;
    }
}

Entity& Entity::operator=(const Entity& entity) {
    this->id = entity.id;
    this->ecs = entity.ecs;
    return *this;
}

Entity& Entity::operator=(const EntityID& entity) {
    this->id = entity;
    return *this;
}

bool Entity::operator==(const Entity& entity) const {
    return id == entity.id && ecs == entity.ecs;
}


Entity::operator EntityID() const {
    return id;
}

bool Entity::exists() const {
    return id != 0;
}

bool Entity::has(ComponentID component) const {
    return ecs->hasComponent(id, component);
}

bool Entity::has(const std::string& component) const {
    return ecs->hasComponent(id, ecs->getComponentID(component));
}

void* Entity::get(ComponentID component) const {
    void* data = ecs->getComponent(id, component);

    return data;
}

void* Entity::get(const std::string& component) const {
    return ecs->getComponent(id, ecs->getComponentID(component));
}

void* Entity::add(ComponentID component) const {
    return ecs->addComponent(id, component);
}

void* Entity::add(const std::string& component) const {
    return ecs->addComponent(id, ecs->getComponentID(component));
}

void Entity::remove(ComponentID component) const {
    ecs->removeComponent(id, component);
}

void Entity::remove(const std::string& component) const {
    ecs->removeComponent(id, ecs->getComponentID(component));
}

Type Entity::getType() const {
    return ecs->entity_index[id]->archetype->type;
}

void Entity::destroy() {
    //We have to delete all the components
    EntityRecord* record = ecs->entity_index[id];
    Archetype* archetype = record->archetype;
    Debug::AssertIf::isNull(archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");
    for (auto& list: archetype->components) {
        void* data = list.get(record->row);
        if (ecs->functions.find(list.component) != ecs->functions.end()) {
            if (ecs->functions[list.component].destructor != nullptr)
                ecs->functions[list.component].destructor(data);
        }
    }
    archetype->removeRow(record->row);
    ecs->entity_index.erase(id);
    delete record;
    id = NULL_ENTITY;
}

void Entity::serialize(Archive& archive) const {
    if (id == NULL_ENTITY) {
        return;
    }

    EntityRecord* record = ecs->entity_index[id];
    Archetype* archetype = record->archetype;
    Debug::AssertIf::isNull(archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");

    for (auto& list: archetype->components) {
        void* componentData = list.get(record->row);
        archive << list.component;
        Archive component{};
        ecs->functions[list.component].serialize(component, componentData);
        archive << component;
    }
}

void Entity::deserialize(Archive& archive) {
    while (!archive.isEnd()) {
        ComponentID component;
        archive >> component;
        Archive component_archive;
        archive >> component_archive;
        void* data = ecs->addComponent(id, component);
        void* reflectable = (Reflectable*) data;
        ecs->functions[component].deserialize(component_archive, reflectable);
    }
}
