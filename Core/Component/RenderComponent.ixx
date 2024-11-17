export module Misaka.Core.Component.RenderComponent;

import <cstdint>;
import <vector>;
import <string>;
import <memory>;
import Misaka.Core.Component.IComponent;
import Misaka.Core.Renderer.VertexBuffer;
import Misaka.Core.Renderer.IndexBuffer;
import Misaka.Core.Renderer.Shader;

namespace Misaka::Core::Component::Data {

export struct RenderData {
    std::shared_ptr<Renderer::VertexBuffer> vertexBuffer;
    std::shared_ptr<Renderer::IndexBuffer>  indexBuffer;
    std::shared_ptr<Renderer::Shader>       shader;

    bool hasTexture = false;

};

} // namespace Misaka::Core::Component::Data

namespace Misaka::Core::Component {

export class RenderComponent : public IComponent {
public:
    std::vector<Data::RenderData> renderDatas;
};

} // namespace Misaka::Core::Component