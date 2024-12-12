module;

#include <imgui.h>

export module Misaka.Core.BTTree.RenderableNode;

import <string>;
import <algorithm>;

namespace Misaka::Core::BTTree {

export class RenderableNode {
public:
    RenderableNode(std::string nodeName, ImVec2 position, ImVec2 size) : NodeName(nodeName), Position(position), Size(size) {
    }

    void OnBTNodeDebug() {};

    void OnBTNodeRender() {
        // 设置按钮的位置
        ImGui::SetCursorPos(Position);

        // 创建一个按钮
        if (ImGui::Button(NodeName.c_str(), ImVec2(Size.x, Size.y))) {
            // 按钮被点击时的处理
            ImGui::Text("Button clicked!");
        }

        // 判断按钮是否被拖拽
        // 判断按钮是否被拖拽
        if (ImGui::IsItemActive() && !IsDragging) {
            // 如果鼠标点击在按钮上，记录初始偏移量
            IsDragging = true;
            DragOffset = ImVec2(ImGui::GetMousePos().x - Position.x, ImGui::GetMousePos().y - Position.y);
        }

        // 如果按钮正在拖拽
        if (IsDragging) {
            // 获取鼠标当前位置，并计算按钮的新位置
            ImVec2 newPos = ImVec2(ImGui::GetMousePos().x - DragOffset.x, ImGui::GetMousePos().y - DragOffset.y);

            // 限制拖拽范围，避免按钮出现在窗口外
            ImVec2 windowSize = ImGui::GetWindowSize();
            newPos.x          = std::clamp(newPos.x, 0.0f, windowSize.x - Size.x);
            newPos.y          = std::clamp(newPos.y, 0.0f, windowSize.y - Size.y);

            // 更新按钮位置
            Position = newPos;

            // 如果鼠标释放，结束拖拽
            if (!ImGui::IsMouseDown(0)) {
                IsDragging = false;
            }
        }
    }

    std::string NodeName;
    ImVec2      Position;
    ImVec2      Size;
    bool        IsDragging;
    ImVec2      DragOffset;
};

} // namespace Misaka::Core::BTTree