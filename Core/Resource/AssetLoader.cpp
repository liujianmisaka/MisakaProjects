module;

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

module Misaka.Core.Resource.AssetLoader;

import <memory>;
import <iostream>;
import Misaka.Core.Component.MeshComponent;

namespace Misaka::Core::Resource {

// 函数声明
static void                        ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Data::Mesh>>& meshes);
static std::shared_ptr<Data::Mesh> ProcessMesh(aiMesh* assimpMesh, const aiScene* scene);

void AssetLoader::LoadMeshes(const std::string& meshPath, Component::MeshComponent& meshComponent) {
    // 使用 Assimp 读取模型文件
    Assimp::Importer importer;
    const aiScene*   scene =
        importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

    // 检查文件是否成功导入
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    std::vector<std::shared_ptr<Data::Mesh>> meshes;
    ProcessNode(scene->mRootNode, scene, meshes);

    meshComponent.indices  = meshes[0]->indices;
    meshComponent.vertices = meshes[0]->vertices;
}

// 遍历aiNode并加载网格
static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Data::Mesh>>& meshes) {
    // 遍历当前节点的每个网格
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];
        auto    mesh       = ProcessMesh(assimpMesh, scene);
        meshes.push_back(mesh);
    }

    // 递归处理子节点
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene, meshes);
    }
}

// 处理网格的具体函数
static std::shared_ptr<Data::Mesh> ProcessMesh(aiMesh* assimpMesh, const aiScene* scene) {
    auto mesh = std::make_shared<Data::Mesh>();

    glm::mat4 modelMatrix  = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 modelMatrix2 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 modelMatrix3 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // 提取顶点数据
    for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i) {
        // position
        glm::vec4 transformedPosition = modelMatrix3 * modelMatrix2 * modelMatrix *
                                        glm::vec4(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z, 1.0f);

        mesh->vertices.push_back(transformedPosition.x / transformedPosition.w);
        mesh->vertices.push_back(transformedPosition.y / transformedPosition.w);
        mesh->vertices.push_back(transformedPosition.z / transformedPosition.w);

        /* mesh->vertices.push_back(assimpMesh->mVertices[i].x);
         mesh->vertices.push_back(assimpMesh->mVertices[i].y);
         mesh->vertices.push_back(assimpMesh->mVertices[i].z);*/

        // color
        if (assimpMesh->mColors[0]) {
            mesh->vertices.push_back(assimpMesh->mColors[0][i].r);
            mesh->vertices.push_back(assimpMesh->mColors[0][i].g);
            mesh->vertices.push_back(assimpMesh->mColors[0][i].b);
        } else {
            mesh->vertices.push_back(1.0f);
            mesh->vertices.push_back(0.5f);
            mesh->vertices.push_back(0.2f);
        }
    }

    // 提取索引数据
    for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i) {
        aiFace face = assimpMesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            mesh->indices.push_back(face.mIndices[j]);
        }
    }

    return mesh;
}

} // namespace Misaka::Core::Resource