module;

#include <GLFW/glfw3.h>

export module Misaka.Core.Context.GraphicsContext;

import <unordered_map>;
import Misaka.Core.Context.IContext;

namespace Misaka::Core::Context {

export enum class ShaderType { Base };

export class GraphicsContext : public IContext {
public:
    virtual ~GraphicsContext() = default;

    bool shouldClose() const { return glfwWindowShouldClose(Window); }

    GLFWwindow* Window = nullptr;

    std::unordered_map<ShaderType, unsigned int> CommonShaders = {};
};

} // namespace Misaka::Core::Context