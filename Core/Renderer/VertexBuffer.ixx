module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.VertexBuffer;

import <memory>;
import Misaka.Core.Renderer.VertexLayout;

namespace Misaka::Core::Renderer {

export class VertexBuffer {
public:
    VertexBuffer()  = default;
    ~VertexBuffer() = default;

    operator bgfx::VertexBufferHandle() const {
        return m_VertexBufferHandle;
    }

    void Bind(uint16_t viewId = 0) const {
        bgfx::setVertexBuffer(viewId, m_VertexBufferHandle);
    }

    static std::shared_ptr<VertexBuffer> Create(float* vertices, VertexLayout layout);

private:
    bgfx::VertexBufferHandle m_VertexBufferHandle;
};

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, VertexLayout layout) {
    auto vertexBuffer                  = std::make_shared<VertexBuffer>();
    vertexBuffer->m_VertexBufferHandle = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), layout);
    return vertexBuffer;
}

} // namespace Misaka::Core::Renderer