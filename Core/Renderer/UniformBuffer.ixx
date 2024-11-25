module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.UniformBuffer;

import <memory>;
import <iostream>;

namespace Misaka::Core::Renderer {

export enum class UniformType {
    Mat4,
    Sampler,
    Count,
};

export class UniformBuffer {
public:
    void SetData(const float* data) const {
        bgfx::setUniform(m_UniformHandle, data);
    }

    auto GetHandle() const {
        return m_UniformHandle;
    }

    static std::shared_ptr<UniformBuffer> Create(const char* name, UniformType type) {
        auto buffer = std::make_shared<UniformBuffer>();

        switch (type) {
            case Misaka::Core::Renderer::UniformType::Mat4: {
                buffer->m_UniformHandle = bgfx::createUniform(name, bgfx::UniformType::Mat4);
                break;
            }
            case Misaka::Core::Renderer::UniformType::Sampler: {
                buffer->m_UniformHandle = bgfx::createUniform(name, bgfx::UniformType::Sampler);
                break;
            }
            default: {
                std::cerr << "Failed to create uniform buffer" << std::endl;
                break;
            }
        }

        return buffer;
    }

    operator bgfx::UniformHandle() const {
        return m_UniformHandle;
    }

private:
    bgfx::UniformHandle m_UniformHandle;
};

} // namespace Misaka::Core::Renderer