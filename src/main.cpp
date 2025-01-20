#include <utility>
#include <core/core.h>
#include <ecs/ecs.h>
#include <events/events.h>
#include <ecs/extensions/common/common.h>
#include <ecs/extensions/rendering/rendering.h>
#include <graphics/opengl/graphics.h>
#include <input/input.h>
#include <math/geometry/geometry.h>
#include "lua/lua_state.h"
#include "lua/debug.h"
#include "lua/events.h"
#include "lua/ecs.h"

void testFunc() {
    Debug::Log::info("Hello World!");
}

int main() {

#pragma region Events
    const EventID DRAW = Event::create("@draw");
    const EventID UPDATE = Event::create("@update");
#pragma endregion

#pragma region EcsExtensions
    Extensions::Common::init();
    Extensions::Rendering::init();
    ECS::setThreadCount(8);
#pragma endregion

#pragma region GraphicsInitialization
    Graphics::getInstance();

    Window window{};

    window.setTitle("Pomegranate Engine - OpenGL");
    window.setSize(800, 600);
    window.show();

    Mesh<Vertex3D, unsigned int> sphere = Mesh<Vertex3D,unsigned int>::sphere(0.5f, 8, 8);

    Mesh<Vertex2D, unsigned int> quad = Mesh<Vertex2D, unsigned int>::quad(Vector2::one);

    Surface2D s_pomegranate("assets/graphics/textures/pomegranate.png", "pomegranate");
    Surface2D s_pomegranate_normal("assets/graphics/textures/pomegranate_n.png", "pomegranate_normal");
    Texture2D t_pomegranate(&s_pomegranate);
    Texture2D t_pomegranate_normal(&s_pomegranate_normal);

#pragma endregion

#pragma region Shader
    File vertexFile("assets/graphics/shaders/opengl/shader.vert");
    vertexFile.open();
    File fragmentFile("assets/graphics/shaders/opengl/shader.frag");
    fragmentFile.open();

    RenderInfo renderInfo = {
            .renderMode = RENDER_MODE_FILL,
            .cullMode = CULL_MODE_BACK,
            .topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED,
            .depthMode = DEPTH_MODE_LESS
    };

    Shader<Vertex3D> shader(vertexFile.readText().c_str(), fragmentFile.readText().c_str(), renderInfo);

    File vertexFile2D("assets/graphics/shaders/opengl/sprite2d.vert");
    vertexFile2D.open();
    File fragmentFile2D("assets/graphics/shaders/opengl/sprite2d.frag");
    fragmentFile2D.open();

    RenderInfo renderInfo2d = {
            .renderMode = RENDER_MODE_FILL,
            .cullMode = CULL_MODE_BACK,
            .topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED,
            .depthMode = DEPTH_MODE_NEVER,
            .alphaMode = ALPHA_MODE_BLEND
    };

    Shader<Vertex2D> shader2d(vertexFile2D.readText().c_str(), fragmentFile2D.readText().c_str(), renderInfo2d);

#pragma endregion

#pragma region InputManagement
    InputManager inputManager(&window);

    auto& exit = inputManager.addButtonAlias("exit", Keyboard::KEY_ESCAPE, Gamepad::BUTTON_START);
    exit.onPressed(Function::create<void>([](){
        Debug::Log::info("Exiting...");
        Window::getCurrent()->close();
    }));

    auto& forward = inputManager.addAxisAlias("forward",
                                              Axis(Keyboard::KEY_W, Keyboard::KEY_S),
                                              Axis(Gamepad::AXIS_RIGHT_Y)
                                              );

    Event::on("@forward-changed", Function::create<void, float>([](float position){
        Camera3D::getMain().get<Transform3D>()->position += Transform3D::getForward(Camera3D::getMain()) * position;
    }));

#pragma endregion

    Entity e_camera2d = Entity::create();
    e_camera2d.add<Transform2D>();
    e_camera2d.add<Camera2D>();
    Debug::Log::info("Camera Zoom: ",e_camera2d.get<Camera2D>()->zoom);
    Camera2D::setMain(e_camera2d);

    Entity e_sprite_shadow = Entity::create();
    e_sprite_shadow.add<Transform2D>();
    auto* instance2d = e_sprite_shadow.add<MeshInstance>();
    instance2d->mesh = &quad;
    instance2d->shader = &shader2d;
    e_sprite_shadow.add<Color>()->color = {0.0f,0.0f,0.0f,0.75f};
    auto* sprite = e_sprite_shadow.add<Sprite>();
    sprite->texture = &t_pomegranate;
    //sprite->normalMap = &t_pomegranate_normal;
    sprite->normalStrength = 1.0f;
    sprite->zIndex = 1;

    Entity e_sprite = Entity::create();
    e_sprite.add<Transform2D>();
    instance2d = e_sprite.add<MeshInstance>();
    instance2d->mesh = &quad;
    instance2d->shader = &shader2d;
    e_sprite.add<Color>()->color = {1.0f,1.0f,1.0f,1.0f};
    sprite = e_sprite.add<Sprite>();
    sprite->texture = &t_pomegranate;
    //sprite->normalMap = &t_pomegranate_normal;
    sprite->normalStrength = 1.0f;


    //Event::on(DRAW, Function::create<void>(Extensions::Rendering::render3D));
    Event::on(DRAW, Function::create<void>(Extensions::Rendering::render2D));
    Event::on(UPDATE, Function::create<void,float>([](float deltaTime){
        InputManager* inputManager = Window::getCurrent()->getInputManager();
        Debug::Log::info(1.0/deltaTime);
    }));

    float deltaTime = 0.016f;
    float lastFrame = 0.0f;

    float time = 0.0f;

    while(window.isOpen()) {
        window.poll();
        inputManager.update();

        time += deltaTime;

        Event::emit(UPDATE, deltaTime);

        e_sprite.get<Transform2D>()->position = Vector2::zero;
        e_sprite.get<Transform2D>()->rotation = time;
        e_sprite.get<Transform2D>()->scale = Vector2::one * 256.0f;

        e_sprite_shadow.get<Transform2D>()->position = Vector2(1.0,-1.0) * 16.0f;
        e_sprite_shadow.get<Transform2D>()->rotation = time;
        e_sprite_shadow.get<Transform2D>()->scale = Vector2::one * 256.0f;

        window.draw.begin();

        window.draw.clear({0.2,0.2,0.2,1.0});

        Event::emit(DRAW);

        window.draw.end();

        deltaTime = (float)glfwGetTime() - lastFrame;
        lastFrame = (float)glfwGetTime();
    }

    return 0;
}