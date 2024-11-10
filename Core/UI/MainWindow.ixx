module;

#include <imgui.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "imgui_impl_bgfx.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

export module Misaka.Core.UI.MainWindow;

import <iostream>;
import Misaka.Core.Context.Context;
import Misaka.Core.Component.WindowDataComponent;

namespace Misaka::Core::UI {

export class MainWindow {
public:
    MainWindow()  = default;
    ~MainWindow() = default;

    void BeginFrame() {
        bgfx::touch(0);
        ImGui_Implbgfx_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Draw() {
        // Note: Switch this to true to enable dockspace
        static bool               dockspaceOpen             = false;
        static bool               opt_fullscreen_persistant = false;
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

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                // ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
                ImGui::MenuItem("New", "Ctrl+N");
                ImGui::MenuItem("Open...", "Ctrl+O");
                ImGui::MenuItem("Save As...", "Ctrl+Shift+S");
                ImGui::MenuItem("Exit");
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Stats");

        ImGui::End();

        ImGui::Begin("Settings");
        ImGui::Text("Hello, world!");
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Viewport");
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset    = ImGui::GetWindowPos();
        // m_ViewportBounds[0]    = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
        // m_ViewportBounds[1]    = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};

        // m_ViewportFocused = ImGui::IsWindowFocused();
        // m_ViewportHovered = ImGui::IsWindowHovered();
        // Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

        // ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        // m_ViewportSize           = {viewportPanelSize.x, viewportPanelSize.y};

        // uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        // ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

        // if (ImGui::BeginDragDropTarget()) {
        //     if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
        //         const auto* path = static_cast<const wchar_t*>(payload->Data);
        //         OpenScene(std::filesystem::path(g_AssetPath) / path);
        //     }
        //     ImGui::EndDragDropTarget();
        // }

        // Gizmos
        // Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
        // if (selectedEntity && m_GizmoType != -1) {
        //    ImGuizmo::SetOrthographic(false);
        //    ImGuizmo::SetDrawlist();

        //    ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x,
        //                      m_ViewportBounds[1].y - m_ViewportBounds[0].y);

        // Camera

        // Runtime camera from entity
        // auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
        // const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
        // const glm::mat4& cameraProjection = camera.GetProjection();
        // glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

        // Editor camera
        //    const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
        //    glm::mat4        cameraView       = m_EditorCamera.GetViewMatrix();

        //    // Entity transform
        //    auto&     tc        = selectedEntity.GetComponent<TransformComponent>();
        //    glm::mat4 transform = tc.GetTransform();

        //    // Snapping
        //    bool  snap      = Input::IsKeyPressed(Key::LeftControl);
        //    float snapValue = 0.5f; // Snap to 0.5m for translation/scale
        //    // Snap to 45 degrees for rotation
        //    if (m_GizmoType == ImGuizmo::OPERATION::ROTATE) snapValue = 45.0f;

        //    float snapValues[3] = {snapValue, snapValue, snapValue};

        //    ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)m_GizmoType,
        //                         ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

        //    if (ImGuizmo::IsUsing()) {
        //        glm::vec3 translation, rotation, scale;
        //        Math::DecomposeTransform(transform, translation, rotation, scale);

        //        glm::vec3 deltaRotation = rotation - tc.Rotation;
        //        tc.Translation          = translation;
        //        tc.Rotation += deltaRotation;
        //        tc.Scale = scale;
        //    }
        //}

        ImGui::End();
        ImGui::PopStyleVar();

        // UI_Toolbar();

        ImGui::End();
    }

    void EndFrame() {
        ImGui::Render();
        ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
        bgfx::setViewRect(0, 0, 0, Component::WindowDataComponent::Instance().width, Component::WindowDataComponent::Instance().height);
        bgfx::frame();
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

} // namespace Misaka::Core::UI