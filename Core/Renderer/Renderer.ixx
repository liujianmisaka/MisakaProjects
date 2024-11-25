module;

#include <glm/glm.hpp>
#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>

export module Misaka.Core.Renderer.Renderer;

import <cstdint>;
import <memory>;
import Misaka.Core.Renderer.RenderCommand;
import Misaka.Core.Renderer.IndexBuffer;
import Misaka.Core.Renderer.VertexBuffer;
import Misaka.Core.Renderer.VertexLayout;
import Misaka.Core.Renderer.Shader;
import Misaka.Core.Component.WindowDataComponent;

namespace Misaka::Core::Renderer {

export class Renderer {
public:
    static void Init() {
        RenderCommand::Init();
    }
    static void Shutdown() {
        RenderCommand::Shutdown();
    }

    static void OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetBackBufferSize(width, height);
    }

    static void BeginScene(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, uint8_t viewId = 0) {
        RenderCommand::SetViewTransform(viewMatrix, projectionMatrix, viewId);
    }
    static void EndScene() {};

    static void Submit(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<Shader> shader,
                       uint8_t viewId = 0) {
        RenderCommand::SubmitIndex(vertexBuffer, indexBuffer, shader, viewId);
    }

    static void DrawFrame() {
        RenderCommand::DrawFrame();
    }
};

} // namespace Misaka::Core::Renderer