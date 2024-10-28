export module Misaka.Core.Resource.AssetLoader;

import <string>;
import <vector>;
import Misaka.Core.Component.MeshComponent;

namespace Misaka::Core::Resource::Data {

export struct Mesh {
    std::vector<float>        vertices;
    std::vector<unsigned int> indices;
};

export struct Shader {
    std::string vertexSource;
    std::string fragmentSource;
};

} // namespace Misaka::Core::Resource::Data

namespace Misaka::Core::Resource {

export class AssetLoader {
public:
    void LoadMeshes(const std::string& meshPath, Component::MeshComponent& meshComponent);
};

} // namespace Misaka::Core::Resource