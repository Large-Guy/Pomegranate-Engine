
#include <utility>
#include <core/core.h>
#include <ecs/ecs.h>
#include <events/events.h>
#include <ecs/extensions/common/common.h>
#include <graphics/vulkan/graphics.h>
#include <math/math.h>

int main() {

#define GRAPHICS

#ifdef GRAPHICS

    Graphics::enableValidationLayers = true;


//region Shader
    auto vertexFile = File("assets/graphics/shaders/shader.vert.spv");
    vertexFile.open();
    auto fragmentFile = File("assets/graphics/shaders/shader.frag.spv");
    fragmentFile.open();

    auto vertexShader = vertexFile.readBuffer();
    auto fragmentShader = fragmentFile.readBuffer();

    RenderInfo renderInfo = {
            .renderMode = RENDER_MODE_FILL,
            .cullMode = CULL_MODE_BACK,
            .topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED
    };

    Shader shader = Shader<Vertex3D>(vertexShader, fragmentShader, renderInfo);
//endregion

//region Model
//RGB triangle model
    List<Vertex3D> vertices = {
            {{-1.0,-1.0,0.0},{0.0,0.0},{0.0,0.0,1.0}},
            {{1.0,-1.0,0.0},{1.0,0.0},{0.0,1.0,0.0}},
            {{-1.0,1.0,0.0},{0.0,1.0},{1.0,0.0,0.0}},
            {{1.0,1.0,0.0},{1.0,1.0},{1.0,1.0,1.0}}
    };

    List<uint16_t> indices = {
            0, 1, 2,
            2, 1, 3
    };

    Mesh3D mesh(vertices,indices, &shader);
//endregion

    Window window;

    window.setTitle("Pomegranate Engine - Vulkan");
    window.setSize(800, 600);
    window.show();

    double lastTime = glfwGetTime();
    double deltaTime = 0.0;

    while(window.isOpen()) {
        window.poll();

        window.draw.begin();
        window.draw.clear({0.0, 0.0, 0.0, 1.0});

        window.draw.mesh(mesh);

        window.draw.end();

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        Debug::Log::info("FPS: ",1.0/deltaTime);
    }

    return 0;
#else

    const EventID function = Event::getEventId("function");

    Event::on(function,[&](float arg){
        Debug::Log::info("Hello, World!",arg);
    });

    Event::call(function,1.0f);

#endif
}