module;

#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <stb_image.h>

export module Misaka.Core.Renderer.Texture;

import <memory>;
import <filesystem>;
import <iostream>;
import Misaka.Core.CoreConfig;
import Misaka.Core.Renderer.UniformBuffer;

namespace Misaka::Core::Renderer {

export class Texture {
public:
    Texture()  = default;
    ~Texture() = default;

    void SetData(uint8_t stage, std::shared_ptr<UniformBuffer> uniformBuffer) const {
        bgfx::setTexture(stage, uniformBuffer->GetHandle(), m_TextureHandle);
    }

    static std::shared_ptr<Texture> Create2D(const char* path) {
        stbi_uc* data = nullptr;
        int      width;
        int      height;
        int      channels;

        data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);

        if (data == nullptr) {
            std::cerr << "Failed to load texture: " << path << std::endl;
            return nullptr;
        }

        auto texture = std::make_shared<Texture>();

        const bgfx::Memory* mem  = bgfx::makeRef(data, width * height * 4);
        texture->m_TextureHandle = bgfx::createTexture2D(uint16_t(width), uint16_t(height), false, 1, bgfx::TextureFormat::RGBA8, 0, mem);

        // 检查是否创建成功
        if (!bgfx::isValid(texture->m_TextureHandle)) {
            std::cerr << "Failed to create texture: " << path << std::endl;
            return nullptr;
        }

        return texture;
    }

private:
    bgfx::TextureHandle m_TextureHandle;
};

} // namespace Misaka::Core::Renderer