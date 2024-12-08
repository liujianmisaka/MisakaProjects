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
std::filesystem::path Configs     = AssetRoot / "Configs";

glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 5.0f); // 摄像机位置
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // 目标位置
glm::vec3 upDirection  = glm::vec3(0.0f, 1.0f, 0.0f); // 向上方向
glm::mat4 view         = glm::lookAt(cameraPos, cameraTarget, upDirection);

float     fov                   = glm::radians(45.0f); // 视野角度
float     aspectRatio           = 1600 / 900;          // 屏幕宽高比
float     nearPlane             = 0.1f;                // 近裁剪面
float     farPlane              = 100.0f;              // 远裁剪面
glm::mat4 perspectiveProjection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

float     orthoNear       = -1.0f;      // 正交投影近裁剪面
float     orthoFar        = 1.0f;       // 正交投影远裁剪面
float     orthoFov        = 45.0f;      // 正交投影视野角度
float     orthoAspect     = 1600 / 900; // 正交投影宽高比
float     orthosize       = 10.0f;      // 正交投影大小
glm::mat4 orthoProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, -10.0f, 10.0f);

GLFWwindow* window       = nullptr;
int         windowWidth  = 1600;
int         windowHeight = 900;
const char* windowTitle  = "Misaka Engine";

} // namespace Misaka::Core::CoreConfig