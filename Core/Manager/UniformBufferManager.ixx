export module Misaka.Core.Manager.UniformBufferManager;

import <string>;
import <unordered_map>;
import <memory>;
import <iostream>;
import Misaka.Core.Renderer.UniformBuffer;

namespace Misaka::Core::Manager {

export class UniformBufferManager {
public:
    void Init() {
        CreateUniformBuffer("u_mvp", Renderer::UniformType::Mat4);
        CreateUniformBuffer("s_tex", Renderer::UniformType::Sampler);
    }

    std::shared_ptr<Renderer::UniformBuffer> CreateUniformBuffer(const char* name, Renderer::UniformType type) {
        m_UniformBuffers[name] = Renderer::UniformBuffer::Create(name, type);
        return m_UniformBuffers[name];
    }

    std::shared_ptr<Renderer::UniformBuffer> GetUniformBuffer(const std::string& name) {
        if (m_UniformBuffers.find(name) == m_UniformBuffers.end()) {
            std::cerr << "UniformBuffer not found" << std::endl;
            return nullptr;
        }
        return m_UniformBuffers[name];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Renderer::UniformBuffer>> m_UniformBuffers;
};

} // namespace Misaka::Core::Manager