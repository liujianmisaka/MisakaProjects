module;

#include <imgui.h>

export module Misaka.Core.Editor.MisakaEditor:Tools;

import glm;
import Misaka.Core.CoreConfig;

namespace Misaka::Core::Editor {

class Tools {
public:
    static void Render() {
        ImGui::Begin("Tools");

        // Set MVP Matrix
        auto fov = glm::degrees(CoreConfig::fov);
        ImGui::DragFloat("FOV", &fov, 0.1f, 0.0f, 180.0f);
        CoreConfig::fov        = glm::radians(fov);
        CoreConfig::projection = glm::perspective(CoreConfig::fov, CoreConfig::aspectRatio, CoreConfig::nearPlane, CoreConfig::farPlane);

        ImGui::End();
    }
};

} // namespace Misaka::Core::Editor