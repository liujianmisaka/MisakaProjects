module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // Add this include for glm::value_ptr

export module Misaka.Core.GameModule.RenderSystem;

import Misaka.Core.GameModule.Interface.IRenderSystem;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Renderer.Renderer;
import Misaka.Core.Component.WindowDataComponent;
import Misaka.Core.Component.FrameBufferComponent;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Utils.Registry;
import Misaka.Core.Manager.UniformBufferManager;
import Misaka.Core.Manager.TextureManager;

namespace Misaka::Core::GameModule {

export class RenderSystem : public IRenderSystem {
public:
    virtual ~RenderSystem() = default;
    virtual void Render() override {
        auto registry = SingletonManager::GetInstance<Utils::Registry>();

        auto& frameBufferComponent = Component::FrameBufferComponent::Instance();
        frameBufferComponent.viewportFrameBuffer->Bind();

        for (auto entity : registry->view<Component::RenderComponent>()) {
            auto& renderComponent = registry->get<Component::RenderComponent>(entity);
            auto& transformComponent = registry->get<Component::TransformComponent>(entity);

            auto u_mvp = SingletonManager::GetInstance<Manager::UniformBufferManager>()->GetUniformBuffer("u_mvp");
            u_mvp->SetData(glm::value_ptr(CoreConfig::projection * CoreConfig::view * transformComponent.GetModelMatrix()));

            auto s_tex = SingletonManager::GetInstance<Manager::UniformBufferManager>()->GetUniformBuffer("s_tex");
            auto texture = SingletonManager::GetInstance<Manager::TextureManager>()->GetTexture("docker.png");
            texture->SetData(0, s_tex);

            for (Component::Data::RenderData& data : renderComponent.renderDatas) {
                Renderer::Renderer::Submit(data.vertexBuffer, data.indexBuffer, data.shader,
                                           frameBufferComponent.viewportFrameBuffer->GetViewId());
            }
        }
    }
};

} // namespace Misaka::Core::GameModule