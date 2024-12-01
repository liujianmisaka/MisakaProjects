export module Misaka.Core.Manager.LayerHandlerManager;

import <vector>;
import <memory>;
import Misaka.Core.Layer.ILayerHandler;
import Misaka.Core.Layer.GameWindowLayerHandler;
import Misaka.Core.Layer.ImGuiWindowLayerHandler;

namespace Misaka::Core::Manager {

export class LayerHandlerManager {
public:
    void InitWindowLayerHandler() {
        m_WindowLayerHandlers.push_back(std::make_unique<Layer::GameWindowLayerHandler>());
        m_WindowLayerHandlers.push_back(std::make_unique<Layer::ImGuiWindowLayerHandler>());
    }

    void DoWindowLayer() {
        for (auto& handler : m_WindowLayerHandlers) {
            handler->OnLayerHandler();
        }
    }

private:
    std::vector<std::unique_ptr<Layer::WindowLayerHandler>> m_WindowLayerHandlers;
};

} // namespace Misaka::Core::Manager