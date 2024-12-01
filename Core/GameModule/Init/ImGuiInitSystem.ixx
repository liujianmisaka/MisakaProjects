module;

#include <imgui.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "UI/imgui_impl_bgfx.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

export module Misaka.Core.GameModule.ImGuiInitSystem;

import <iostream>;
import Misaka.Core.CoreConfig;
import Misaka.Core.GameModule.Interface.IInitSystem;

namespace Misaka::Core::GameModule {

export class ImGuiInitSystem : public IInitSystem {
public:
    virtual ~ImGuiInitSystem() = default;

    virtual void Initialize() override {
        if (CoreConfig::window == nullptr) {
            throw std::runtime_error("GLFW window is nullptr, call RenderInitSystem first.");
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_Implbgfx_Init(255);
        ImGui_ImplGlfw_InitForOpenGL(CoreConfig::window, true);
    }
};

} // namespace Misaka::Core::GameModule
