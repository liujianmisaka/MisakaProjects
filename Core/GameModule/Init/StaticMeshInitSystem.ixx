module;

#include <bgfx/bgfx.h>

export module Misaka.Core.GameModule.StaticMeshInitSystem;

import <filesystem>;
import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.SingletonManager;
import Misaka.Core.Manager.MeshManager;
import Misaka.Core.CoreConfig;
import Misaka.Core.Context.Context;

namespace Misaka::Core::GameModule {

export class StaticMeshInitSystem : public IInitSystem {
public:
    void Initialize() override {
        auto meshManager = SingletonManager::GetInstance<Manager::MeshManager>();
        meshManager->LoadStaticMesh("Cube", (CoreConfig::ObjectRoot / "cube.obj").string());
        meshManager->AddTriangle("Triangle");
    }
};

} // namespace Misaka::Core::GameModule