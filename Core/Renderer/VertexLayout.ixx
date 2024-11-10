module;

#include <bgfx/bgfx.h>

export module Misaka.Core.Renderer.VertexLayout;

import <memory>;

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

    static std::shared_ptr<VertexLayout> Create();

private:
    bgfx::VertexLayout m_VertexLayout;
};

std::shared_ptr<VertexLayout> VertexLayout::Create() {
    return std::make_shared<VertexLayout>();
}

} // namespace Misaka::Core::Renderer