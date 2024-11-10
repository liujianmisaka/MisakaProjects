module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.Texture;

import <memory>;

namespace Misaka::Core::Renderer {

export class Texture {
public:
    Texture()  = default;
    ~Texture() = default;

    void Bind() const;

    static std::shared_ptr<Texture> Create2D(int width, int height, const char* path);

private:
    bgfx::TextureHandle m_TextureHandle;
};

std::shared_ptr<Texture> Texture::Create2D(int width, int height, const char* path) {
    auto texture             = std::make_shared<Texture>();
    texture->m_TextureHandle = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGBA8, 0, bgfx::makeRef(nullptr, 0));
    return texture;
}

} // namespace Misaka::Core::Renderer