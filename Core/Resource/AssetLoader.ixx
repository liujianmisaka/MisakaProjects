export module Misaka.Core.Resource.AssetLoader;

import <string>;
import <vector>;
import Misaka.Core.Component.MeshComponent;

namespace Misaka::Core::Resource {

export class AssetLoader {
public:
    void LoadMeshes(const std::string& meshPath, Component::MeshComponent& meshComponent);
};

} // namespace Misaka::Core::Resource