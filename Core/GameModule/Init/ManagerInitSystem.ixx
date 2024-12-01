export module Misaka.Core.GameModule.ManagerInitSystem;

import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Manager.UniformBufferManager;
import Misaka.Core.Manager.MeshManager;
import Misaka.Core.Manager.ShaderManager;
import Misaka.Core.Manager.TextureManager;
import Misaka.Core.Manager.FrameBufferManager;
import Misaka.Core.Manager.LayerHandlerManager;

namespace Misaka::Core::GameModule {

export class ManagerInitSystem : public IInitSystem {
public:
    virtual void Initialize() override {
        SingletonManager::GetInstance<Manager::UniformBufferManager>()->Init();

        SingletonManager::GetInstance<Manager::FrameBufferManager>()->Init();

        SingletonManager::GetInstance<Manager::LayerHandlerManager>()->InitWindowLayerHandler();

        auto meshManager = SingletonManager::GetInstance<Manager::MeshManager>();
        meshManager->LoadStaticMesh("cube", (CoreConfig::ObjectRoot / "cube.obj").string());
        meshManager->LoadStaticMesh("capsule", (CoreConfig::ObjectRoot / "capsule.obj").string());
        meshManager->LoadStaticMesh("convexmesh", (CoreConfig::ObjectRoot / "convexmesh.obj").string());

        auto shaderManager = SingletonManager::GetInstance<Manager::ShaderManager>();
        shaderManager->LoadShader("base");

        auto textureManager = SingletonManager::GetInstance<Manager::TextureManager>();
        textureManager->LoadTexture("docker.png");
    }
};

} // namespace Misaka::Core::GameModule