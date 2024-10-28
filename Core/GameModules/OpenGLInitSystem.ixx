export module Misaka.Core.GameModule.OpenGLInitSystem;

import Misaka.Core.GameModule.Interface.IInitSystem;

namespace Misaka::Core::GameModules {

export class OpenGLInitSystem : public IInitSystem {
public:
    virtual ~OpenGLInitSystem() = default;
    virtual void Init() override;
};

} // namespace Misaka::Core::GameModules