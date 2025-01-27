#include "component.h"

std::unordered_map<ComponentID, ClassFunctions> Component::components;
std::unordered_map<std::string, ComponentID> Component::component_names;
std::unordered_map<size_t, ComponentID> Component::component_types;

std::unordered_map<ComponentID, ComponentList> Component::component_lists;

Component::Component() {

}

size_t Component::addComponent(ComponentID component, void *data) {
    size_t loc = component_lists[component].add();
    void *dest = component_lists[component].get(loc);
    memcpy(dest, data, component_lists[component].element_size);
    return loc;
}

void *Component::getComponent(ComponentID component, size_t row) {
    if (component_lists[component].has(row)) {
        return component_lists[component].get(row);
    }
    return nullptr;
}

ComponentList::ComponentList() {
    this->element_size = 0;
    this->count = 0;
    this->capacity = 0;
    this->elements = nullptr;
    this->occupied = nullptr;
}

ComponentList::ComponentList(ComponentID component, size_t component_size) {
    this->element_size = component_size;
    this->count = 0;
    this->capacity = 0;
    this->elements = nullptr;
    this->occupied = nullptr;
    this->component = component;
}

void ComponentList::resize(size_t new_size) {
    if (elements == nullptr) {
        elements = malloc(element_size * new_size);
        occupied = (bool *) malloc(sizeof(bool) * new_size);
        //Mark all slots as unoccupied
        for (size_t i = 0; i < new_size; i++) {
            occupied[i] = false;
        }
        return;
    }
    elements = realloc(elements, element_size * new_size);
    occupied = (bool *) realloc(occupied, sizeof(bool) * new_size);
    //Mark all new slots as unoccupied
    for (size_t i = count; i < new_size; i++) {
        occupied[i] = false;
    }
}

size_t ComponentList::add() {
    if (count + 1 >= capacity) {
        capacity = count + 1;
        resize(capacity);
        //Mark the new slot as occupied
        occupied[count] = true;
        return count++;
    } else {
        //Find empty slot
        for (size_t i = 0; i < capacity; i++) {
            if (!occupied[i]) {
                occupied[i] = true;
                count++;
                return i;
            }
        }
    }
    throw std::runtime_error("No empty slots found!");
}

void *ComponentList::get(size_t i) const {
    return (void *) ((char *) elements + element_size * i);
}

void ComponentList::remove(size_t i) {
    if (i >= capacity || !occupied[i]) {
        throw std::runtime_error("Index out of bounds!");
    }
    occupied[i] = false;
    count--;
    //0 the memory
    memset((char *) elements + element_size * i, 0, element_size);
}

bool ComponentList::has(size_t i) const {
    return occupied[i];
}

void Component::callUpdate(ComponentID component) {
    for (size_t i = 0; i < component_lists[component].count; i++) {
        if (component_lists[component].occupied[i]) {
            void *ptr = component_lists[component].get(i);
            ((Component *) ptr)->update();
        }
    }
}

void Component::callDraw(ComponentID component) {
    for (size_t i = 0; i < component_lists[component].count; i++) {
        if (component_lists[component].occupied[i]) {
            void *ptr = component_lists[component].get(i);
            ((Component *) ptr)->draw();
        }
    }
}

void Component::callUpdate() {
    for (auto &component: components) {
        callUpdate(component.first);
    }
}

void Component::callDraw() {
    for (auto &component: components) {
        callDraw(component.first);
    }
}