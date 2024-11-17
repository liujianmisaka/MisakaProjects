export module Misaka.Core.Data.StaticMesh;

import <vector>;

namespace Misaka::Core::Data {

export struct Vertex {
    float position[3];
    float color[4];
};

export struct SubStaticMesh {
    std::vector<Vertex>   vertices;
    std::vector<uint16_t> indices;
};

export struct StaticMesh {
    std::vector<SubStaticMesh> subMeshes;

    void AddSubMesh(const SubStaticMesh& subMesh) {
        subMeshes.push_back(subMesh);
    }
};

} // namespace Misaka::Core::Data