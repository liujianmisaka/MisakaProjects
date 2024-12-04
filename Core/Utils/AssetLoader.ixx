module;

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

export module Misaka.Core.Utils.AssetLoader;

import <string>;
import <vector>;
import <memory>;
import glm;
import Misaka.Core.Data.StaticMesh;

namespace Misaka::Core::Utils {

export class AssetLoader {
public:
    static Data::StaticMesh LoadStaticMesh(const std::string& path) {
        Assimp::Importer importer;
        const aiScene*   scene =
            importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return Data::StaticMesh{};
        }

        Data::StaticMesh meshes;
        ProcessNode(scene->mRootNode, scene, meshes);

        return meshes;
    }

private:
    static void ProcessNode(aiNode* node, const aiScene* scene, Data::StaticMesh& meshes) {
        for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
            aiMesh*             assimpMesh = scene->mMeshes[node->mMeshes[i]];
            Data::SubStaticMesh subMesh    = ProcessMesh(assimpMesh, scene);
            meshes.AddSubMesh(subMesh);
        }

        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            ProcessNode(node->mChildren[i], scene, meshes);
        }
    }

    static Data::SubStaticMesh ProcessMesh(aiMesh* assimpMesh, const aiScene* scene) {
        Data::SubStaticMesh subMesh = {};

        for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i) {
            Data::Vertex vertex = {};

            // position
            vertex.position[0] = assimpMesh->mVertices[i].x;
            vertex.position[1] = assimpMesh->mVertices[i].y;
            vertex.position[2] = assimpMesh->mVertices[i].z;

            // color
            vertex.color[0] = 0.5f;
            vertex.color[1] = 0.5f;
            vertex.color[2] = 0.5f;
            vertex.color[3] = 1.0f;

            // texcoord
            if (assimpMesh->mTextureCoords[0]) {
                vertex.texcoord[0] = assimpMesh->mTextureCoords[0][i].x;
                vertex.texcoord[1] = assimpMesh->mTextureCoords[0][i].y;
            } else {
                vertex.texcoord[0] = 0.0f;
                vertex.texcoord[1] = 0.0f;
            }

            subMesh.vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i) {
            aiFace face = assimpMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                subMesh.indices.push_back((uint16_t)face.mIndices[j]);
            }
        }

        return subMesh;
    }
};

} // namespace Misaka::Core::Utils