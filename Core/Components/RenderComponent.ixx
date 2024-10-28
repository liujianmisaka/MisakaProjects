export module Misaka.Core.Component.RenderComponent;

// import "Utils/MisakaStd.h";
import <cstdint>;
import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class RenderComponent : public IComponent {
public:
    RenderComponent() {
        textureID       = -1;
        shaderProgramID = -1;
        vertexArrayID   = -1;
        vertexBufferID  = -1;
        indexBufferID   = -1;
        indexCount      = -1;
    }
    RenderComponent(RenderComponent& other) {
        textureID       = other.textureID;
        shaderProgramID = other.shaderProgramID;
        vertexArrayID   = other.vertexArrayID;
        vertexBufferID  = other.vertexBufferID;
        indexBufferID   = other.indexBufferID;
        indexCount      = other.indexCount;

        other.textureID       = 0;
        other.shaderProgramID = 0;
        other.vertexArrayID   = 0;
        other.vertexBufferID  = 0;
        other.indexBufferID   = 0;
        other.indexCount      = 0;
    }

    std::uint32_t textureID;
    std::uint32_t shaderProgramID;
    std::uint32_t vertexArrayID;
    std::uint32_t vertexBufferID;
    std::uint32_t indexBufferID;
    std::uint32_t indexCount;
};

} // namespace Misaka::Core::Component