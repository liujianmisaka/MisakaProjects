module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.IndexBuffer;

import <memory>;

namespace Misaka::Core::Renderer {

export class IndexBuffer {
public:
    IndexBuffer()  = default;
    ~IndexBuffer() = default;

    operator bgfx::IndexBufferHandle() const {
        return m_IndexBufferHandle;
    }

    void Bind() const {
        bgfx::setIndexBuffer(m_IndexBufferHandle);
    }

    static std::shared_ptr<IndexBuffer> Create(uint16_t* indices, uint32_t size) {
        auto buffer                 = std::make_shared<IndexBuffer>();
        buffer->m_IndexBufferHandle = bgfx::createIndexBuffer(bgfx::makeRef(indices, size));
        return buffer;
    }

    bgfx::IndexBufferHandle m_IndexBufferHandle;
};

} // namespace Misaka::Core::Renderer
