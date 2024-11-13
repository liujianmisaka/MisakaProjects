module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module Misaka.Core.GameModule.AssetUpLoadSystem;

import Misaka.Core.GameModule.Interface.IExcuteSystem;
import Misaka.Core.Context.Context;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Renderer.VertexBuffer;
import Misaka.Core.Renderer.IndexBuffer;
import Misaka.Core.Renderer.VertexLayout;

namespace Misaka::Core::GameModules {

export class AssetUpLoadSystem : public IExcuteSystem {
public:
    virtual ~AssetUpLoadSystem() = default;
    virtual void Excute() override {
        auto &registry = Context::Context::Instance().gameRoomContext.Registry;
        for (auto entity : registry->view<Component::MeshComponent>()) {
            Entity::MisakaEntity misakaEntity = Entity::MisakaEntity(entity, registry);

            auto &meshComponent             = misakaEntity.GetComponent<Component::MeshComponent>();
            auto &renderComponent           = misakaEntity.GetComponent<Component::RenderComponent>();
            renderComponent.shaderProgramID = Context::Context::Instance().graphicsContext.CommonShaders[Context::ShaderType::Base];

            CreateRenderComponent(meshComponent, renderComponent);
        }
    }

private:
    Component::RenderComponent &CreateRenderComponent(Component::MeshComponent &mesh, Component::RenderComponent &renderComponent) {
        // TODO: temp
        auto layout = Renderer::VertexLayout::Create();
        layout.AddPosition();
        layout.AddColor();

        for (auto &meshData : mesh.meshes) {
            auto vertexBuffer = Renderer::VertexBuffer::Create(meshData->vertices.data(), layout);
            auto indexBufer   = Renderer::IndexBuffer::Create(meshData->indices.data());
        }

        return renderComponent;
    }
};

} // namespace Misaka::Core::GameModules