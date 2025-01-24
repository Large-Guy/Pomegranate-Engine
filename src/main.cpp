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
    Mesh<Vertex2D,uint>* getMesh() {
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

    File vertexFile2D("assets/graphics/shaders/opengl/sprite2d.vert");
    vertexFile2D.open();
    File fragmentFile2D("assets/graphics/shaders/opengl/color.frag");
    fragmentFile2D.open();
    RenderInfo renderInfo2d = {
            .renderMode = RENDER_MODE_FILL,
            .cullMode = CULL_MODE_BACK,
            .topologyMode = TOPOLOGY_MODE_TRIANGLE_INDEXED,
            .depthMode = DEPTH_MODE_NEVER,
            .alphaMode = ALPHA_MODE_BLEND
    };
    Shader<Vertex2D> shader(vertexFile2D.readText().c_str(), fragmentFile2D.readText().c_str(), renderInfo2d);

    Polygon polygon;

    Matrix4x4 ortho = Matrix4x4::orthographic(-400,400,-300,300,-1,1);
    Matrix4x4 view = Matrix4x4::identity();
    Matrix4x4 model = Matrix4x4::identity();

    //Delta time
    auto lastTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f;

    ECS ecs;
    ecs.setThreadCount(4);
    ecs.component<Point>("Point");
    ecs.component<Spring>("Spring");

    //Generate points grid and springs for softbody
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(-100, -100);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(0, -100);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(100, -100);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(100, 0);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(100, 100);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(0, 100);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(-100, 100);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(-100, 0);
        point->position_old = point->position;
    }
    {
        Entity entity = ecs.entity();
        auto point = entity.add<Point>();
        point->position = Vector2(0, 0);
        point->position_old = point->position;
    }

    auto link = [&ecs](int a, int b){
        ecs.entity().add<Spring>(ecs.get(a).get<Point>(),ecs.get(b).get<Point>(),ecs.get(a).get<Point>()->position.distanceTo(ecs.get(b).get<Point>()->position));
    };

    link(1,2);
    link(2,3);
    link(3,4);
    link(4,5);
    link(5,6);
    link(6,7);
    link(7,8);
    link(8,1);
    link(1,9);
    link(2,9);
    link(3,9);
    link(4,9);
    link(5,9);
    link(6,9);
    link(7,9);
    link(8,9);



    float gravity = 9800.0f;

    Point* grabbed = nullptr;

    while(window->isOpen())
    {
        window->poll();
        inputManager.update();
        //Updating

        Vector2 cursor = inputManager.getMouse().getPosition();
        //Convert to world space
        cursor = cursor - Vector2(400,300);
        cursor.y = -cursor.y;

        if(grabbed == nullptr && inputManager.getMouse().getButton(Mouse::BUTTON_LEFT) == BUTTON_PRESSED) {
            ecs.each<Point>("Point", [&](Point *point) {
                if (cursor.distanceTo(point->position) < 50) {
                    std::cout << "Grabbed" << std::endl;
                    grabbed = point;
                }
            });
        }

        if(grabbed != nullptr)
        {
            std::cout << "Held" << std::endl;
            Vector2 direction = cursor.directionTo(grabbed->position);
            grabbed->acceleration += direction * -150000.0f * deltaTime;
        }

        if(inputManager.getMouse().getButton(Mouse::BUTTON_LEFT) == BUTTON_RELEASED)
        {
            grabbed = nullptr;
        }


        //Physics
        ecs.each<Spring>("Spring",[&](Spring* spring){
            auto a = spring->a;
            auto b = spring->b;

            float compression = a->position.distanceTo(b->position) - spring->length;
            float constant = 24000.0f;
            float force = constant * compression * 0.5f;
            float finalForce = force - spring->previousForce * 0.7f;
            spring->previousForce = force;

            Vector2 direction = a->position.directionTo(b->position);

            a->acceleration += direction * finalForce * deltaTime;
            b->acceleration -= direction * finalForce * deltaTime;
        });

        ecs.each<Point>("Point",[&deltaTime,&gravity,&cursor,&inputManager](Point* point){
            point->acceleration += Vector2(0,-gravity) * deltaTime;

            if(point->position.y < -300)
            {
                point->position.y = -300;
            }

            Vector2 velocity = point->position - point->position_old;

            point->position_old = point->position;

            point->position = point->position + velocity + point->acceleration * deltaTime * deltaTime;

            point->acceleration = {};
        });

        //Build the polygon
        polygon.points.clear();

        Point* p1 = nullptr;

        ecs.each<Point>("Point",[&](Point* point){
            if(p1 == nullptr)
            {
                p1 = point;
            }
            polygon.addPoint(point->position);
        });

        //polygon.addPoint(p1->position);

        polygon.generate();

        //Rendering
        window->draw.begin();
        window->draw.clear(Vector4(0.1f,0.1f,0.1f,1.0f));

        window->draw.shader(&shader);
        shader.setUniform("projection",ortho);
        shader.setUniform("view",view);
        shader.setUniform("model",model);
        shader.setUniform("tint",Vector4::one);

        window->draw.mesh(polygon.getMesh());

        window->draw.end();

        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float,std::chrono::seconds::period>(currentTime - lastTime).count();
        lastTime = currentTime;

        window->setTitle("Pomegranate Engine - " + std::to_string(1.0f/deltaTime));
    }

    return 0;
}