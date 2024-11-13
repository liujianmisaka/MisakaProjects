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

    static std::shared_ptr<IndexBuffer> Create(unsigned int* indices) {
        auto indexBuffer                 = std::make_shared<IndexBuffer>();
        indexBuffer->m_IndexBufferHandle = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));
        return indexBuffer;
    }

private:
    bgfx::IndexBufferHandle m_IndexBufferHandle;
};

} // namespace Misaka::Core::Renderer
