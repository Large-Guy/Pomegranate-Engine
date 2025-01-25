#ifndef POMEGRANATEENGINE_DRAW_H
#define POMEGRANATEENGINE_DRAW_H
#include <core/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math/math.h>
#include "core.h"
#include "mesh.h"
#include "shader.h"
#include "texture2d.h"
#include "window.h"
#include "vertex2d.h"
#include "camera2d.h"

class Draw {
private:
    TopologyMode _topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED;
    Shader<Vertex2D>* _defaultFill2d;
    Shader<Vertex2D>* _defaultLine2d;
    Mesh<Vertex2D, uint32_t>* _quad;
    Mesh<Vertex2D, uint32_t>* _line;
    Window* _window;
    uint32_t imageIndex;
    Camera2D* _camera2d;
public:
    Draw(Window* window);
    void begin();
    void end();
    void clear(Vector4 color);
    //void buffers(BufferBase<BUFFER_TYPE_VERTEX>* vertexBuffer, BufferBase<BUFFER_TYPE_INDEX>* indexBuffer, ShaderBase* shader);
    void camera(Camera2D* camera);
    void shader(ShaderBase* shader);
    void mesh(MeshBase* mesh);
    void rect(Vector2 position, Vector2 size, float rotation, Vector4 color);
    void line(Vector2 start, Vector2 end, Vector4 color);
    void image(Texture2D* texture, Vector2 position, Vector2 size, float rotation, Vector4 tint);
};


#endif //POMEGRANATEENGINE_DRAW_H
