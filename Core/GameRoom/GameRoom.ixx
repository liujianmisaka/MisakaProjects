export module Misaka.Core.GameRoom.GameRoom;

import <entt/entt.hpp>;
import Misaka.Core.Context.Context;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Entity.MisakaEntity;

namespace Misaka::Core::GameRoom {

export class GameRoom {
public:
    Entity::MisakaEntity AddEntity() {
        auto& registry = Context::Context::Instance().gameRoomContext.Registry;
        auto  entity   = registry->create();
        return Entity::MisakaEntity(entity, registry);
    }

    Entity::MisakaEntity GetEntity(entt::entity entity) {
        auto& registry = Context::Context::Instance().gameRoomContext.Registry;
        return Entity::MisakaEntity(entity, registry);
    }
};

} // namespace Misaka::Core::GameRoom