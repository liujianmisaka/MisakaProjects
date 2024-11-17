export module Misaka.Core.Component.FrameBufferComponent;

import <memory>;
import Misaka.Core.Utils.Singleton;
import Misaka.Core.Component.IComponent;
import Misaka.Core.Renderer.FrameBuffer;

namespace Misaka::Core::Component {

export class FrameBufferComponent : public Utils::Singleton<FrameBufferComponent>, public IComponent {
public:
    std::shared_ptr<Renderer::FrameBuffer> viewportFrameBuffer;
    uint16_t                               width  = 900;
    uint16_t                               height = 900;
};

} // namespace Misaka::Core::Component