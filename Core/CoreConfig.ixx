module;

#include <GLFW/glfw3.h>

export module Misaka.Core.CoreConfig;

import <filesystem>;
import <string>;
import glm;

export namespace Misaka::Core::CoreConfig {

// 一些全局配置
std::filesystem::path AssetRoot   = "../Assets";
std::filesystem::path ObjectRoot  = AssetRoot / "Objects";
std::filesystem::path ShaderRoot  = AssetRoot / "Shaders";
std::filesystem::path TextureRoot = AssetRoot / "Textures";

glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 5.0f); // 摄像机位置
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // 目标位置
glm::vec3 upDirection  = glm::vec3(0.0f, 1.0f, 0.0f); // 向上方向
glm::mat4 view         = glm::lookAt(cameraPos, cameraTarget, upDirection);

float     fov         = glm::radians(45.0f); // 视野角度
float     aspectRatio = 1.0f;                // 屏幕宽高比
float     nearPlane   = 0.1f;                // 近裁剪面
float     farPlane    = 100.0f;              // 远裁剪面
glm::mat4 projection  = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

GLFWwindow* window       = nullptr;
int         windowWidth  = 1600;
int         windowHeight = 900;
const char* windowTitle  = "Misaka Engine";

} // namespace Misaka::Core::CoreConfig