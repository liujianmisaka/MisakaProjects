export module Misaka.Core.Manager.FrameBufferManager;

import <string>;
import <unordered_map>;
import <memory>;
import <iostream>;
import Misaka.Core.Renderer.FrameBuffer;

namespace Misaka::Core::Manager {

export enum class FrameBufferType {
    VIEWPORT,
};

export class FrameBufferManager {
public:
    void Init() {
        CreateFrameBuffer(FrameBufferType::VIEWPORT, 900, 900, 2);
    }

    std::shared_ptr<Renderer::FrameBuffer> CreateFrameBuffer(FrameBufferType type, uint16_t width, uint16_t height, uint8_t viewId) {
        m_FrameBuffers[type] = Renderer::FrameBuffer::Create(width, height, viewId);
        return m_FrameBuffers[type];
    }

    std::shared_ptr<Renderer::FrameBuffer> GetFrameBuffer(FrameBufferType type) {
        if (m_FrameBuffers.find(type) == m_FrameBuffers.end()) {
            std::cerr << "FrameBuffer not found" << std::endl;
            return nullptr;
        }
        return m_FrameBuffers[type];
    }

private:
    std::unordered_map<FrameBufferType, std::shared_ptr<Renderer::FrameBuffer>> m_FrameBuffers;
};

} // namespace Misaka::Core::Manager