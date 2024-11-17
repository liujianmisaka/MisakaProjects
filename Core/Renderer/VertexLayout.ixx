module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.VertexLayout;

namespace Misaka::Core::Renderer {

export class VertexLayout {
public:
    VertexLayout()  = default;
    ~VertexLayout() = default;

    operator bgfx::VertexLayout() const {
        return m_VertexLayout;
    }

    void Begin() {
        m_VertexLayout.begin();
    }
    void End() {
        m_VertexLayout.end();
    }

    void AddPosition() {
        m_VertexLayout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
    }
    void AddColor() {
        m_VertexLayout.add(bgfx::Attrib::Color0, 3, bgfx ::AttribType::Float);
    }

    static VertexLayout Create() {
        return VertexLayout();
    }

    bgfx::VertexLayout m_VertexLayout;
};

} // namespace Misaka::Core::Renderer