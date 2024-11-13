module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

module Misaka.Core.GameModule.RenderSystem;

import Misaka.Core.Context.Context;
import Misaka.Core.Component.RenderComponent;

using namespace Misaka::Core::Component;
using namespace Misaka::Core::GameModules;

void RenderSystem::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto& registry = Context::Context::Instance().gameRoomContext.Registry;

    for (auto entity : registry->view<RenderComponent>()) {
        auto& renderComponent = registry->get<RenderComponent>(entity);

        glUseProgram(renderComponent.shaderProgramID);
        glBindVertexArray(renderComponent.vertexArrayID);
        glDrawElements(GL_TRIANGLES, renderComponent.indexCount, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(Context::Context::Instance().graphicsContext.Window);
    glfwPollEvents();
}