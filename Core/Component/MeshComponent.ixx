export module Misaka.Core.Component.MeshComponent;

import <vector>;
import <string>;
import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class MeshComponent : public IComponent {
public:
    std::vector<std::string> meshes;

    void AddMesh(const std::string& mesh) {
        meshes.push_back(mesh);
    }

    bool dirty = true;
};

} // namespace Misaka::Core::Component