module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <span>
#include <entt/entt.hpp>

export module Misaka.Core.GameModule.AssetUpLoadSystem;

import Misaka.Core.GameModule.Interface.IExcuteSystem;
import Misaka.Core.Context.Context;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Renderer.VertexBuffer;
import Misaka.Core.Renderer.IndexBuffer;
import Misaka.Core.Renderer.VertexLayout;
import Misaka.Core.SingletonManager;
import Misaka.Core.Manager.MeshManager;
import Misaka.Core.Manager.ShaderManager;
import Misaka.Core.Utils.Registry;

namespace Misaka::Core::GameModule {

export class AssetUpLoadSystem : public IExcuteSystem {
public:
    virtual ~AssetUpLoadSystem() = default;
    virtual void Excute() override {
        auto registry = SingletonManager::GetInstance<entt::registry>();

        for (auto entity : registry->view<Component::MeshComponent>()) {
            Entity::MisakaEntity misakaEntity = Entity::MisakaEntity(entity, registry);

            auto &meshComponent   = misakaEntity.GetComponent<Component::MeshComponent>();
            auto &renderComponent = misakaEntity.GetComponent<Component::RenderComponent>();

            auto layout = bgfx::VertexLayout();
            layout.begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float)
                .end();
            auto shader = SingletonManager::GetInstance<Manager::ShaderManager>()->GetShader("base");

            auto meshManager = SingletonManager::GetInstance<Manager::MeshManager>();
            for (auto &name : meshComponent.meshes) {
                auto meshData = meshManager->GetStaticMesh(name);

                for (auto &subMesh : meshData->subMeshes) {
                    auto vertexBuffer =
                        Renderer::VertexBuffer::Create(subMesh.vertices.data(), std::span(subMesh.vertices).size_bytes(), layout);
                    auto indexBuffer = Renderer::IndexBuffer::Create(subMesh.indices.data(), std::span(subMesh.indices).size_bytes());
                    renderComponent.renderDatas.push_back({vertexBuffer, indexBuffer, shader});
                }
            }

            meshComponent.dirty = false;

            misakaEntity.RemoveComponent<Component::MeshComponent>();
        }
    }
};

} // namespace Misaka::Core::GameModule