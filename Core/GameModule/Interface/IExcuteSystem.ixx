export module Misaka.Core.GameModule.Interface.IExcuteSystem;

import Misaka.Core.GameModule.Interface.ISystem;

namespace Misaka::Core::GameModule {

export class IExcuteSystem : public ISystem {
public:
    virtual ~IExcuteSystem() = default;
    virtual void Excute() = 0;
};

} // namespace Misaka::Core::GameModule