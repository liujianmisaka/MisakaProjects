// import Misaka.Core.Utils.GameController;
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <imgui.h>

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, bgfx!", nullptr, nullptr);

    bgfx::PlatformData pd;
    pd.nwh = glfwGetWin32Window(window);
    bgfx::setPlatformData(pd);

    bgfx::Init init;
    init.type              = bgfx::RendererType::OpenGL;
    init.vendorId          = BGFX_PCI_ID_NONE;
    init.platformData.nwh  = pd.nwh;
    init.platformData.ndt  = nullptr;
    //init.platformData.type = bgfx::PlatformData::type;
    init.resolution.width  = 800;
    init.resolution.height = 600;
    init.resolution.reset  = BGFX_RESET_VSYNC;
    bgfx::init(init);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, 800, 600);

    unsigned int counter = 0;
    while (true) {
        glfwPollEvents();
        bgfx::touch(0);
        bgfx::frame();
        counter++;
    }

    return 0;
}
