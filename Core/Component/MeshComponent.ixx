export module Misaka.Core.Component.MeshComponent;

import <vector>;
import <string>;
import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class MeshComponent : public IComponent {
public:
    std::vector<std::string> meshes;

    bool dirty = true;
};

} // namespace Misaka::Core::Component