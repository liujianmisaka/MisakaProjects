export module Misaka.Core.Context.Context;

import Misaka.Core.Context.IContext;
import Misaka.Core.Utils.Singleton;
import Misaka.Core.Context.GameRoomContext;
import Misaka.Core.Context.GraphicsContext;

namespace Misaka::Core::Context {

export class Context : public IContext, public Utils::Singleton<Context> {
public:
    virtual ~Context() = default;

    GameRoomContext gameRoomContext;
    GraphicsContext graphicsContext;
};

} // namespace Misaka::Core::Context