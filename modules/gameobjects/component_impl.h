template<typename Comp>
ComponentID Component::create(const std::string& name) {
    ComponentID id = components.size();
    component_names[name] = id;
    components[id] = {
            _constructor<Comp>,
            _destructor<Comp>,
            _copy<Comp>,
            _move<Comp>,
            _serialize<Comp>,
            _deserialize<Comp>
    };
    component_lists[id] = ComponentList(id, sizeof(Comp));
    component_types[typeid(Comp).hash_code()] = id;
    return id;
}