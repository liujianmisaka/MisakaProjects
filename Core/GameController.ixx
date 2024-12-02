module;

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <entt/entt.hpp>

export module Misaka.Core.GameController;

import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.GameModule.GameModule;
import Misaka.Core.GameModule.RenderInitSystem;
import Misaka.Core.GameModule.EditorInitSystem;
import Misaka.Core.GameModule.ManagerInitSystem;
import Misaka.Core.GameModule.AssetUpLoadSystem;
import Misaka.Core.GameModule.GameRenderSystem;
import Misaka.Core.GameModule.WindowRenderSystem;
import Misaka.Core.GameRoom.GameRoom;
import Misaka.Core.Component.MeshComponent;

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
        auto gameModule = SingletonManager::GetInstance<GameModule::GameModule>();
        gameModule->AddSystem<GameModule::RenderInitSystem>();
        gameModule->AddSystem<GameModule::EditorInitSystem>();
        gameModule->AddSystem<GameModule::ManagerInitSystem>();
        gameModule->AddSystem<GameModule::AssetUpLoadSystem>();
        gameModule->AddSystem<GameModule::GameRenderSystem>();
        gameModule->AddSystem<GameModule::WindowRenderSystem>();
        gameModule->Initialize();

        auto gameRoom = SingletonManager::GetInstance<GameRoom>();

        auto  entity        = gameRoom->AddEntity("cube");
        auto& meshComponent = entity.AddComponent<Component::MeshComponent>();
        meshComponent.meshes.push_back("cube");
    }

    void Loop() {
        while (!glfwWindowShouldClose(CoreConfig::window)) {
            glfwPollEvents();
            SingletonManager::GetInstance<GameModule::GameModule>()->Excute();
            SingletonManager::GetInstance<GameModule::GameModule>()->Render();
            bgfx::frame();
        }
    }

    void Exit() {
    }
};

} // namespace Misaka::Core