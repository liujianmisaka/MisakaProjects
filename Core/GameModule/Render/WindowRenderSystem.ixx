export module Misaka.Core.GameModule.WindowRenderSystem;

import Misaka.Core.GameModule.Interface.IRenderSystem;
import Misaka.Core.SingletonManager;
import Misaka.Core.Manager.LayerHandlerManager;

namespace Misaka::Core::GameModule {

export class WindowRenderSystem : public IRenderSystem {
public:
    virtual ~WindowRenderSystem() = default;

    virtual void Render() override {
        SingletonManager::GetInstance<Manager::LayerHandlerManager>()->DoWindowLayer();
    }
};

} // namespace Misaka::Core::GameModule