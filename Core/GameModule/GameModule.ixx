export module Misaka.Core.GameModule.GameModule;

import <vector>;
import <memory>;
import Misaka.Core.GameModule.Interface.ISystem;
import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.GameModule.Interface.IExcuteSystem;
import Misaka.Core.GameModule.Interface.IRenderSystem;

namespace Misaka::Core::GameModule {

export class GameModule {
public:
    template <typename T>
    void AddSystem() {
        static_assert(std::is_base_of<ISystem, T>::value, "T must be derived from ISystem");

        if constexpr (std::is_base_of<IInitSystem, T>::value) {
            m_InitSystem.push_back(std::make_unique<T>());
        }

        if constexpr (std::is_base_of<IExcuteSystem, T>::value) {
            m_ExcuteSystem.push_back(std::make_unique<T>());
        }

        if constexpr (std::is_base_of<IRenderSystem, T>::value) {
            m_RenderSystem.push_back(std::make_unique<T>());
        }
    }

    void Initialize() {
        for (auto& system : m_InitSystem) {
            system->Initialize();
        }
    }

    void Excute() {
        for (auto& system : m_ExcuteSystem) {
            system->Excute();
        }
    }

    void Render() {
        for (auto& system : m_RenderSystem) {
            system->Render();
        }
    }

private:
    std::vector<std::unique_ptr<IInitSystem>>   m_InitSystem;
    std::vector<std::unique_ptr<IExcuteSystem>> m_ExcuteSystem;
    std::vector<std::unique_ptr<IRenderSystem>> m_RenderSystem;
};

} // namespace Misaka::Core::GameModule