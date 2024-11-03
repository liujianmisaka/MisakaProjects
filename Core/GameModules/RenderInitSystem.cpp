module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

module Misaka.Core.GameModule.RenderInitSystem;

import <vector>;
import <fstream>;
import <sstream>;
import <iostream>;
import Misaka.Core.Component.GLFWWindowComponent;
import Misaka.Core.GameModule.Interface.IInitSystem;

namespace Misaka::Core::GameModules {

static void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    bgfx::reset(width, height, BGFX_RESET_VSYNC);
    Component::GLFWWindowComponent::Instance().width  = width;
    Component::GLFWWindowComponent::Instance().height = height;
}

void RenderInitSystem::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    auto       &glfwWindowComponent = Component::GLFWWindowComponent::Instance();
    GLFWwindow *window =
        glfwCreateWindow(glfwWindowComponent.width, glfwWindowComponent.height, glfwWindowComponent.title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwWindowComponent.window = window;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    bgfx::Init init;
    init.type              = bgfx::RendererType::OpenGL;
    init.vendorId          = BGFX_PCI_ID_NVIDIA;
    init.platformData.nwh  = glfwGetWin32Window(glfwWindowComponent.window);
    init.platformData.ndt  = nullptr;
    init.resolution.width  = glfwWindowComponent.width;
    init.resolution.height = glfwWindowComponent.height;
    init.resolution.reset  = BGFX_RESET_VSYNC;
    bgfx::init(init);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDFF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, glfwWindowComponent.width, glfwWindowComponent.height);
}

} // namespace Misaka::Core::GameModules