export module Misaka.Core.GameModule.RenderInitSystem;

import Misaka.Core.GameModule.Interface.IInitSystem;

namespace Misaka::Core::GameModules {

export class RenderInitSystem : public IInitSystem {
public:
    virtual ~RenderInitSystem() = default;
    virtual void Init() override;
};

} // namespace Misaka::Core::GameModules