module;

#include <bgfx/bgfx.h>
#include <bx/bx.h>

export module Misaka.Core.Renderer.FrameBuffer;

import <memory>;
import <print>;

namespace Misaka::Core::Renderer {

export class FrameBuffer {
public:
    FrameBuffer()  = default;
    ~FrameBuffer() = default;

    void Bind() const {
        bgfx::setViewFrameBuffer(m_ViewId, m_FrameBufferHandle);
        bgfx::setViewRect(m_ViewId, 0, 0, m_Width, m_Height);
        bgfx::setViewClear(m_ViewId, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
        bgfx::touch(m_ViewId);
    }

    uint16_t GetTextureIndex() const {
        return bgfx::getTexture(m_FrameBufferHandle).idx;
    }

    uint8_t GetViewId() const {
        return m_ViewId;
    }

    void SetViewportSize(uint16_t width, uint16_t height) {
        m_Width  = width;
        m_Height = height;
    }

    static std::shared_ptr<FrameBuffer> Create(uint16_t width, uint16_t height, uint8_t viewId) {
        auto frameBuffer = std::make_shared<FrameBuffer>();

        auto colorTexture = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT);
        auto depthTexture = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT);

        // 将颜色和深度纹理绑定到 Framebuffer
        bgfx::TextureHandle attachments[] = {colorTexture, depthTexture};
        frameBuffer->m_FrameBufferHandle  = bgfx::createFrameBuffer(BX_COUNTOF(attachments), attachments, true);
        if (!bgfx::isValid(frameBuffer->m_FrameBufferHandle)) {
            std::println("Failed to create FrameBuffer");
        }
        frameBuffer->m_ViewId       = viewId;
        frameBuffer->m_Width        = width;
        frameBuffer->m_Height       = height;
        frameBuffer->m_ColorTexture = colorTexture;
        frameBuffer->m_DepthTexture = depthTexture;

        return frameBuffer;
    }

private:
    bgfx::FrameBufferHandle m_FrameBufferHandle;
    uint8_t                m_ViewId;
    uint16_t                m_Width;
    uint16_t                m_Height;
    bgfx::TextureHandle     m_ColorTexture;
    bgfx::TextureHandle     m_DepthTexture;
};

} // namespace Misaka::Core::Renderer