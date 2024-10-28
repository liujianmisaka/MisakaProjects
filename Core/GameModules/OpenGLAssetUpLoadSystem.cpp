module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

module Misaka.Core.GameModule.OpenGLAssetUpLoadSystem;

import Misaka.Core.Context.Context;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Entity.MisakaEntity;

namespace Misaka::Core::GameModules {

static Component::RenderComponent& CreateRenderComponent(Component::MeshComponent &mesh, Component::RenderComponent &renderComponent);

void OpenGLAssetUpLoadSystem::Excute() {
    auto &registry = Context::Context::Instance().gameRoomContext.Registry;
    for (auto entity : registry->view<Component::MeshComponent>()) {
        Entity::MisakaEntity misakaEntity = Entity::MisakaEntity(entity, registry);

        auto &meshComponent             = misakaEntity.GetComponent<Component::MeshComponent>();
        auto &renderComponent           = misakaEntity.GetComponent<Component::RenderComponent>();
        renderComponent.shaderProgramID = Context::Context::Instance().graphicsContext.CommonShaders[Context::ShaderType::Base];

        CreateRenderComponent(meshComponent, renderComponent);
    }
}

static Component::RenderComponent& CreateRenderComponent(Component::MeshComponent &mesh, Component::RenderComponent &renderComponent) {
    unsigned int vertexArray  = 0;
    unsigned int vertexBuffer = 0;
    unsigned int indexBuffer  = 0;

    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);

    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)12);
    glEnableVertexAttribArray(1);

    renderComponent.vertexArrayID  = vertexArray;
    renderComponent.vertexBufferID = vertexBuffer;
    renderComponent.indexBufferID  = indexBuffer;
    renderComponent.indexCount     = mesh.indices.size();

    return renderComponent;
}

} // namespace Misaka::Core::GameModules