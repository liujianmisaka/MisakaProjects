export module Misaka.Core.Component.PositionComponent;

import glm;
import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class PositionComponent : public IComponent {
public:
    union Position {
        glm::vec3 position = glm::vec3(0.0f);
        struct {
            float x;
            float y;
            float z;
        };
    };

    union Rotation {
        glm::vec3 rotation = glm::vec3(0.0f);
        struct {
            float x;
            float y;
            float z;
        };
    };

    union Scale {
        glm::vec3 scale = glm::vec3(1.0f);
        struct {
            float x;
            float y;
            float z;
        };
    };
};

} // namespace Misaka::Core::Components