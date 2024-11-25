export module Misaka.Core.Manager.TextureManager;

import <string>;
import <unordered_map>;
import <memory>;
import <iostream>;
import Misaka.Core.Renderer.Texture;
import Misaka.Core.CoreConfig;

namespace Misaka::Core::Manager {

export class TextureManager {
public:
    void LoadTexture(const char* name) {
        std::string path = (CoreConfig::TextureRoot / name).string();

        m_Textures[name] = Renderer::Texture::Create2D(path.c_str());
    }

    std::shared_ptr<Renderer::Texture> GetTexture(const std::string& name) {
        if (m_Textures.find(name) == m_Textures.end()) {
            std::cerr << "Texture not found" << std::endl;
            return nullptr;
        }
        return m_Textures[name];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Renderer::Texture>> m_Textures;
};

} // namespace Misaka::Core::Manager