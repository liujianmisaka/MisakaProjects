export module Misaka.Core.Component.TransformComponent;

import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class TransformComponent : public IComponent {
public:
    float Position[3] = {0.0f, 0.0f, 0.0f};
    float Rotation[3] = {0.0f, 0.0f, 0.0f};
    float Scale[3]    = {1.0f, 1.0f, 1.0f};
};

} // namespace Misaka::Core::Components
