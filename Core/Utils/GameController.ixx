export module Misaka.Core.Utils.GameController;

import Misaka.Core.Context.Context;
import Misaka.Core.GameModule.OpenGLInitSystem;
import Misaka.Core.GameModule.OpenGLRenderSystem;
import Misaka.Core.GameModule.OpenGLAssetUpLoadSystem;
import Misaka.Core.GameRoom.GameRoom;
import Misaka.Core.Entity.MisakaEntity;
import Misaka.Core.Component.MeshComponent;
import Misaka.Core.Component.RenderComponent;
import Misaka.Core.Resource.AssetLoader;

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
        // 初始化游戏
        Context::Context::Instance().Initialize();
        GameModules::OpenGLInitSystem initSystem;
        initSystem.Init();

        GameRoom::GameRoom mainRoom;
        auto               entity        = mainRoom.AddEntity();
        auto&              meshComponent = entity.AddComponent<Component::MeshComponent>();
        entity.AddComponent<Component::RenderComponent>();
        Resource::AssetLoader().LoadMeshes("../Assets/Objects/cube.obj", meshComponent);

        auto view = Context::Context::Instance().gameRoomContext.Registry->view<Component::MeshComponent>();
    }
    void Loop() {
        // 游戏主循环
        while (!Context::Context::Instance().graphicsContext.shouldClose()) {
            m_AssetUpLoadSystem.Excute();
            m_RenderSystem.Render();
        }
    }
    void Exit() {
        // 退出游戏
    }

private:
    Context::Context*                    m_Context;
    GameModules::OpenGLAssetUpLoadSystem m_AssetUpLoadSystem;
    GameModules::OpenGLRenderSystem      m_RenderSystem;
};

} // namespace Misaka::Core::Utils