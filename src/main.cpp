#include <utility>
#include <core/core.h>
#include <ecs/ecs.h>
#include <math/math.h>

struct Player
{
    char name[32];
    int health;
    int mana;

    void serialize(Archive& archive)
    {
        //char[] not support
        for(int i = 0; i < 32; i++)
        {
            archive << name[i];
        }
        archive << health << mana;
    }

    void deserialize(Archive& archive)
    {
        for(int i = 0; i < 32; i++)
        {
            archive >> name[i];
        }
        archive >> health >> mana;
    }
};

int main() {
    ECS ecs{};

    ecs.component<Player>("Player");
    ecs.component<Vector2>("Position");

    Entity test = ecs.entity();
    auto* player = test.add<Player>();

    strcpy(player->name,"Test");
    player->health = 100;
    player->mana = 100;

    test.add<Vector2>();
    player = test.get<Player>();
    auto* position = test.get<Vector2>();

    std::cout << player->name << std::endl;
    std::cout << player->health << std::endl;
    std::cout << player->mana << std::endl;

    std::cout << position->x << std::endl;
    std::cout << position->y << std::endl;

    return 0;
}