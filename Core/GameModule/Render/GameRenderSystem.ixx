module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // Add this include for glm::value_ptr

export module Misaka.Core.GameModule.GameRenderSystem;

import Misaka.Core.GameModule.Interface.IRenderSystem;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Renderer.Renderer;
import Misaka.Core.Component.TransformComponent;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Manager.UniformBufferManager;
import Misaka.Core.Manager.TextureManager;
import Misaka.Core.Manager.FrameBufferManager;

namespace Misaka::Core::GameModule {

export class GameRenderSystem : public IRenderSystem {
public:
    virtual ~GameRenderSystem() = default;

    virtual void Render() override {
        auto registry = SingletonManager::GetInstance<entt::registry>();

        auto viewportFrameBuffer =
            SingletonManager::GetInstance<Manager::FrameBufferManager>()->GetFrameBuffer(Manager::FrameBufferType::VIEWPORT);
        viewportFrameBuffer->Bind();

        for (auto entity : registry->view<Component::RenderComponent, Component::TransformComponent>()) {
            auto& renderComponent    = registry->get<Component::RenderComponent>(entity);
            auto& transformComponent = registry->get<Component::TransformComponent>(entity);

            auto u_mvp = SingletonManager::GetInstance<Manager::UniformBufferManager>()->GetUniformBuffer("u_mvp");
            u_mvp->SetData(glm::value_ptr(CoreConfig::projection * CoreConfig::view * transformComponent.GetModelMatrix()));

            auto s_tex   = SingletonManager::GetInstance<Manager::UniformBufferManager>()->GetUniformBuffer("s_tex");
            auto texture = SingletonManager::GetInstance<Manager::TextureManager>()->GetTexture("docker.png");
            texture->SetData(0, s_tex);

            for (Component::Data::RenderData& data : renderComponent.renderDatas) {
                Renderer::Renderer::Submit(data.vertexBuffer, data.indexBuffer, data.shader, viewportFrameBuffer->GetViewId());
            }
        }
    }
};

} // namespace Misaka::Core::GameModule