export module Misaka.Core.GameRoom.GameRoom;

import <entt/entt.hpp>;
import <memory>;
import <vector>;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.GameModule.Interface.ISystem;
import Misaka.Core.GameModule.Interface.IExcuteSystem;
import Misaka.Core.GameModule.Interface.IRenderSystem;
import Misaka.Core.GameModule.AssetUpLoadSystem;
import Misaka.Core.GameModule.RenderSystem;
import Misaka.Core.SingletonManager;
import Misaka.Core.Utils.Registry;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.Component.TagComponent;

namespace Misaka::Core::GameRoom {

export class GameRoom {
public:
    void Init() {
        m_ExcuteSystem.emplace_back(std::make_shared<GameModule::AssetUpLoadSystem>());
        m_RenderSystem.emplace_back(std::make_shared<GameModule::RenderSystem>());
    }

    Entity::MisakaEntity AddEntity(const std::string name = "MisakaEntity") {
        auto registry = SingletonManager::GetInstance<Utils::Registry>();
        auto  entity   = registry->create();
        auto misakEntity = Entity::MisakaEntity(entity, registry);
        misakEntity.AddComponent<Component::TagComponent>(name);
        misakEntity.AddComponent<Component::TransformComponent>();
        return misakEntity;
    }

    void Excute() {
        for (auto& system : m_ExcuteSystem) {
            std::dynamic_pointer_cast<GameModule::IExcuteSystem>(system)->Excute();
        }
    }

    void Render() {
        for (auto& system : m_RenderSystem) {
            std::dynamic_pointer_cast<GameModule::IRenderSystem>(system)->Render();
        }
    }

private:
    std::vector<std::shared_ptr<GameModule::ISystem>> m_ExcuteSystem;
    std::vector<std::shared_ptr<GameModule::ISystem>> m_RenderSystem;
};

} // namespace Misaka::Core::GameRoom