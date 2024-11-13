export module Misaka.Core.Component.RenderComponent;

import <cstdint>;
import <vector>;
import <string>;
import <memory>;
import Misaka.Core.Component.IComponent;
import Misaka.Core.Renderer.VertexBuffer;
import Misaka.Core.Renderer.IndexBuffer;
import Misaka.Core.Renderer.Shader;

namespace Misaka::Core::Resource::Data {

struct RenderData {
    Renderer::VertexBuffer vertexBuffer;
    Renderer::IndexBuffer  indexBuffer;
    Renderer::Shader       shader;
};

} // namespace Misaka::Core::Resource::Data

namespace Misaka::Core::Component {

export class RenderComponent : public IComponent {
public:
    std::vector<std::shared_ptr<Resource::Data::RenderData>> renderDatas;
};

} // namespace Misaka::Core::Component