export module Misaka.Core.Layer.MisakaEditorLayerHandler;

import Misaka.Core.Layer.ILayerHandler;
import Misaka.Core.SingletonManager;
import Misaka.Core.Editor.MisakaEditor;

namespace Misaka::Core::Layer {

export class MisakaEditorLayerHandler : public WindowLayerHandler {
public:
    virtual ~MisakaEditorLayerHandler() = default;

    virtual void OnWindowLayerHandler() {
        SingletonManager::GetInstance<Editor::MisakaEditor>()->Tick();
    }
};

} // namespace Misaka::Core::Layer