#ifndef POMEGRANATE_ENGINE_ECS_CORE_IMPL_H
#define POMEGRANATE_ENGINE_ECS_CORE_IMPL_H

#include <ecs/ecs.h>

template<typename T>
ComponentID ECS::component(const std::string& component) {
    ComponentID id = this->component(component, sizeof(T), ClassFunctions{
            _constructor<T>,
            _destructor<T>,
            _copy<T>,
            _move<T>,
            _serialize<T>,
            _deserialize<T>
    });
    ECS::component_ids[typeid(T).hash_code()] = id;
    return id;
}

template<typename Args>
void ECS::parallelEach(ComponentID component, std::function<void(Args*)> func) {
    ThreadPool<void, Args*> pool{};
    pool.start(threadCount);

    for (auto archetype: ECS::component_index[component]) {
        ArchetypeRecord& record = archetype.second;
        for (size_t i = 0; i < record.archetype->components[record.column].count; i++) {
            //Call the function
            pool.queue(func, (Args*) record.archetype->components[record.column].get(i));
        }
    }
    pool.finish();
}

template<typename Args>
void ECS::parallelEach(const std::string& component, std::function<void(Args*)> func) {
    parallelEach<Args>(getComponentID(component), func);
}

template<typename Args>
void ECS::parallelEach(ComponentID component, std::function<void(Args*, Entity&)> func) {
    ThreadPool<void, Args*, Entity&> pool{};
    pool.start(threadCount);
    for (auto archetype: ECS::component_index[component]) {
        ArchetypeRecord& record = archetype.second;
        for (size_t i = 0; i < record.archetype->components[record.column].count; i++) {
            //Call the function
            Entity entity(this, record.archetype->entities[i]);
            pool.queue(func, (Args*) record.archetype->components[record.column].get(i), entity);
        }
    }
    pool.finish();
}

template<typename Args>
void ECS::parallelEach(const std::string& component, std::function<void(Args*, Entity&)> func) {
    parallelEach(getComponentID(component), func);
}

template<typename T>
void ECS::parallelEach(std::function<void(T*)> func) {
    parallelEach<T>(ECS::component_ids[typeid(T).hash_code()], func);
}

template<typename T>
void ECS::parallelEach(std::function<void(T*, Entity&)> func) {
    parallelEach<T>(ECS::component_ids[typeid(T).hash_code()], func);
}

template<typename Args>
void ECS::each(ComponentID component, std::function<void(Args*)> func) {
    for (auto archetype: ECS::component_index[component]) {
        ArchetypeRecord& record = archetype.second;
        for (size_t i = 0; i < record.archetype->components[record.column].count; i++) {
            //Call the function
            func((Args*) record.archetype->components[record.column].get(i));
        }
    }
}

template<typename Args>
void ECS::each(const std::string& component, std::function<void(Args*)> func) {
    each(getComponentID(component), func);
}

template<typename Args>
void ECS::each(ComponentID component, std::function<void(Args*, Entity&)> func) {
    for (auto archetype: ECS::component_index[component]) {
        ArchetypeRecord& record = archetype.second;
        for (size_t i = 0; i < record.archetype->components[record.column].count; i++) {
            //Call the function
            Entity entity(this, record.archetype->entities[i]);
            func((Args*) record.archetype->components[record.column].get(i), entity);
        }
    }
}

template<typename Args>
void ECS::each(const std::string& component, std::function<void(Args*, Entity&)> func) {
    each(getComponentID(component), func);
}

#endif //POMEGRANATE_ENGINE_ECS_IMPL_H
