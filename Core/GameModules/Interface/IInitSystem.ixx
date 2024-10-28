export module Misaka.Core.GameModule.Interface.IInitSystem;

import Misaka.Core.GameModule.Interface.ISystem;

namespace Misaka::Core::GameModules {

export class IInitSystem {
public:
    virtual ~IInitSystem() = default;
    virtual void Init() = 0;
};

} // namespace Misaka::Core::GameModules