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

    static std::shared_ptr<IndexBuffer> Create(uint16_t* indices);

private:
    bgfx::IndexBufferHandle m_IndexBufferHandle;
};

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint16_t* indices) {
    auto indexBuffer                 = std::make_shared<IndexBuffer>();
    indexBuffer->m_IndexBufferHandle = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));
    return indexBuffer;
}

} // namespace Misaka::Core::Renderer
