module;

#include <entt/entt.hpp>

export module Misaka.Core.GameRoom.GameRoom;

import <string>;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.Component.TagComponent;

namespace Misaka::Core {

export class GameRoom {
public:
    Entity::MisakaEntity AddEntity(const std::string name = "MisakaEntity") {
        entt::entity entity      = SingletonManager::GetInstance<entt::registry>()->create();
        auto         misakEntity = Entity::MisakaEntity(entity, SingletonManager::GetInstance<entt::registry>());
        misakEntity.AddComponent<Component::TagComponent>(name);
        misakEntity.AddComponent<Component::TransformComponent>();
        return misakEntity;
    }
};

} // namespace Misaka::Core