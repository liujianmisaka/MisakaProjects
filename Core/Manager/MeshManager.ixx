export module Misaka.Core.Manager.MeshManager;

import <unordered_map>;
import <string>;
import <memory>;
import Misaka.Core.Data.StaticMesh;
import Misaka.Core.Utils.AssetLoader;

namespace Misaka::Core::Manager {

export class MeshManager {
public:
    void LoadStaticMesh(const std::string& name, const std::string& path) {
        m_Meshes[name] = std::make_shared<Data::StaticMesh>(Utils::AssetLoader::LoadStaticMesh(path));
    }

    void AddTriangle(const std::string& name) {
        Data::StaticMesh    mesh;
        Data::SubStaticMesh subMesh;

        {
            Data::Vertex vertex1 = {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}};
            Data::Vertex vertex2 = {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}};
            Data::Vertex vertex3 = {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
            Data::Vertex vertex4 = {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
            Data::Vertex vertex5 = {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
            Data::Vertex vertex6 = {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}};

            subMesh.vertices.push_back(vertex4);
            subMesh.vertices.push_back(vertex5);
            subMesh.vertices.push_back(vertex6);

            subMesh.indices.push_back(0);
            subMesh.indices.push_back(1);
            subMesh.indices.push_back(2);

            mesh.AddSubMesh(subMesh);
        }

        {
            Data::Vertex vertex1 = {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}};
            Data::Vertex vertex2 = {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}};
            Data::Vertex vertex3 = {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
            Data::Vertex vertex4 = {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
            Data::Vertex vertex5 = {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
            Data::Vertex vertex6 = {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}};

            subMesh.vertices.push_back(vertex1);
            subMesh.vertices.push_back(vertex2);
            subMesh.vertices.push_back(vertex3);

            subMesh.indices.push_back(3);
            subMesh.indices.push_back(4);
            subMesh.indices.push_back(5);

            mesh.AddSubMesh(subMesh);
        }

        m_Meshes[name] = std::make_shared<Data::StaticMesh>(mesh);
    }

    std::shared_ptr<Data::StaticMesh> GetStaticMesh(const std::string& name) {
        return m_Meshes[name];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Data::StaticMesh>> m_Meshes;
};

} // namespace Misaka::Core::Manager