export module Misaka.Core.Context.Context;

import <string>;
import Misaka.Core.Context.IContext;
import Misaka.Core.Utils.Singleton;
import Misaka.Core.Context.GameRoomContext;
import Misaka.Core.Context.GraphicsContext;

namespace Misaka::Core::Context {

export class Context : public IContext, public Utils::Singleton<Context> {
public:
    virtual ~Context() = default;

    const std::string SHADER_ROOT_PATH = "../../Assets/Shaders/bgfx";

    GameRoomContext gameRoomContext;
    GraphicsContext graphicsContext;
};

} // namespace Misaka::Core::Context