module;

#include <imgui.h>

export module Misaka.Core.Editor.MisakaEditor:Toolbar;

namespace Misaka::Core::Editor {

class Toolbar {
public:
    static void Render() {
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
    }
};

} // namespace Misaka::Core::Editor