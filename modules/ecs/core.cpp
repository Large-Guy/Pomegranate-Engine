#include "core.h"

#include "entity.h"

Archetype* ECS::getArchetype(const Type& type) {
    if(archetype_index.find(type) == archetype_index.end())
    {
        auto* archetype = new Archetype();
        archetype->ecs = this;
        archetype->type = type;
        archetype->id = archetype_index.size();
        archetype_index[type] = archetype;
        for(auto c : type)
        {
            archetype->components.emplace_back(c,component_sizes[c]);
            component_index[c][archetype->id] = {archetype->components.size()-1,archetype};
        }
    }
    return archetype_index[type];
}

void ECS::moveEntityArchetype(EntityID entity, Archetype *new_archetype) {
    EntityRecord* record = entity_index[entity];
    Archetype* old_archetype = record->archetype;
    Debug::AssertIf::isNull(old_archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");
    if(old_archetype == new_archetype)
    {
        return;
    }
    int row = 0;
    for(auto& list : new_archetype->components)
    {
        row = list.add();
    }
    new_archetype->entities[row] = entity;
    for(auto& list : record->archetype->components)
    {
        if(new_archetype->type.count(list.component) == 0)
        {
            continue;
        }

        void* data_loc = list.get(record->row);
        ComponentList& new_list = new_archetype->components[component_index[list.component][new_archetype->id].column];
        void* new_data_loc = new_list.get(row);
        if(functions.find(list.component) != functions.end())
        {
            if(functions[list.component].copy != nullptr)
            {
                functions[list.component].copy(new_data_loc,data_loc);
            }
            else
            {
                memcpy(new_data_loc,data_loc,list.element_size);
            }
        }
        list.remove(record->row);
    }
    record->archetype->entities.erase(record->row);
    record->archetype = new_archetype;
    record->row = row;
}

bool ECS::hasComponent(EntityID entity, ComponentID component) {
    if(component_index.find(component) == component_index.end())
    {
        return false;
    }
    EntityRecord* record = entity_index[entity];
    Archetype* archetype = record->archetype;
    Debug::AssertIf::isNull(archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");
    ArchetypeMap& archetype_map = component_index[component];
    return archetype_map.count(archetype->id) != 0;
}

bool ECS::hasComponent(EntityID entity, const std::string &component) {
    if(component_names.find(component) == component_names.end())
    {
        return false;
    }
    return hasComponent(entity,getComponentID(component));
}

void* ECS::getComponent(EntityID entity, ComponentID component) {
    EntityRecord* record = entity_index[entity];
    Archetype* archetype = record->archetype;
    Debug::AssertIf::isNull(archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");
    ArchetypeMap& archetypes = component_index[component];
    if(archetypes.count(archetype->id) == 0)
    {
        return nullptr;
    }

    ArchetypeRecord& a_record = archetypes[archetype->id];
    return archetype->components[a_record.column].get(record->row);
}

void ECS::removeComponent(EntityID entity, ComponentID component) {
    EntityRecord* record = entity_index[entity];
    Archetype* archetype = record->archetype;
    Debug::AssertIf::isNull(archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");
    Archetype* next = archetype->removeComponent(component);
    moveEntityArchetype(entity, next);
}

void ECS::removeComponent(EntityID entity, const std::string &component) {
    removeComponent(entity,getComponentID(component));
}

void* ECS::getComponent(EntityID entity, const std::string &component) {
    return getComponent(entity,getComponentID(component));
}

void* ECS::addComponent(EntityID entity, ComponentID component) {
    EntityRecord* record = entity_index[entity];
    Archetype* archetype = record->archetype;
    Debug::AssertIf::isNull(archetype, "Somethings gone wrong. Most likely an engine bug. Sorry!");
    Archetype* next = archetype->addComponent(component);
    moveEntityArchetype(entity, next);
    void* data = getComponent(entity,component);
    if(functions.find(component) != functions.end())
    {
        if(functions[component].constructor != nullptr)
            functions[component].constructor(data);
    }
    return data;
}

void* ECS::addComponent(EntityID entity, const std::string &component) {
    return addComponent(entity,getComponentID(component));
}

Entity ECS::entity()
{
    Entity entity;
    entity.id = entity_index.size() + 1;
    entity.ecs = this;
    entity_index[entity.id] = new EntityRecord{getArchetype({}),0};
    return entity;
}

ComponentID ECS::component(const std::string& component, size_t size, ClassFunctions functions) {
    ComponentID id = component_sizes.size();
    component_sizes[id] = size;
    component_names[component] = id;
    this->functions[id] = std::move(functions);
    return id;
}

ComponentID ECS::getComponentID(const std::string &component) {
    if(component_names.find(component) == component_names.end())
    {
        throw std::runtime_error("Component \"" + component + "\" not found!");
    }
    return component_names[component];
}

std::string ECS::getComponentName(ComponentID component) {
    for(auto& pair : component_names)
    {
        if(pair.second == component)
        {
            return pair.first;
        }
    }
    throw std::runtime_error("Component with ID " + std::to_string(component) + " not found!");
}

std::size_t SetHash::operator()(const std::unordered_set<EntityID>& set) const {
    std::size_t hash_value = 0;
    std::hash<EntityID> hasher;

    for (EntityID id : set) {
        hash_value ^= hasher(id) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
    }

    return hash_value;
}

bool SetEqual::operator()(const std::unordered_set<EntityID>& set1, const std::unordered_set<EntityID>& set2) const {
    if (set1.size() != set2.size()) {
        return false;
    }

    for (const EntityID& id : set1) {
        if (set2.find(id) == set2.end()) {
            return false;
        }
    }

    return true;
}

void ECS::setThreadCount(int count) {
    threadCount = count;
}

unsigned int ECS::getMaxThreadCount() {
    return std::thread::hardware_concurrency();
}

void ECS::parallelEach(ComponentID component, std::function<void(void *)> func) {
    ThreadPool<void,void*> pool{};
    pool.start(threadCount);
    for(auto archetype : component_index[component])
    {
        ArchetypeRecord& record = archetype.second;
        for(size_t i = 0; i < record.archetype->components[record.column].count; i++)
        {
            //Call the function
            pool.queue(func,record.archetype->components[record.column].get(i));
        }
    }
    pool.finish();
}

void ECS::parallelEach(const std::string &component, std::function<void(void *)> func) {
    parallelEach(getComponentID(component), func);
}

void ECS::parallelEach(ComponentID component, std::function<void(void *, Entity &)> func) {
    ThreadPool<void,void*,Entity&> pool{};
    pool.start(threadCount);
    for(auto archetype : component_index[component])
    {
        ArchetypeRecord& record = archetype.second;
        for(size_t i = 0; i < record.archetype->components[record.column].count; i++)
        {
            //Call the function
            Entity entity(record.archetype->entities[i]);
            pool.queue(func,record.archetype->components[record.column].get(i),entity);
        }
    }
    pool.finish();
}

void ECS::parallelEach(const std::string &component, std::function<void(void *, Entity &)> func) {
    parallelEach(getComponentID(component), func);
}

void ECS::each(ComponentID component, std::function<void(void *)> func) {
    for(auto archetype : component_index[component])
    {
        ArchetypeRecord& record = archetype.second;
        for(size_t i = 0; i < record.archetype->components[record.column].count; i++)
        {
            //Call the function
            func(record.archetype->components[record.column].get(i));
        }
    }
}

void ECS::each(const std::string &component, std::function<void(void *)> func) {
    each(getComponentID(component), func);
}

void ECS::each(ComponentID component, std::function<void(void *, Entity &)> func) {
    for(auto archetype : component_index[component])
    {
        ArchetypeRecord& record = archetype.second;
        for(size_t i = 0; i < record.archetype->components[record.column].count; i++)
        {
            //Call the function
            Entity entity(record.archetype->entities[i]);
            func(record.archetype->components[record.column].get(i),entity);
        }
    }
}

void ECS::each(const std::string &component, std::function<void(void *, Entity &)> func) {
    each(getComponentID(component), func);
}
