export module Misaka.Core.GameModule.EditorInitSystem;

import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.SingletonManager;
import Misaka.Core.Editor.MisakaEditor;

namespace Misaka::Core::GameModule {

export class EditorInitSystem : public IInitSystem {
public:
    virtual ~EditorInitSystem() = default;

    virtual void Initialize() override {
        SingletonManager::GetInstance<Editor::MisakaEditor>()->Init();
    }
};

} // namespace Misaka::Core::GameModule
