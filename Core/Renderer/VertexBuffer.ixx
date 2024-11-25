module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.VertexBuffer;

import <memory>;
import Misaka.Core.Renderer.VertexLayout;
import Misaka.Core.Data.StaticMesh;

namespace Misaka::Core::Renderer {

export class VertexBuffer {
public:
    VertexBuffer()  = default;
    ~VertexBuffer() = default;

    operator bgfx::VertexBufferHandle() const {
        return m_VertexBufferHandle;
    }

    void Bind(uint8_t viewId = 0) const {
        bgfx::setVertexBuffer(viewId, m_VertexBufferHandle);
    }

    static std::shared_ptr<VertexBuffer> Create(Data::Vertex* vertices, uint32_t size, bgfx::VertexLayout layout) {
        auto buffer                  = std::make_shared<VertexBuffer>();
        buffer->m_VertexBufferHandle = bgfx::createVertexBuffer(bgfx::makeRef(vertices, size), layout);
        return buffer;
    }

    bgfx::VertexBufferHandle m_VertexBufferHandle;
};

} // namespace Misaka::Core::Renderer