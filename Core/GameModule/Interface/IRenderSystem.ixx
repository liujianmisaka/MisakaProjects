export module Misaka.Core.GameModule.Interface.IRenderSystem;

import Misaka.Core.GameModule.Interface.ISystem;

namespace Misaka::Core::GameModule {

export class IRenderSystem : public ISystem {
public:
    virtual ~IRenderSystem() = default;
    virtual void Render()    = 0;
};

} // namespace Misaka::Core::GameModule