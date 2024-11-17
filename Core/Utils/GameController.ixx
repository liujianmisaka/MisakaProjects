module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

export module Misaka.Core.Utils.GameController;

import Misaka.Core.Context.Context;
import Misaka.Core.GameModule.RenderInitSystem;
import Misaka.Core.GameModule.RenderSystem;
import Misaka.Core.GameModule.AssetUpLoadSystem;
import Misaka.Core.GameModule.ImGuiInitSystem;
import Misaka.Core.GameModule.ShaderInitSystem;
import Misaka.Core.GameModule.StaticMeshInitSystem;
import Misaka.Core.GameRoom.GameRoom;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Component.WindowDataComponent;
import Misaka.Core.Component.FrameBufferComponent;
import Misaka.Core.Renderer.FrameBuffer;
import Misaka.Core.UI.MainWindow;

namespace Misaka::Core::Utils {

export class GameController {
public:
    GameController()  = default;
    ~GameController() = default;

    void Run() {
        Init();
        Loop();
        Exit();
    }

protected:
    void Init() {
        Context::Context::Instance().Initialize();

        GameModule::RenderInitSystem initSystem;
        initSystem.Initialize();

        GameModule::StaticMeshInitSystem staticMeshLoadSystem;
        staticMeshLoadSystem.Initialize();

        GameModule::ImGuiInitSystem imguiInitSystem;
        imguiInitSystem.Initialize();

        GameModule::ShaderInitSystem shaderInitSystem;
        shaderInitSystem.Initialize();

        m_MainWindow = UI::MainWindow();

        m_MainRoom.Init();

        auto  entity        = m_MainRoom.AddEntity();
        auto& meshComponent = entity.AddComponent<Component::MeshComponent>();
        meshComponent.meshes.push_back("Cube");

        Component::FrameBufferComponent::Instance().viewportFrameBuffer = Renderer::FrameBuffer::Create(900, 900, 2);
    }

    void Loop() {
        while (!glfwWindowShouldClose(Component::WindowDataComponent::Instance().window)) {
            glfwPollEvents();
            // bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);
            bgfx::touch(0);
            m_MainRoom.Excute();
            m_MainRoom.Render();
            m_MainWindow.BeginFrame();
            m_MainWindow.Draw();
            m_MainWindow.EndFrame();
            bgfx::frame();
            // bgfx::dbgTextClear();
            // bgfx::dbgTextPrintf(0, 0, 0x0f, "Hello bgfx!");
        }
    }

    void Exit() {
    }

private:
    GameRoom::GameRoom m_MainRoom;
    UI::MainWindow     m_MainWindow;

    bgfx::VertexBufferHandle vbh;
    bgfx::IndexBufferHandle  ibh;
};

} // namespace Misaka::Core::Utils