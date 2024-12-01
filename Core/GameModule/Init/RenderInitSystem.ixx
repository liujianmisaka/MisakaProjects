module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

export module Misaka.Core.GameModule.RenderInitSystem;

import <vector>;
import <fstream>;
import <sstream>;
import <iostream>;
import Misaka.Core.CoreConfig;
import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.Renderer.Renderer;

namespace Misaka::Core::GameModule {

export class RenderInitSystem : public IInitSystem {
public:
    virtual ~RenderInitSystem() = default;

    virtual void Initialize() override {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        GLFWwindow *window = glfwCreateWindow(CoreConfig::windowWidth, CoreConfig::windowHeight, CoreConfig::windowTitle, nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            return;
        }

        CoreConfig::window = window;

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            Renderer::Renderer::OnWindowResize(width, height);
            CoreConfig::windowWidth  = width;
            CoreConfig::windowHeight = height;
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        Renderer::Renderer::Init();
    }
};

} // namespace Misaka::Core::GameModule