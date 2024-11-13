#include <utility>
#include <core/core.h>
#include <ecs/ecs.h>
#include <events/events.h>
#include <ecs/extensions/common/common.h>
#include <graphics/vulkan/graphics.h>
#include <audio/audio.h>
#include <math/geometry/geometry.h>
#include "lua/lua_state.h"
#include "lua/debug.h"
#include "lua/events.h"
#include "lua/ecs.h"



int main() {

//#define GRAPHICS

#ifdef GRAPHICS
    Graphics::getInstance();

    Window window;

    window.setTitle("Pomegranate Engine - Vulkan");
    window.setSize(800, 600);
    window.show();


//region Shader
    auto vertexFile = File("assets/graphics/shaders/shader.vert.spv");
    vertexFile.open();
    auto fragmentFile = File("assets/graphics/shaders/shader.frag.spv");
    fragmentFile.open();

    auto vertexShader = vertexFile.readBuffer();
    auto fragmentShader = fragmentFile.readBuffer();

    RenderInfo renderInfo = {
            .renderMode = RENDER_MODE_FILL,
            .cullMode = CULL_MODE_NONE,
            .topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED
    };

    Shader shader = Shader<Vertex3D>(vertexShader, fragmentShader, renderInfo);

//endregion

//region Model
//RGB triangle model
    List<Vertex3D> vertices = {
            {{-0.5,-0.5,0.5},{0.0,0.0},{0.0,0.0,1.0},{1.0,0.0,0.0}},
            {{0.5,-0.5,0.5},{1.0,0.0},{0.0,0.0,1.0},{0.0,1.0,0.0}},
            {{-0.5,0.5,0.5},{0.0,1.0},{0.0,0.0,1.0},{1.0,1.0,0.0}},
            {{0.5,0.5,0.5},{1.0,1.0},{0.0,0.0,1.0},{0.0,0.0,1.0}}
    };

    List<uint16_t> indices = {
            0, 1, 2,
            2, 1, 3
    };

    Mesh3D* mesh = new Mesh3D(vertices,indices, &shader);
//endregion


    double lastTime = glfwGetTime();
    double deltaTime = 0.0;

    Perspective perspective;

    //For now, we'll just use the identity matrix
    perspective.model = Matrix4x4();
    perspective.view = Matrix4x4();
    perspective.projection = Matrix4x4();


    while(window.isOpen()) {
        window.poll();

        shader._perspectiveSet.set(window._currentFrame,0, perspective);

        window.draw.begin();
        window.draw.clear({0.1, 0.1, 0.1, 1.0});

        window.draw.mesh(*mesh);

        window.draw.end();

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        //Debug::Log::info("FPS: ",1.0/deltaTime);
    }

    delete mesh;

    Debug::Log::info("------------------------------------------------------ Exiting... ------------------------------------------------------");

    return 0;
#else

    /*std::vector<float> samples;
    for(int i = 0; i < 44100; i++) {
        samples.push_back(sin(2 * M_PI * 440 * i / 44100));
    }

    AudioSample sample = AudioSample(samples, 1, 44100);*/

    Audio::getInstance();

    Stream stream = Stream();

    stream.setCustomCallback(Function::create<void,Stream::CallbackInfo>([](Stream::CallbackInfo info) {
        //Generate a sine wave

        for(int i = 0; i < info.frameCount; i++) {
            float left = 0.5f * std::sin((info.time + info.frameDeltaTime * (float)i) * 2.0 * M_PI * 440.0f);
            float right = 0.5f * std::sin((info.time + info.frameDeltaTime * (float)i) * 2.0 * M_PI * 440.0f);

            *info.output++ = left;
            *info.output++ = right;
        }
    }));

    stream.start();

    while (true)
    {

    }

    stream.stop();

    return 0;

#endif
}