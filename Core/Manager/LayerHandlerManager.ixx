export module Misaka.Core.Manager.LayerHandlerManager;

import <vector>;
import <memory>;
import Misaka.Core.Layer.ILayerHandler;
import Misaka.Core.Layer.MisakaGameLayerHandler;
import Misaka.Core.Layer.MisakaEditorLayerHandler;

namespace Misaka::Core::Manager {

export class LayerHandlerManager {
public:
    void InitWindowLayerHandler() {
        m_WindowLayerHandlers.push_back(std::make_unique<Layer::MisakaGameLayerHandler>());
        m_WindowLayerHandlers.push_back(std::make_unique<Layer::MisakaEditorLayerHandler>());
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