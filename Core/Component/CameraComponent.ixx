module;

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

export module Misaka.Core.Component.CameraComponent;

import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class CameraComponent : public IComponent {
public:
    glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 5.0f); // 摄像机位置
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // 目标位置
    glm::vec3 upDirection  = glm::vec3(0.0f, 1.0f, 0.0f); // 向上方向

    float fov         = glm::radians(45.0f); // 视野角度
    float aspectRatio = 16.0f / 9.0f;        // 屏幕宽高比
    float nearPlane   = 0.1f;                // 近裁剪面
    float farPlane    = 100.0f;              // 远裁剪面

    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(cameraPos, cameraTarget, upDirection);
    }

    glm::mat4 GetProjectionMatrix() const {
        return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    }
};

} // namespace Misaka::Core::Component