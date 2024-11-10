module;

#include <GLFW/glfw3.h>

export module Misaka.Core.Component.WindowDataComponent;

import Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Component {

export class WindowDataComponent : public Utils::Singleton<WindowDataComponent> {
public:
    GLFWwindow* window = nullptr;
    int         width  = 1600;
    int         height = 900;
    const char* title  = "Misaka Engine";

    // ImGui data
    int viewPortWidth  = 0;
    int viewPortHeight = 0;
};

} // namespace Misaka::Core::Component