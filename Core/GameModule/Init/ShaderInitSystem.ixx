export module Misaka.Core.GameModule.ShaderInitSystem;

import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.SingletonManager;
import Misaka.Core.Manager.ShaderManager;

namespace Misaka::Core::GameModule {

export class ShaderInitSystem : public IInitSystem {
public:
    void Initialize() override {
        auto shaderManager = SingletonManager::GetInstance<Manager::ShaderManager>();
        shaderManager->LoadShader("base");
    }
};

} // namespace Misaka::Core::GameModule