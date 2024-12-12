module;

#include <imgui.h>
#include <imgui_internal.h>

export module Misaka.Core.Editor.MisakaEditor:BTTreePanel;

import Misaka.Core.BTTree.RenderableNode;

using namespace Misaka::Core::BTTree;

namespace Misaka::Core::Editor {

class BTTreePanel {
public:
    static void Render() {
        static RenderableNode button = {"Draggable Button", ImVec2(100, 100), ImVec2(150, 30)};

        ImGui::Begin("Behavior Tree");

        button.OnBTNodeRender();

        ImGui::End();
    }
};

} // namespace Misaka::Core::Editor