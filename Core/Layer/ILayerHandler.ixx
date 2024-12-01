export module Misaka.Core.Layer.ILayerHandler;

namespace Misaka::Core::Layer {

export class ILayerHandler {
public:
    virtual ~ILayerHandler() = default;

    virtual void OnLayerHandler() = 0;
};

export class WindowLayerHandler : public ILayerHandler {
public:
    virtual ~WindowLayerHandler() = default;

    virtual void OnLayerHandler() override {
        OnWindowLayerHandler();
    }

    virtual void OnWindowLayerHandler() = 0;
};

} // namespace Misaka::Core::Layer