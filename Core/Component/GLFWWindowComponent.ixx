module;

#include <GLFW/glfw3.h>

export module Misaka.Core.Component.GLFWWindowComponent;

import <stdexcept>;
import Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Component {

export class GLFWWindowComponent : public Utils::Singleton<GLFWWindowComponent> {
public:
    GLFWwindow* window = nullptr;
    int         width  = 1600;
    int         height = 900;
    const char* title  = "Misaka Engine";
};

} // namespace Misaka::Core::Component