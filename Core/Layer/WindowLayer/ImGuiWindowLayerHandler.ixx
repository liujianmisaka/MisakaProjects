export module Misaka.Core.Layer.ImGuiWindowLayerHandler;

import Misaka.Core.Layer.ILayerHandler;
import Misaka.Core.SingletonManager;
import Misaka.Core.UI.MainWindow;

namespace Misaka::Core::Layer {

export class ImGuiWindowLayerHandler : public WindowLayerHandler {
public:
    virtual ~ImGuiWindowLayerHandler() = default;

    virtual void OnWindowLayerHandler() {
        SingletonManager::GetInstance<UI::MainWindow>()->BeginFrame();
        SingletonManager::GetInstance<UI::MainWindow>()->Draw();
        SingletonManager::GetInstance<UI::MainWindow>()->EndFrame();
    }
};

} // namespace Misaka::Core::Layer