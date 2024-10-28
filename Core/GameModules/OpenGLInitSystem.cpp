module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

module Misaka.Core.GameModule.OpenGLInitSystem;

import <vector>;
import <fstream>;
import <sstream>;
import <iostream>;
import Misaka.Core.Context.Context;

namespace Misaka::Core::GameModules {

static unsigned int compileShader(unsigned int type, const char *source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

// 创建着色器程序
static unsigned int createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
    unsigned int vertexShader   = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

static const char *readFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_NOT_FOUND\n";
        return nullptr;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string fileContent = buffer.str();
    char       *source      = new char[fileContent.size() + 1];
    std::strcpy(source, fileContent.c_str());

    return source;
}

static unsigned int createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
    const char *vertexShaderSource   = readFile(vertexPath);
    const char *fragmentShaderSource = readFile(fragmentPath);
    return createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void OpenGLInitSystem::Init() {
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    // 配置 OpenGL 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Triangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // 加载 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    Context::Context::Instance().graphicsContext.Window = window;

    // TODO: 放到其它地方
    unsigned int      shaderProgram = -1;
    const std::string PROJECT_PATH  = "D:/dev/MisakaProjects/";

    shaderProgram = createShaderProgram(PROJECT_PATH + "Assets/Shaders/base.vert", PROJECT_PATH + "Assets/Shaders/base.frag");
    Context::Context::Instance().graphicsContext.CommonShaders[Context::ShaderType::Base] = shaderProgram;
}

} // namespace Misaka::Core::GameModules
