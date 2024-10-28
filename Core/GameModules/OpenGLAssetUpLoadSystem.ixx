export module Misaka.Core.GameModule.OpenGLAssetUpLoadSystem;

import Misaka.Core.GameModule.Interface.IExcuteSystem;

namespace Misaka::Core::GameModules {

export class OpenGLAssetUpLoadSystem : public IExcuteSystem {
public:
    virtual ~OpenGLAssetUpLoadSystem() = default;
    virtual void Excute() override;
};

} // namespace Misaka::Core::GameModules