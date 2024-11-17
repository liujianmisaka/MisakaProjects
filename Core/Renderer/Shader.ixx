module;

#include <bgfx/bgfx.h>
#include <cstdio>

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

    bgfx::ProgramHandle GetProgram() const {
        return m_Program;
    }

    static std::shared_ptr<Shader> Create(const char* vertexShaderPath, const char* fragmentShaderPath) {
        auto shader = std::make_shared<Shader>();

        bgfx::ShaderHandle vsh     = LoadShader(vertexShaderPath);
        bgfx::ShaderHandle fsh     = LoadShader(fragmentShaderPath);
        auto               program = bgfx::createProgram(vsh, fsh, true);
        if (!bgfx::isValid(program)) {
            std::cerr << "Failed to create shader program" << std::endl;
            return shader;
        }
        shader->m_Program = program;

        return shader;
    }

    static bgfx::ShaderHandle LoadShader(const char* filePath) {
        FILE* file = fopen(filePath, "rb");
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        const bgfx::Memory* mem = bgfx::alloc(size + 1);
        fread(mem->data, 1, size, file);
        fclose(file);

        mem->data[mem->size - 1] = '\0';
        return bgfx::createShader(mem);
    }

    bgfx::ProgramHandle m_Program;
};

} // namespace Misaka::Core::Renderer
