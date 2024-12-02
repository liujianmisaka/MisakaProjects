export module Misaka.Core.Layer.MisakaGameLayerHandler;

import Misaka.Core.Layer.ILayerHandler;

namespace Misaka::Core::Layer {

export class MisakaGameLayerHandler : public WindowLayerHandler {
public:
    virtual ~MisakaGameLayerHandler() = default;

    virtual void OnWindowLayerHandler() {
    }
};

} // namespace Misaka::Core::Layer
