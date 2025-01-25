#include <utility>
#include <chrono>
#include <core/core.h>
#include <ecs/ecs.h>
#include <math/math.h>
#include <graphics/opengl/graphics.h>
#include <input/input.h>

class Polygon {
private:
    std::vector<Vertex2D> _vertices{};
    std::vector<uint> _indices{};
    Mesh<Vertex2D,uint>* _mesh = nullptr;
public:
    std::vector<Vector2> points;

    void addPoint(Vector2 point) {
        points.push_back(point);
    }
    void generate()
    {
        delete _mesh;
        _vertices.clear();
        _indices.clear();
        for(auto& point : points)
        {
            _vertices.push_back(Vertex2D{point,Vector2::zero,Vector4::one});
        }
        for(int i = 0; i < points.size() - 1; i++)
        {
            _indices.push_back(0);
            _indices.push_back(i);
            _indices.push_back(i+1);
        }
        _mesh = new Mesh<Vertex2D,uint>(_vertices,_indices);
    }
    Mesh<Vertex2D,uint32_t>* getMesh() {
        return _mesh;
    }
};

struct PointLink;

struct Point {
    Vector2 position = Vector2::zero;
    Vector2 position_old = Vector2::zero;
    Vector2 acceleration = Vector2::zero;
    float mass = 1.0f;

    void serialize(Archive& archive) {
        archive << position << position_old << acceleration << mass;
    }

    void deserialize(Archive& archive) {
        archive >> position >> position_old >> acceleration >> mass;
    }
};

struct Spring {
    Point* a = nullptr;
    Point* b = nullptr;
    float length = 0.0f;
    float stiffness = 1.0f;

    float previousForce = 0.0f;

    Spring() = default;
    Spring(Point* a, Point* b, float length) : a(a), b(b), length(length) {}

    void serialize(Archive& archive) {
        archive << length << stiffness;
    }

    void deserialize(Archive& archive) {
        archive >> length >> stiffness;
    }
};

int main() {
    auto* window = new Window(800,600,"Pomegranate Engine");
    window->show();

    InputManager inputManager(window);
    Draw draw(window);

    File vertexFile2D("assets/graphics/shaders/opengl/sprite2d.vert");
    vertexFile2D.open();
    File fragmentFile2D("assets/graphics/shaders/opengl/color.frag");
    fragmentFile2D.open();
    RenderInfo renderInfo2d = {
            .renderMode = RENDER_MODE_WIRE_FRAME,
            .cullMode = CULL_MODE_NONE,
            .topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED,
            .depthMode = DEPTH_MODE_NEVER,
            .alphaMode = ALPHA_MODE_BLEND
    };
    Shader<Vertex2D> shader(vertexFile2D.readText().c_str(), fragmentFile2D.readText().c_str(), renderInfo2d);

    Surface2D surface = Surface2D("assets/graphics/textures/pomegranate.png","pomegranate");
    Texture2D texture = Texture2D(&surface);

    Polygon polygon{};

    //Delta time
    auto lastTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f;

    Camera2D camera(Vector2::zero,Vector2(800,600),0,1);

    float gravity = 9800.0f;

    Point* grabbed = nullptr;

    while(window->isOpen())
    {
        window->poll();
        inputManager.update();

        //Rendering
        draw.begin();
        draw.clear(Vector4(0.1f,0.1f,0.1f,1.0f));
        draw.camera(&camera);

        draw.rect(Vector2(0,0),Vector2(256,256),0,Vector4(1,0,0,1));

        draw.line(Vector2(0,0),Vector2(256,0),Vector4(1,0,0,1));
        draw.line(Vector2(0,0),Vector2(0,256),Vector4(0,1,0,1));
        draw.image(&texture,Vector2(0,0),Vector2(256,256),glfwGetTime(),Vector4::one);


        draw.end();

        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float,std::chrono::seconds::period>(currentTime - lastTime).count();
        lastTime = currentTime;

        window->setTitle("Pomegranate Engine - " + std::to_string(1.0f/deltaTime));
    }

    return 0;
}