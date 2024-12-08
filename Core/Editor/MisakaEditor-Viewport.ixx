module;

#include <imgui.h>
#include <imgui_internal.h>
#include <entt/entt.hpp>

export module Misaka.Core.Editor.MisakaEditor:Viewport;

import glm;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Manager.FrameBufferManager;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.TagComponent;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.Component.MeshComponent;

namespace Misaka::Core::Editor {

class Viewport {
public:
    static void Render() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Viewport");

        auto viewportFrameBuffer =
            SingletonManager::GetInstance<Manager::FrameBufferManager>()->GetFrameBuffer(Manager::FrameBufferType::VIEWPORT);

        // 获取视口尺寸
        ImVec2 viewportPanelSize   = ImGui::GetContentRegionAvail();
        float  viewportAspectRatio = viewportPanelSize.x / viewportPanelSize.y;

        CoreConfig::aspectRatio = viewportAspectRatio;
        CoreConfig::perspectiveProjection  = glm::perspective(CoreConfig::fov, CoreConfig::aspectRatio, CoreConfig::nearPlane, CoreConfig::farPlane);

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
    }
};

} // namespace Misaka::Core::Editor