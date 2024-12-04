module;

#include <imgui.h>
#include <imgui_internal.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "imgui_impl_bgfx.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <entt/entt.hpp>

export module Misaka.Core.Editor.MisakaEditor;

import :Toolbar;
import :SceneHierarchy;
import :Tools;
import :Viewport;

import <iostream>;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Manager.FrameBufferManager;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.TagComponent;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.Component.MeshComponent;

namespace Misaka::Core::Editor {

export class MisakaEditor {
public:
    MisakaEditor()  = default;
    ~MisakaEditor() = default;

    void Init() {
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

    void Tick() {
        BeginFrame();
        Draw();
        EndFrame();
    }

    void BeginFrame() {
        bgfx::touch(0);
        ImGui_Implbgfx_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Draw() {
        // Note: Switch this to true to enable dockspace
        static bool               dockspaceOpen             = true;
        static bool               opt_fullscreen_persistant = true;
        bool                      opt_fullscreen            = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags           = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we
        // ask Begin() to not render a background.
        if (dockspace_flags) // TODO: ImGuiDockNodeFlags_PassthruCentralNode
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen) ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO&    io          = ImGui::GetIO();
        ImGuiStyle& style       = ImGui::GetStyle();
        float       minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x   = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        Toolbar::Render();
        SceneHierarchy::Render();
        Tools::Render();
        Viewport::Render();

        ImGui::End();
    }

    void EndFrame() {
        ImGui::Render();
        ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
    }

    void Shutdown() {
        ImGui_ImplGlfw_Shutdown();
        ImGui_Implbgfx_Shutdown();
        ImGui::DestroyContext();
        bgfx::shutdown();
    }

private:
    bool   show_demo_window    = true;
    bool   show_another_window = false;
    ImVec4 clear_color         = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

} // namespace Misaka::Core::Editor