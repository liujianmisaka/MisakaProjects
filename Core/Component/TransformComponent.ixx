export module Misaka.Core.Component.TransformComponent;

import glm;
import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class TransformComponent : public IComponent {
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale    = glm::vec3(1.0f);

    glm::mat4 GetModelMatrix() const {
        return glm::translate(glm::mat4(1.0f), position) *
               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
               glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), scale);
    }
};

} // namespace Misaka::Core::Component
