module;

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

export module Misaka.Core.Context.Context;

import <string>;
import Misaka.Core.Context.IContext;
import Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Context {

export class Context : public IContext, public Utils::Singleton<Context> {
public:
    virtual ~Context() = default;
};

} // namespace Misaka::Core::Context