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
    parallelEach < Args > (getComponentID(component), func);
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
    parallelEach < T > (ECS::component_ids[typeid(T).hash_code()], func);
}

template<typename T>
void ECS::parallelEach(std::function<void(T*, Entity&)> func) {
    parallelEach < T > (ECS::component_ids[typeid(T).hash_code()], func);
}

template<typename... Args, typename Func>
void ECS::each(const std::vector<ComponentID>& components, Func func) {
    for (std::pair<ArchetypeID, ArchetypeRecord> archetype: ECS::component_index[components[0]]) {
        ArchetypeRecord& record = archetype.second;
        //Check if all components are present
        bool allPresent = true;
        for (ComponentID component: components) {
            if (ECS::component_index[component].find(archetype.first) == ECS::component_index[component].end()) {
                allPresent = false;
                break;
            }
        }
        if (!allPresent) {
            continue;
        }
        for (size_t i = 0; i < record.archetype->components[record.column].count; i++) {
            // Retrieve remaining components
            if (!record.archetype->components[0].has(i)) {
                continue;
            }

            int index = 0;
            auto getComponent = [&]() {
                ArchetypeRecord& rec = ECS::component_index[components[index++]][archetype.first];
                return rec.archetype->components[rec.column].get(i);
            };

            // Expand parameter pack for remaining arguments
            func((Args*) getComponent()...);
        }
    }
}


template<typename... Args, typename Func>
void ECS::each(Func func) {
    std::vector<ComponentID> components = {ECS::component_ids[typeid(Args).hash_code()]...};

    for (std::pair<ArchetypeID, ArchetypeRecord> archetype: ECS::component_index[components[0]]) {
        ArchetypeRecord& record = archetype.second;
        //Check if all components are present
        bool allPresent = true;
        for (ComponentID component: components) {
            if (ECS::component_index[component].find(archetype.first) == ECS::component_index[component].end()) {
                allPresent = false;
                break;
            }
        }
        if (!allPresent) {
            continue;
        }
        for (size_t i = 0; i < record.archetype->components[record.column].count; i++) {
            // Retrieve remaining components
            if (!record.archetype->components[0].has(i)) {
                continue;
            }

            int index = 0;
            auto getComponent = [&]() {
                ArchetypeRecord& rec = ECS::component_index[components[index++]][archetype.first];
                return rec.archetype->components[rec.column].get(i);
            };

            // Expand parameter pack for remaining arguments
            func((Args*) getComponent()...);
        }
    }
}


#endif //POMEGRANATE_ENGINE_ECS_IMPL_H
