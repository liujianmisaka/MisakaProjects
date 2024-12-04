module;

#include <imgui.h>
#include <imgui_internal.h>
#include <entt/entt.hpp>

export module Misaka.Core.Editor.MisakaEditor:SceneHierarchy;

import glm;
import Misaka.Core.SingletonManager;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.TagComponent;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.Component.MeshComponent;

namespace Misaka::Core::Editor {

class SceneHierarchy {
public:
    static void Render() {
        ImGui::Begin("Scene Hierarchy");

        auto registry = SingletonManager::GetInstance<entt::registry>();

        if (registry) {
            for (auto entity : registry->view<entt::entity>()) {
                auto misakaEntity = Entity::MisakaEntity(entity, registry);
                DrawEntityNode(misakaEntity);
            }

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
                SelectionEntity = {};
            }
        }

        ImGui::End();

        ImGui::Begin("Properties");
        if (SelectionEntity.IsValid()) {
            DrawComponents(SelectionEntity);
        }
        ImGui::End();
    }

private:
    static void DrawEntityNode(Entity::MisakaEntity entity) {
        const auto& tag = entity.GetComponent<Component::TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = (SelectionEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        // flags |= ImGuITreeNodeFlags_SpanAllAvailWidth;   // TODO: not support in this imgui version
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

        if (ImGui::IsItemClicked()) {
            SelectionEntity = entity;
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
            if (SelectionEntity == entity) {
                SelectionEntity = {};
            }
        }
    }

    static void DrawComponents(Entity::MisakaEntity entity) {
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

        if (ImGui::BeginPopup("AddComponent")) {
            if (!SelectionEntity.HasComponent<Component::MeshComponent>()) {
                if (ImGui::MenuItem("Mesh")) {
                    SelectionEntity.AddComponent<Component::MeshComponent>();
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

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
    static Entity::MisakaEntity SelectionEntity;
};

Entity::MisakaEntity SceneHierarchy::SelectionEntity = {};

} // namespace Misaka::Core::Editor