export module Misaka.Core.Component.MeshComponent;

//import "Utils/MisakaStd.h";
import <vector>;
import Misaka.Core.Component.IComponent;

namespace Misaka::Core::Component {

export class MeshComponent : public IComponent {
public:
    std::vector<float>        vertices;
    std::vector<unsigned int> indices;
};

} // namespace Misaka::Core::Components