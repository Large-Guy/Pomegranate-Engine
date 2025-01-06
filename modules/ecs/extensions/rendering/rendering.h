#ifndef POMEGRANATE_ENGINE_ECS_RENDERING_H
#define POMEGRANATE_ENGINE_ECS_RENDERING_H

#include "mesh_instance.h"
#include "camera3d.h"
#include "camera2d.h"
#include "sprite.h"
#include "ecs/extensions/common/common.h"

namespace Extensions::Rendering {
    ComponentID MESH_INSTANCE;
    ComponentID CAMERA_3D;
    ComponentID CAMERA_2D;
    ComponentID SPRITE;

    void init() {
        MESH_INSTANCE = Component::create<MeshInstance>("MeshInstance");
        CAMERA_3D = Component::create<Camera3D>("Camera3D");
        CAMERA_2D = Component::create<Camera2D>("Camera2D");
        SPRITE = Component::create<Sprite>("Sprite");
    }

    void render3D()
    {
        Camera3D* camera = nullptr;
        Entity camEntity = Camera3D::getMain();
        if(camEntity != NULL_ENTITY && camEntity.has<Camera3D>())
        {
            camera = camEntity.get<Camera3D>();
        }
        else
        {
            Debug::Log::warn("No main camera!");
            return;
        }

        Matrix4x4 view = Matrix4x4::identity().translate(Transform3D::getPosition(camEntity)).rotate(Transform3D::getRotation(camEntity));
        Matrix4x4 projection = camera->getProjectionMatrix();

        ECS::each<MeshInstance>(MESH_INSTANCE, [&](MeshInstance* meshInstance, Entity& entity){
            if(!entity.has<Transform3D>())
                return;

            ShaderBase* shader = nullptr;
            if(meshInstance->shader != nullptr)
            {
                shader = meshInstance->shader;
            }
            else
            {
                Debug::Log::warn("No shader for mesh instance!");
                return;
            }

            Vector4 color = {1.0f, 1.0f, 1.0f, 1.0f};
            bool hasColor = entity.has<Color>();
            if(hasColor)
            {
                color = entity.get<Color>()->color;
            }

            Matrix4x4 model = Transform3D::getMatrix(entity);

            Window::getCurrent()->draw.shader(shader);
            shader->setUniform("projection", projection);
            shader->setUniform("view", view);
            shader->setUniform("model", model);
            if(hasColor) shader->setUniform("tint", color);
            Window::getCurrent()->draw.mesh(meshInstance->mesh);
        });
    }

    void render2D()
    {
        Camera2D* camera = nullptr;
        Entity camEntity = Camera2D::getMain();
        if(camEntity != NULL_ENTITY && camEntity.has<Camera2D>())
        {
            camera = camEntity.get<Camera2D>();
        }
        else
        {
            Debug::Log::warn("No main camera!");
            return;
        }

        Matrix4x4 view = Matrix4x4::identity().translate(Transform2D::getPosition(camEntity)).rotateZ(Transform2D::getRotation(camEntity));
        Matrix4x4 projection = camera->getProjectionMatrix();

        ECS::each<MeshInstance>(MESH_INSTANCE, [&](MeshInstance* meshInstance, Entity& entity){
            if(!entity.has<Transform2D>())
                return;

            ShaderBase* shader = nullptr;
            if(meshInstance->shader != nullptr)
            {
                shader = meshInstance->shader;
            }
            else
            {
                Debug::Log::warn("No shader for mesh instance!");
                return;
            }

            Vector4 color = {1.0f, 1.0f, 1.0f, 1.0f};
            bool hasColor = entity.has<Color>();
            if(hasColor)
            {
                color = entity.get<Color>()->color;
            }

            Texture2D* texture = nullptr;
            bool hasSprite = entity.has<Sprite>();
            if(hasSprite)
            {
                texture = entity.get<Sprite>()->texture;
            }

            Matrix4x4 model = Transform2D::getMatrix(entity);

            Window::getCurrent()->draw.shader(shader);
            Matrix4x4 proj = Matrix4x4::identity();
            Vector2 a = Window::getCurrent()->getSize() / -2.0f / camera->zoom;
            Vector2 b = Window::getCurrent()->getSize() / 2.0f / camera->zoom;
            proj.x.x = 2.0f / (b.x - a.x);
            proj.y.y = 2.0f / (b.y - a.y);
            proj.x.w = -(b.x + a.x) / (b.x - a.x);
            proj.y.w = -(b.y + a.y) / (b.y - a.y);
            shader->setUniform("projection", proj);
            shader->setUniform("view", view);
            shader->setUniform("model", model);
            if(hasColor) shader->setUniform("tint", color);
            else shader->setUniform("tint", Vector4::one);
            if(hasSprite)
            {
                shader->setUniform("useTexture",true);
                shader->setUniform("texture",0);
            }
            else
            {
                shader->setUniform("useTexture",false);
            }
            Window::getCurrent()->draw.mesh(meshInstance->mesh);
        });
    }
}

#endif //POMEGRANATEENGINE_RENDERING_H
