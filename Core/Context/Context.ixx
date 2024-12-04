module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Context.Context;

import <string>;
import glm;
import Misaka.Core.Context.IContext;
import Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Context {

export class Context : public IContext, public Utils::Singleton<Context> {
public:
    virtual ~Context() = default;
};

} // namespace Misaka::Core::Context