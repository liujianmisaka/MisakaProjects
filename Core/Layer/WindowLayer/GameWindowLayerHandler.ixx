export module Misaka.Core.Layer.GameWindowLayerHandler;

import Misaka.Core.Layer.ILayerHandler;

namespace Misaka::Core::Layer {

export class GameWindowLayerHandler : public WindowLayerHandler {
public:
    virtual ~GameWindowLayerHandler() = default;

    virtual void OnWindowLayerHandler() {
    }
};

} // namespace Misaka::Core::Layer
