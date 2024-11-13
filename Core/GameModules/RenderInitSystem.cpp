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
import Misaka.Core.Component.WindowDataComponent;
import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.Renderer.Renderer;

namespace Misaka::Core::GameModules {

static void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    Renderer::Renderer::OnWindowResize(width, height);
    Component::WindowDataComponent::Instance().width  = width;
    Component::WindowDataComponent::Instance().height = height;
}

void RenderInitSystem::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    auto       &glfwWindowComponent = Component::WindowDataComponent::Instance();
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

    Renderer::Renderer::Init();
}

} // namespace Misaka::Core::GameModules