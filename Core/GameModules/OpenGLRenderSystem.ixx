export module Misaka.Core.GameModule.OpenGLRenderSystem;

import Misaka.Core.GameModule.Interface.IRenderSystem;

namespace Misaka::Core::GameModules {

export class OpenGLRenderSystem : public IRenderSystem {
public:
    virtual ~OpenGLRenderSystem() = default;
    virtual void Render() override;
};

} // namespace Misaka::Core::GameModules