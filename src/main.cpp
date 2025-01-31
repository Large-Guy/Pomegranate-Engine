#include <ecs/ecs.h>

struct Position {
    int x, y;

    void serialize(Archive& archive) {
        archive << x << y;
    }

    void deserialize(Archive& archive) {
        archive >> x >> y;
    }
};

struct Velocity {
    int x, y;

    void serialize(Archive& archive) {
        archive << x << y;
    }

    void deserialize(Archive& archive) {
        archive >> x >> y;
    }
};

struct Name {
    std::string name;

    void serialize(Archive& archive) {
        archive << name;
    }

    void deserialize(Archive& archive) {
        archive >> name;
    }
};

int main() {
    ECS ecs;

    ComponentID position = ecs.component<Position>("position");
    ComponentID name = ecs.component<Name>("name");
    ComponentID velocity = ecs.component<Velocity>("velocity");

    Entity entity = ecs.entity();

    entity.add<Position>(10, 10);
    entity.add<Velocity>();
    entity.add<Name>("Player");

    entity.get<Position>()->x = 20;

    entity.get<Velocity>()->x = 5;

    entity = ecs.entity();
    entity.add<Position>(10, 10);
    entity.add<Velocity>();
    entity.add<Name>("Enemy");

    entity = ecs.entity();
    entity.add<Position>(10, 10);
    entity.add<Name>("NPC");

    ecs.each<Position, Velocity, Name>([](Position* pos, Velocity* vel, Name* name) {
        pos->x += vel->x;
        pos->y += vel->y;

        std::cout << "Name: " << name->name << std::endl;
        std::cout << "Position: " << pos->x << ", " << pos->y << std::endl;
        std::cout << "Velocity: " << vel->x << ", " << vel->y << std::endl;
    });

    ecs.foreach({position, velocity, name}, [](std::vector<void*> components) {
        Position* pos = (Position*) components[0];
        Velocity* vel = (Velocity*) components[1];
        Name* name = (Name*) components[2];
        pos->x += vel->x;
        pos->y += vel->y;

        std::cout << "Name: " << name->name << std::endl;
        std::cout << "Position: " << pos->x << ", " << pos->y << std::endl;
        std::cout << "Velocity: " << vel->x << ", " << vel->y << std::endl;
    });

    return 0;
}