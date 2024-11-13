export module Misaka.Core.Component.MeshComponent;

import <vector>;
import <string>;
import <memory>;
import Misaka.Core.Component.IComponent;

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

namespace Misaka::Core::Component {

export class MeshComponent : public IComponent {
public:
    std::vector<std::shared_ptr<Resource::Data::Mesh>> meshes;
};

} // namespace Misaka::Core::Component