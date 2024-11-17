export module Misaka.Core.GameModule.Interface.IInitSystem;

import Misaka.Core.GameModule.Interface.ISystem;

namespace Misaka::Core::GameModule {

export class IInitSystem {
public:
    virtual ~IInitSystem() = default;
    virtual void Initialize() = 0;
};

} // namespace Misaka::Core::GameModule