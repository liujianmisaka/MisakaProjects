export module Misaka.Core.GameModule.RenderSystem;

import Misaka.Core.GameModule.Interface.IRenderSystem;

namespace Misaka::Core::GameModules {

export class RenderSystem : public IRenderSystem {
public:
    virtual ~RenderSystem() = default;
    virtual void Render() override;
};

} // namespace Misaka::Core::GameModules