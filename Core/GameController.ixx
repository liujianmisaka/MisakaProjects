module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

export module Misaka.Core.GameController;

import Misaka.Core.GameModule.RenderInitSystem;
import Misaka.Core.GameModule.ImGuiInitSystem;
import Misaka.Core.GameModule.ManagerInitSystem;
import Misaka.Core.GameRoom.GameRoom;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.WindowDataComponent;
import Misaka.Core.Component.FrameBufferComponent;
import Misaka.Core.Renderer.FrameBuffer;
import Misaka.Core.UI.MainWindow;

namespace Misaka::Core {

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
        GameModule::RenderInitSystem initSystem;
        initSystem.Initialize();

        GameModule::ImGuiInitSystem imguiInitSystem;
        imguiInitSystem.Initialize();

        GameModule::ManagerInitSystem managerInitSystem;
        managerInitSystem.Initialize();

        m_MainWindow = UI::MainWindow();
        m_MainRoom   = GameRoom::GameRoom();

        m_MainRoom.Init();

        auto  entity        = m_MainRoom.AddEntity("cube");
        auto& meshComponent = entity.AddComponent<Component::MeshComponent>();
        meshComponent.meshes.push_back("cube");

        Component::FrameBufferComponent::Instance().viewportFrameBuffer = Renderer::FrameBuffer::Create(900, 900, 2);
    }

    void Loop() {
        while (!glfwWindowShouldClose(Component::WindowDataComponent::Instance().window)) {
            glfwPollEvents();
            // bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);
            m_MainRoom.Excute();
            m_MainRoom.Render();
            bgfx::touch(0);
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
};

} // namespace Misaka::Core