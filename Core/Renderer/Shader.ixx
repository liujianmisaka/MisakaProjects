module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.Shader;

import <memory>;
import <fstream>;
import <iostream>;
import <vector>;

namespace Misaka::Core::Renderer {

export class Shader {
public:
    Shader()  = default;
    ~Shader() = default;

    operator bgfx::ProgramHandle() const {
        return m_Program;
    }

    static std::shared_ptr<Shader> Create(const char* vertexShaderPath, const char* fragmentShaderPath);

private:
    static bgfx::ShaderHandle LoadShader(const char* filePath);

private:
    bgfx::ProgramHandle m_Program;
};

std::shared_ptr<Shader> Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath) {
    auto               shader = std::make_shared<Shader>();
    bgfx::ShaderHandle vsh    = LoadShader(vertexShaderPath);
    bgfx::ShaderHandle fsh    = LoadShader(fragmentShaderPath);
    shader->m_Program         = bgfx::createProgram(vsh, fsh, true);
}

bgfx::ShaderHandle Shader::LoadShader(const char* filePath) {
    // 打开文件（以二进制模式读取）
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return BGFX_INVALID_HANDLE;
    }

    // 获取文件大小
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // 读取文件内容到缓冲区
    std::vector<char> buffer(size + 1); // 多一个字节用来存储 '\0'
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Failed to read shader file: " << filePath << std::endl;
        return BGFX_INVALID_HANDLE;
    }
    file.close();

    // 为字符串末尾添加终止符
    buffer[size] = '\0';

    // 使用 bgfx 分配内存
    const bgfx::Memory* mem = bgfx::copy(buffer.data(), static_cast<uint32_t>(buffer.size()));

    // 创建 ShaderHandle
    bgfx::ShaderHandle shader = bgfx::createShader(mem);

    // 检查 ShaderHandle 是否有效
    if (!bgfx::isValid(shader)) {
        std::cerr << "Failed to create shader from file: " << filePath << std::endl;
        return BGFX_INVALID_HANDLE;
    }

    return shader;
}

} // namespace Misaka::Core::Renderer
