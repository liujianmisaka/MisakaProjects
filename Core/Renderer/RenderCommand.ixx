module;

#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

export module Misaka.Core.Renderer.RenderCommand;

import <iostream>;
import glm;
import Misaka.Core.CoreConfig;
import Misaka.Core.Renderer.IndexBuffer;
import Misaka.Core.Renderer.VertexBuffer;
import Misaka.Core.Renderer.VertexLayout;
import Misaka.Core.Renderer.Shader;

namespace Misaka::Core::Renderer {

export class RenderCommand {
public:
    static void Init() {
        bgfx::Init init;
        init.type              = bgfx::RendererType::OpenGL;
        init.vendorId          = BGFX_PCI_ID_NVIDIA;
        init.platformData.nwh  = glfwGetWin32Window(CoreConfig::window);
        init.platformData.ndt  = nullptr;
        init.resolution.width  = CoreConfig::windowWidth;
        init.resolution.height = CoreConfig::windowHeight;
        init.resolution.reset  = BGFX_RESET_VSYNC;

        if (!bgfx::init(init)) {
            std::cerr << "Failed to initialize bgfx" << std::endl;
            return;
        }

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDFF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, CoreConfig::windowWidth, CoreConfig::windowHeight);
        bgfx::setState(BGFX_STATE_DEFAULT);
        bgfx::setState(BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS);
    }

    static void Shutdown() {
        bgfx::shutdown();
    }

    static void SubmitIndex(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer,
                            std::shared_ptr<Shader> shader, uint8_t viewId = 0) {
        vertexBuffer->Bind(viewId);
        indexBuffer->Bind();
        bgfx::submit(viewId, shader->GetProgram());
    }

    static void DrawFrame() {
        bgfx::frame();
    }

    static void Clear(uint8_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil) {
        bgfx::setViewClear(_id, _flags, _rgba, _depth, _stencil);
    }

    static void SetViewPort(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t viewId = 0) {
        bgfx::setViewRect(viewId, x, y, width, height);
    }

    // 设置后台缓冲区大小, 用于窗口大小改变时调用
    static void SetBackBufferSize(uint32_t width, uint32_t height) {
        bgfx::reset(width, height, BGFX_RESET_VSYNC);
    }

    static void SetViewTransform(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, uint8_t viewId = 0) {
        bgfx::setViewTransform(viewId, &viewMatrix[0][0], &projectionMatrix[0][0]);
    }
};

} // namespace Misaka::Core::Renderer