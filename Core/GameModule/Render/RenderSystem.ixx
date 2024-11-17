module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <entt/entt.hpp>

export module Misaka.Core.GameModule.RenderSystem;

import Misaka.Core.GameModule.Interface.IRenderSystem;
import Misaka.Core.Context.Context;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Renderer.Renderer;
import Misaka.Core.Component.WindowDataComponent;
import Misaka.Core.Component.FrameBufferComponent;
import Misaka.Core.SingletonManager;
import Misaka.Core.Utils.Registry;

namespace Misaka::Core::GameModule {

export class RenderSystem : public IRenderSystem {
public:
    virtual ~RenderSystem() = default;
    virtual void Render() override {
        auto registry = SingletonManager::GetInstance<entt::registry>();

        auto& frameBufferComponent = Component::FrameBufferComponent::Instance();
        frameBufferComponent.viewportFrameBuffer->Bind();

        for (auto entity : registry->view<Component::RenderComponent>()) {
            auto& renderComponent = registry->get<Component::RenderComponent>(entity);

            for (Component::Data::RenderData& data : renderComponent.renderDatas) {
                Renderer::Renderer::Submit(data.vertexBuffer, data.indexBuffer, data.shader,
                                           frameBufferComponent.viewportFrameBuffer->GetViewId());
            }
        }
    }
};

} // namespace Misaka::Core::GameModule