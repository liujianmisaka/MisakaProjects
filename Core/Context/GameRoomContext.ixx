export module Misaka.Core.Context.GameRoomContext;

import <memory>;
import <entt/entt.hpp>;
import Misaka.Core.Context.IContext;

namespace Misaka::Core::Context {

export class GameRoomContext : public IContext {
public:
    virtual ~GameRoomContext() = default;

    std::shared_ptr<entt::registry> Registry = std::make_shared<entt::registry>();
};

} // namespace Misaka::Core::Context