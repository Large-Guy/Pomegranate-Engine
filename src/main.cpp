#include <utility>
#include <chrono>
#include <core/core.h>
#include <math/math.h>
#include <graphics/opengl/graphics.h>
#include <input/input.h>
#include <gameobjects/gameobjects.h>

class Transform : public Component {
public:
    Vector3 position = Vector3();
    Vector3 scale = Vector3::one;
    Vector3 rotation = Vector3();

    void start() override {
        Debug::Log::info("Starting Transform");
    }

    void update() override {
        position.x += 0.01f;
        position.y += 0.01f;
        position.z += 0.01f;
    }

    void draw() override {
        //Debug::Log::info("Drawing Transform");
    }
};

int main() {
    const ComponentID TRANSFORM = Component::create<Transform>("Transform");

    auto *gameObject = new GameObject("Player");
    gameObject->addComponent<Transform>();

    auto *transform = gameObject->getComponent<Transform>();

    Debug::Log::info("Component GameObject:", transform->gameObject->getName());
    Debug::Log::info("Position:", transform->position.x, transform->position.y, transform->position.z);
    Debug::Log::info("Scale:", transform->scale.x, transform->scale.y, transform->scale.z);
    Debug::Log::info("Rotation:", transform->rotation.x, transform->rotation.y, transform->rotation.z);


    while (1) {
        Component::callUpdate();
        Component::callDraw();
    }
    return 0;
}