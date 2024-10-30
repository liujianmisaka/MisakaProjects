export module Misaka.Core.Utils.GameController;

import <GLFW/glfw3.h>;
import <glad/glad.h>;
import Misaka.Core.Context.Context;
import Misaka.Core.GameModule.RenderInitSystem;
import Misaka.Core.GameModule.OpenGLRenderSystem;
import Misaka.Core.GameModule.OpenGLAssetUpLoadSystem;
import Misaka.Core.GameRoom.GameRoom;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Resource.AssetLoader;
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

        GameModules::RenderInitSystem initSystem;
        initSystem.Init();

        m_MainWindow = UI::MainWindow();
        m_MainWindow.Initialize();

        m_MainRoom.Init();

        auto  entity        = m_MainRoom.AddEntity();
        auto& meshComponent = entity.AddComponent<Component::MeshComponent>();
        entity.AddComponent<Component::RenderComponent>();
        Resource::AssetLoader().LoadMeshes("../Assets/Objects/cube.obj", meshComponent);
    }
    void Loop() {
        while (!Context::Context::Instance().graphicsContext.shouldClose()) {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            m_MainWindow.BeginFrame();
            m_MainWindow.Draw();
            m_MainWindow.EndFrame();
            // m_MainRoom.Excute();
            // m_MainRoom.Render();
            glfwSwapBuffers(Context::Context::Instance().graphicsContext.Window);
        }
    }
    void Exit() {}

private:
    GameRoom::GameRoom m_MainRoom;
    UI::MainWindow     m_MainWindow;
};

} // namespace Misaka::Core::Utils