export module Misaka.Core.GameRoom.GameRoom;

import <entt/entt.hpp>;
import <memory>;
import <vector>;
import Misaka.Core.Context.Context;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.GameModule.Interface.ISystem;
import Misaka.Core.GameModule.Interface.IExcuteSystem;
import Misaka.Core.GameModule.Interface.IRenderSystem;
import Misaka.Core.GameModule.OpenGLAssetUpLoadSystem;
import Misaka.Core.GameModule.OpenGLRenderSystem;

namespace Misaka::Core::GameRoom {

export class GameRoom {
public:
    void Init() {
        m_ExcuteSystem.emplace_back(std::make_shared<GameModules::OpenGLAssetUpLoadSystem>());
        m_RenderSystem.emplace_back(std::make_shared<GameModules::OpenGLRenderSystem>());
    }

    Entity::MisakaEntity AddEntity() {
        auto& registry = Context::Context::Instance().gameRoomContext.Registry;
        auto  entity   = registry->create();
        return Entity::MisakaEntity(entity, registry);
    }

    void Excute() {
        for (auto& system : m_ExcuteSystem) {
            std::dynamic_pointer_cast<GameModules::IExcuteSystem>(system)->Excute();
        }
    }

    void Render() {
        for (auto& system : m_RenderSystem) {
            std::dynamic_pointer_cast<GameModules::IRenderSystem>(system)->Render();
        }
    }

private:
    std::vector<std::shared_ptr<GameModules::ISystem>> m_ExcuteSystem;
    std::vector<std::shared_ptr<GameModules::ISystem>> m_RenderSystem;
};

} // namespace Misaka::Core::GameRoom