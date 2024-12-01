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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // Add this include for glm::value_ptr
#include <entt/entt.hpp>

export module Misaka.Core.UI.MainWindow;

import <iostream>;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Manager.FrameBufferManager;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.TagComponent;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.Component.MeshComponent;

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

        SceneHierarchy();

        ImGui::Begin("Settings");

        // Set MVP Matrix
        auto fov = glm::degrees(CoreConfig::fov);
        ImGui::DragFloat("FOV", &fov, 0.1f, 0.0f, 180.0f);
        CoreConfig::fov        = glm::radians(fov);
        CoreConfig::projection = glm::perspective(CoreConfig::fov, CoreConfig::aspectRatio, CoreConfig::nearPlane, CoreConfig::farPlane);

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Viewport");

        auto viewportFrameBuffer =
            SingletonManager::GetInstance<Manager::FrameBufferManager>()->GetFrameBuffer(Manager::FrameBufferType::VIEWPORT);

        // 获取视口尺寸
        ImVec2 viewportPanelSize   = ImGui::GetContentRegionAvail();
        float  viewportAspectRatio = viewportPanelSize.x / viewportPanelSize.y;

        CoreConfig::aspectRatio = viewportAspectRatio;
        CoreConfig::projection  = glm::perspective(CoreConfig::fov, CoreConfig::aspectRatio, CoreConfig::nearPlane, CoreConfig::farPlane);

        ImTextureID textureID = (ImTextureID)viewportFrameBuffer->GetTextureIndex();
        ImGui::Image(textureID, viewportPanelSize, ImVec2{0, 1}, ImVec2{1, 0});

        // Right-click on blank space
        auto registry = SingletonManager::GetInstance<entt::registry>();
        if (ImGui::BeginPopupContextWindow(nullptr, 1)) {
            ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.15f, 0.15f, 0.15f, 0.9f));
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5));

            if (ImGui::MenuItem("  Create Empty Entity")) {
                auto                 entity = registry->create();
                Entity::MisakaEntity misakaEntity(entity, registry);
                misakaEntity.AddComponent<Component::TagComponent>("MisakaEntity");
                misakaEntity.AddComponent<Component::TransformComponent>();
            }
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Create an empty entity with no components.");
            }

            ImGui::Separator();

            if (ImGui::MenuItem("  Create Cube Entity")) {
                auto                 entity = registry->create();
                Entity::MisakaEntity misakaEntity(entity, registry);
                misakaEntity.AddComponent<Component::TagComponent>("cube");
                misakaEntity.AddComponent<Component::TransformComponent>();
                misakaEntity.AddComponent<Component::MeshComponent>().AddMesh("cube");
            }
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Create a cube entity with a mesh component.");
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
            ImGui::EndPopup();
        }

        ImGui::End();
        ImGui::PopStyleVar();

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

    void SceneHierarchy() {
        ImGui::Begin("Scene Hierarchy");

        auto registry = SingletonManager::GetInstance<entt::registry>();

        if (registry) {
            for (auto entity : registry->view<entt::entity>()) {
                auto misakaEntity = Entity::MisakaEntity(entity, registry);
                DrawEntityNode(misakaEntity);
            }

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
                m_SelectionEntity = {};
            }
        }

        ImGui::End();

        ImGui::Begin("Properties");
        if (m_SelectionEntity.IsValid()) {
            DrawComponents(m_SelectionEntity);
        }
        ImGui::End();
    }

    void DrawEntityNode(Entity::MisakaEntity entity) {
        const auto& tag = entity.GetComponent<Component::TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = (m_SelectionEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        // flags |= ImGuITreeNodeFlags_SpanAllAvailWidth;   // TODO: not support in this imgui version
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

        if (ImGui::IsItemClicked()) {
            m_SelectionEntity = entity;
        }

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete Entity")) {
                entityDeleted = true;
            }
            ImGui::EndPopup();
        }

        if (opened) {
            ImGuiTreeNodeFlags flags     = ImGuiTreeNodeFlags_OpenOnArrow;
            bool               subopened = ImGui::TreeNodeEx((void*)986468, flags, tag.c_str());
            if (subopened) ImGui::TreePop();
            ImGui::TreePop();
        }

        // delay delete entity
        if (entityDeleted) {
            auto registry = SingletonManager::GetInstance<entt::registry>();
            registry->destroy(entity);
            if (m_SelectionEntity == entity) {
                m_SelectionEntity = {};
            }
        }
    }

    void DrawComponents(Entity::MisakaEntity entity) {
        if (entity.HasComponent<Component::TagComponent>()) {
            auto& tag = entity.GetComponent<Component::TagComponent>().Tag;

            char buffer[256] = {};
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component")) ImGui::OpenPopup("AddComponent");

        // if (ImGui::BeginPopup("AddComponent")) {
        //     if (!m_SelectionEntity.HasComponent<CameraComponent>()) {
        //         if (ImGui::MenuItem("Camera")) {
        //             m_SelectionEntity.AddComponent<CameraComponent>();
        //             ImGui::CloseCurrentPopup();
        //         }
        //     }

        //    if (!m_SelectionEntity.HasComponent<SpriteRendererComponent>()) {
        //        if (ImGui::MenuItem("Sprite Render")) {
        //            m_SelectionEntity.AddComponent<SpriteRendererComponent>();
        //            ImGui::CloseCurrentPopup();
        //        }
        //    }

        //    if (!m_SelectionEntity.HasComponent<CircleRendererComponent>()) {
        //        if (ImGui::MenuItem("Circle Renderer")) {
        //            m_SelectionEntity.AddComponent<CircleRendererComponent>();
        //            ImGui::CloseCurrentPopup();
        //        }
        //    }

        //    if (!m_SelectionEntity.HasComponent<Rigidbody2DComponent>()) {
        //        if (ImGui::MenuItem("Rigidbody 2D")) {
        //            m_SelectionEntity.AddComponent<Rigidbody2DComponent>();
        //            ImGui::CloseCurrentPopup();
        //        }
        //    }

        //    if (!m_SelectionEntity.HasComponent<BoxCollider2DComponent>()) {
        //        if (ImGui::MenuItem("BoxCollider 2D")) {
        //            m_SelectionEntity.AddComponent<BoxCollider2DComponent>();
        //            ImGui::CloseCurrentPopup();
        //        }
        //    }

        //    if (!m_SelectionEntity.HasComponent<CircleCollider2DComponent>()) {
        //        if (ImGui::MenuItem("CircleCollider 2D")) {
        //            m_SelectionEntity.AddComponent<CircleCollider2DComponent>();
        //            ImGui::CloseCurrentPopup();
        //        }
        //    }

        //    ImGui::EndPopup();
        //}

        // ImGui::PopItemWidth();

        // DrawComponent<TransformComponent>("Transform", entity, [](auto& component) {
        //     // WHY: Where set Camera move style?
        //     // NOTE: Camera move style is set in Render2D::BeginScene()
        //     DrawVec3Control("Translation", component.Translation);
        //     glm::vec3 rotation = glm::degrees(component.Rotation);
        //     DrawVec3Control("Rotation", rotation);
        //     component.Rotation = glm::radians(rotation);
        //     DrawVec3Control("Scale", component.Scale, 1.0f);
        // });

        DrawComponent<Component::TransformComponent>("Transform", entity, [](Component::TransformComponent& component) {
            // WHY: Where set Camera move style?
            // NOTE: Camera move style is set in Render2D::BeginScene()
            DrawVec3Control("Position", component.position);
            DrawVec3Control("Rotation", component.rotation);
            DrawVec3Control("Scale", component.scale, 1.0f);
        });

        DrawComponent<Component::MeshComponent>("Mesh", entity, [](Component::MeshComponent& component) {
            ImGui::Text("Meshes:");
            for (auto& mesh : component.meshes) {
                ImGui::Text(mesh.c_str());
            }
        });

        // DrawComponent<CameraComponent>("Camera", entity, [](auto& component) {
        //     auto& [camera, primary, fixedAspectRatio] = component;

        //    ImGui::Checkbox("Primary", &primary);

        //    const char* projectionTypeStrings[]     = {"Perspective", "Orthographic"};
        //    const char* currentProjectionTypeString = projectionTypeStrings[static_cast<int>(camera.GetProjectionType())];
        //    if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
        //        for (int i = 0; i < 2; i++) {
        //            const bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
        //            if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
        //                currentProjectionTypeString = projectionTypeStrings[i];
        //                camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
        //            }

        //            if (isSelected) ImGui::SetItemDefaultFocus();
        //        }
        //        ImGui::EndCombo();
        //    }

        //    if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
        //        float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
        //        if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
        //            camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

        //        float perspectiveNear = camera.GetPerspectiveNearClip();
        //        if (ImGui::DragFloat("Near", &perspectiveNear)) camera.SetPerspectiveNearClip(perspectiveNear);

        //        float perspectiveFar = camera.GetPerspectiveFarClip();
        //        if (ImGui::DragFloat("Far", &perspectiveFar)) camera.SetPerspectiveFarClip(perspectiveFar);
        //    }

        //    if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
        //        float orthoSize = camera.GetOrthographicSize();
        //        if (ImGui::DragFloat("Size", &orthoSize)) camera.SetOrthographicSize(orthoSize);

        //        float orthoNear = camera.GetOrthographicNearClip();
        //        if (ImGui::DragFloat("Near", &orthoNear)) camera.SetOrthographicNearClip(orthoNear);

        //        float orthoFar = camera.GetOrthographicFarClip();
        //        if (ImGui::DragFloat("Far", &orthoFar)) camera.SetOrthographicFarClip(orthoFar);

        //        ImGui::Checkbox("FixedAspectRatio", &fixedAspectRatio);
        //    }
        //});

        // DrawComponent<SpriteRendererComponent>("Sprite Render", entity, [](auto& component) {
        //     ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

        //    ImGui::Button("Texture", ImVec2(100.0f, 0.0f));
        //    if (ImGui::BeginDragDropTarget()) {
        //        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
        //            const wchar_t*        path        = (const wchar_t*)payload->Data;
        //            std::filesystem::path texturePath = std::filesystem::path(g_AssetPath) / path;
        //            Ref<Texture2D>        texture     = Texture2D::Create(texturePath.string());
        //            if (texture->IsLoaded())
        //                component.Texture = texture;
        //            else
        //                HZ_WARN("Could not load texture {0}", texturePath.filename().string());
        //        }
        //        ImGui::EndDragDropTarget();
        //    }

        //    ImGui::DragFloat("Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 100.0f);
        //});

        // DrawComponent<CircleRendererComponent>("Circle Renderer", entity, [](auto& component) {
        //     ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
        //     ImGui::DragFloat("Thickness", &component.Thickness, 0.025f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Fade", &component.Fade, 0.00025f, 0.0f, 1.0f);
        // });

        // DrawComponent<Rigidbody2DComponent>("Rigidbody 2D", entity, [](auto& component) {
        //     const char* bodyTypeStrings[]     = {"Static", "Dynamic", "Kinematic"};
        //     const char* currentBodyTypeString = bodyTypeStrings[static_cast<int>(component.Type)];
        //     if (ImGui::BeginCombo("Body Type", currentBodyTypeString)) {
        //         for (int i = 0; i < 2; i++) {
        //             const bool isSelected = currentBodyTypeString == bodyTypeStrings[i];
        //             if (ImGui::Selectable(bodyTypeStrings[i], isSelected)) {
        //                 currentBodyTypeString = bodyTypeStrings[i];
        //                 component.Type        = static_cast<Rigidbody2DComponent::BodyType>(i);
        //             }

        //            if (isSelected) ImGui::SetItemDefaultFocus();
        //        }
        //        ImGui::EndCombo();
        //    }

        //    ImGui::Checkbox("Fixed Rotation", &component.FixedRotation);
        //});

        // DrawComponent<BoxCollider2DComponent>("Box Collider 2D", entity, [](auto& component) {
        //     ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
        //     ImGui::DragFloat2("Size", glm::value_ptr(component.Offset));
        //     ImGui::DragFloat("Density", &component.Density, 0.01f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Friction", &component.Friction, 0.01f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Restitution", &component.Restitution, 0.01f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Restitution Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
        // });

        // DrawComponent<CircleCollider2DComponent>("Circle Collider 2D", entity, [](auto& component) {
        //     ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
        //     ImGui::DragFloat("Radius", &component.Radius);
        //     ImGui::DragFloat("Density", &component.Density, 0.01f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Friction", &component.Friction, 0.01f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Restitution", &component.Restitution, 0.01f, 0.0f, 1.0f);
        //     ImGui::DragFloat("Restitution Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
        // });
    }

    template <typename T, typename UIFunction>
    static void DrawComponent(const std::string& name, Entity::MisakaEntity entity, UIFunction uiFunction) {
        constexpr ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
                                                     ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;
        // TODO: ImGuITreeNodeFlags_SpanAllAvailWidth is not support in this imgui version
        if (entity.HasComponent<T>()) {
            auto&  component          = entity.GetComponent<T>();
            ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
            const float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            const bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(T).hash_code()), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();
            ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2{lineHeight, lineHeight})) {
                ImGui::OpenPopup("ComponentSettings");
            }

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings")) {
                if (ImGui::MenuItem("Remove component")) removeComponent = true;

                ImGui::EndPopup();
            }

            if (open) {
                uiFunction(component);
                ImGui::TreePop();
            }

            if (removeComponent) entity.RemoveComponent<T>();
        }
    }

    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f) {
        ImGui::PushID(label.c_str());

        auto boldFont = ImGui::GetIO().Fonts->Fonts[0];

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        // Learn: GImGui properties
        const float  lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        const ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize)) values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize)) values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize)) values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

private:
    bool   show_demo_window    = true;
    bool   show_another_window = false;
    ImVec4 clear_color         = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Entity::MisakaEntity m_SelectionEntity;
};

} // namespace Misaka::Core::UI